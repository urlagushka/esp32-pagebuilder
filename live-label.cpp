#include "live-label.hpp"

kb::LiveLabel::LiveLabel(const Block * src, c_str_ref_t label, std::size_t dtime):
    Widget(src->get_label(), label, WIDGET_TYPE::OUT),
    dtime_(dtime)
{}

const std::pair< kb::str_t, kb::str_t > kb::LiveLabel::generate() const
{
    str_t body_part = "";
    body_part += "<div class=\"lifetime\"><p>";
    body_part += label_ + " : <span id=\"" + hash_ + "\">nullptr</span></p></div>";

    str_t script_part = "";
    script_part += "function F" + hash_ + "() {";
    script_part += "xml_queue.push({hash: \"" + hash_ + "\", type: WIDGET_TYPE.OUT, data: \"\"}); }";
    script_part += "setInterval(F" + hash_ + ", " + std::to_string(dtime_) + ");";

    return std::make_pair(body_part, script_part);
}
