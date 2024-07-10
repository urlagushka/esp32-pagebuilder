#include "button.hpp"

kb::Button::Button(const Block * src, c_str_ref_t label):
    Widget(src->get_label(), label, WIDGET_TYPE::IN)
{}

const std::pair< kb::str_t, kb::str_t > kb::Button::generate() const
{
    str_t body_part = "";
    body_part += "<div><p>";
    body_part += "<button class=\"btns\" onclick=\"" + hash_ + "_func()\">" + label_ + "</button> ";
    body_part += "<p></div>";

    str_t script_part = "";
    script_part += "function " + hash_ + "_func(data){var xhttp = new XMLHttpRequest();";
    script_part += "xhttp.open(\"GET\", \"" + hash_ + "\", true);xhttp.send();}";
    return std::make_pair(body_part, script_part);
}
