#include "button-field.hpp"

kb::ButtonField::ButtonField(const Block * src, c_str_ref_t article, c_str_ref_t label):
    Widget(src->get_label(), label, WIDGET_TYPE::IN),
    article_(article)
{}

const std::pair< kb::str_t, kb::str_t > kb::ButtonField::generate() const
{
    str_t body_part = "";
    body_part += "<div class=\"const\"><p>";
    body_part += article_ + "<br>";
    body_part += "<button class=\"btn\" onclick=\"" + hash_ + "_func()\">" + label_ + "</button> ";
    body_part += "<input type=\"text\" id=\"" + hash_ + "_line\"> ";
    body_part += "<p></div>";

    str_t script_part = "";
    script_part += "function " + hash_ + "_func(data){var xhttp = new XMLHttpRequest();";
    script_part += "xhttp.open(\"GET\", \"" + hash_ + "?data=\" + document.getElementById(\"" + hash_ + "_line\").value, true);xhttp.send();}";
    return std::make_pair(body_part, script_part);
}
