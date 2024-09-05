#include "button-field.hpp"

kb::ButtonField::ButtonField(const Block * src, c_str_ref_t article, c_str_ref_t label):
    Widget(src->get_label() + article, label, WIDGET_TYPE::IN),
    article_(article)
{}

const std::pair< kb::str_t, kb::str_t > kb::ButtonField::generate() const
{
    str_t body_part = "";
    body_part += "<div class=\"const\"><p>";
    body_part += article_ + "<br>";
    body_part += "<button class=\"btn\" onclick=\"F" + hash_ + "()\">" + label_ + "</button> ";
    body_part += "<input type=\"text\" id=\"L" + hash_ + "\"> ";
    body_part += "<p></div>";

    str_t script_part = "";
    script_part += "function F" + hash_ + "() {";
    script_part += "xml_queue.unshift({hash: \"" + hash_ + "\", type: WIDGET_TYPE.IN, data: document.getElementById(\"L" + hash_ + "\").value}); }";

    return std::make_pair(body_part, script_part);
}
