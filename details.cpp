#include "details.hpp"

kb::UriData::UriData(c_str_ref_t uri):
    label(""),
    data("")
{
    auto it = ++uri.begin();
    for (; *it != '?' && it != uri.end(); ++it)
    {
        label.push_back(*it);
    }
    for (std::size_t i = 0; i < 6 && it != uri.end(); ++i, ++it);
    for (; it != uri.end(); ++it)
    {
        data.push_back(*it);
    }
}

kb::EspErrorCollector::EspErrorCollector():
    error(ESP_OK)
{}

void kb::EspErrorCollector::add_error(esp_err_t rhs)
{
    if (error != ESP_OK)
    {
        return;
    }

    error = rhs;
}
