#include "live-label.hpp"

kb::LiveLabel::LiveLabel(const Block * src, c_str_ref_t label, std::size_t delay):
    Widget(src->get_label(), label, WIDGET_TYPE::OUT),
    delay_(delay)
{}

const std::pair< kb::str_t, kb::str_t > kb::LiveLabel::generate() const
{
    str_t body_part = "";
    body_part += "<div class=\"lifetime\"><p>";
    body_part += label_ + " : <span id=\"" + hash_ + "\">nullptr</span></p></div>";

    str_t script_part = "setInterval(function() {";
    script_part += "var xhttp = new XMLHttpRequest();";
    script_part += "xhttp.onreadystatechange = function() {";
    script_part += "if (this.readyState == 4 && this.status == 200) {";
    script_part += "document.getElementById(\"" + hash_ + "\").innerHTML = this.responseText;}};";
    script_part += "xhttp.open(\"GET\", \"" + hash_ + "\", true);";
    script_part += "xhttp.send();}, " + std::to_string(delay_) + ");";
    return std::make_pair(body_part, script_part);
}
