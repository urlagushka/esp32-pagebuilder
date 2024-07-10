idf_component_register(SRCS "block.cpp" "button-field.cpp" "button.cpp" "details.cpp" "http-server.cpp" "live-label.cpp" "page-builder.cpp" "stylesheet.cpp" "widget.cpp"
                    INCLUDE_DIRS "include"
                    REQUIRES "esp_http_server" "esp_wifi" "nvs_flash")
