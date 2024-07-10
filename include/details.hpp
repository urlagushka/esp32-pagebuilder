#ifndef DETAILS_HPP
#define DETAILS_HPP

#include <string>

#include "esp_check.h"

namespace kb
{
    using str_t = std::string;
    using str_ref_t = str_t &;
    using c_str_ref_t = const str_t &;

    struct UriData
    {
        UriData(c_str_ref_t uri);
        str_t label;
        str_t data;
    };

    struct EspErrorCollector
    {
        EspErrorCollector();
        void add_error(esp_err_t rhs);

        esp_err_t error;
    };
}

#endif
