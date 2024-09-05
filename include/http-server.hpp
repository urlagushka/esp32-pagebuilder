#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include <esp_http_server.h>
#include <esp_wifi.h>
#include <esp_err.h>
#include <esp_event.h>

#include <string>
#include <map>

#include "widget.hpp"

namespace kb
{
    using str_t = std::string;
    using str_ref_t = str_t &;
    using c_str_ref_t = const str_t &;

    enum class WIFITYPE
    {
        STA, AP
    };

    class HTTPServer
    {        
        public:
            HTTPServer() = delete;
            HTTPServer(const char * ssid, const char * password, WIFITYPE wtype);
            HTTPServer(const HTTPServer &) = delete;
            HTTPServer(HTTPServer &&) = delete;
            HTTPServer operator=(const HTTPServer &) = delete;
            HTTPServer operator=(HTTPServer &&) = delete;
            ~HTTPServer();

            esp_err_t init();
            esp_err_t connect();
            bool is_connected();
            esp_err_t start();

            void bind(const Widget * wget, void (*addf)(c_str_ref_t));
            void bind(const Widget * wget, str_t (*addf)());
            void bind(const Widget * wget, str_t (*addf)(c_str_ref_t));

            virtual void setup_page() = 0;

        protected:
            inline static std::map< str_t, void (*)(c_str_ref_t) > in_addf_;
            inline static std::map< str_t, str_t (*)() > out_addf_;
            inline static std::map< str_t, str_t (*)(c_str_ref_t) > inout_addf_;

            inline static str_t page_ = "";
        private:
            WIFITYPE wtype_;
            httpd_handle_t server_;
            wifi_config_t wifi_config_;
            EventGroupHandle_t wifi_event_;

            httpd_uri_t uri_get_;
            httpd_uri_t uri_post_;

            static esp_err_t get_handler_(httpd_req_t * req);
            static esp_err_t post_handler_(httpd_req_t * req);
    };
}

#endif
