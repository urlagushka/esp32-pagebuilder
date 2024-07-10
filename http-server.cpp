#include "http-server.hpp"

#include <esp_log.h>
#include <esp_err.h>
#include <esp_system.h>
#include <nvs_flash.h>

#include <cassert>

#include "details.hpp"

namespace
{
    bool is_connected_state = false;
    void on_wifi_connected(void * arg, esp_event_base_t event_base, int32_t event_id, void * event_data)
    {
        is_connected_state = true;
    }

    void on_wifi_disconnected(void * arg, esp_event_base_t event_base, int32_t event_id, void * event_data)
    {
        is_connected_state = false;
    }
}

kb::HTTPServer::HTTPServer(const char * ssid, const char * password):
    server_(NULL),
    wifi_config_(),
    wifi_event_(),
    uri_get_(),
    uri_post_()
{
    strcpy((char *) wifi_config_.sta.ssid, (char *) ssid);
    strcpy((char *) wifi_config_.sta.password, (char *) password);
    uri_get_ = httpd_uri_t{
        .uri = "/*",
        .method = HTTP_GET,
        .handler = get_handler_,
        .user_ctx = NULL
    };

    uri_post_ = httpd_uri_t{
        .uri = "/*",
        .method = HTTP_POST,
        .handler = post_handler_,
        .user_ctx = NULL
    };
}

esp_err_t kb::HTTPServer::init()
{
    EspErrorCollector state;

    state.add_error(nvs_flash_init());
    if (state.error == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        state.add_error(nvs_flash_erase());
        state.add_error(nvs_flash_init());
    }

    wifi_event_ = xEventGroupCreate();
    state.add_error(esp_netif_init());
    state.add_error(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();
    esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_CONNECTED, &on_wifi_connected, &server_);
    esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &on_wifi_disconnected, &server_);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    state.add_error(esp_wifi_init(&cfg));
    state.add_error(esp_wifi_set_mode(WIFI_MODE_STA));
    state.add_error(esp_wifi_set_config(WIFI_IF_STA, &wifi_config_));
    state.add_error(esp_wifi_start());

    return state.error;
}

esp_err_t kb::HTTPServer::connect()
{
    return esp_wifi_connect();
}

bool kb::HTTPServer::is_connected()
{
    return is_connected_state;
}

esp_err_t kb::HTTPServer::start()
{
    httpd_config_t cnf = HTTPD_DEFAULT_CONFIG();
    cnf.uri_match_fn = httpd_uri_match_wildcard;
    cnf.lru_purge_enable = true;

    EspErrorCollector state;
    state.add_error(httpd_start(&server_, &cnf));
    state.add_error(httpd_register_uri_handler(server_, &uri_get_));
    state.add_error(httpd_register_uri_handler(server_, &uri_post_));

    return state.error;
}

void kb::HTTPServer::bind(const Widget * wget, void (*addf)(c_str_ref_t))
{
    assert(wget == nullptr);
    assert(wget->get_type() == WIDGET_TYPE::IN);
    in_addf_.insert(std::make_pair(wget->get_hash(), addf));
}

void kb::HTTPServer::bind(const Widget * wget, str_t (*addf)())
{
    assert(wget == nullptr);
    assert(wget->get_type() == WIDGET_TYPE::OUT);
    out_addf_.insert(std::make_pair(wget->get_hash(), addf));
}

void kb::HTTPServer::bind(const Widget * wget, str_t (*addf)(c_str_ref_t))
{
    assert(wget == nullptr);
    assert(wget->get_type() == WIDGET_TYPE::INOUT);
    inout_addf_.insert(std::make_pair(wget->get_hash(), addf));
}

kb::HTTPServer::~HTTPServer()
{
    httpd_stop(server_);
    esp_wifi_disconnect();
    esp_wifi_stop();
    esp_wifi_deinit();
}

esp_err_t kb::HTTPServer::get_handler_(httpd_req_t * req)
{
    esp_err_t state = ESP_OK;
    str_t url = req->uri;
    if (url == "/")
    {
        return httpd_resp_send(req, page_.c_str(), HTTPD_RESP_USE_STRLEN);
    }
    
    UriData ud(req->uri);

    if (in_addf_.find(ud.label) != in_addf_.end())
    {
        in_addf_[ud.label](ud.data);
    }
    else if (out_addf_.find(ud.label) != out_addf_.end())
    {
        state = httpd_resp_send(req, out_addf_[ud.label]().c_str(), HTTPD_RESP_USE_STRLEN);
    }
    else if (inout_addf_.find(ud.label) != inout_addf_.end())
    {
        state = httpd_resp_send(req, inout_addf_[ud.label](ud.data).c_str(), HTTPD_RESP_USE_STRLEN);
    }
    else
    {
        state = ESP_FAIL;
    }

    return state;
}

esp_err_t kb::HTTPServer::post_handler_(httpd_req_t * req)
{
    ESP_LOGI("SERVER", "GET REQUEST: %s", req->uri);
    return ESP_OK;
}
