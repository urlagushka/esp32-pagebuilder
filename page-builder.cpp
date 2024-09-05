#include "page-builder.hpp"

kb::PageBuilder::PageBuilder(c_str_ref_t stylesheet, std::size_t dtime):
    title_(""),
    header_(""),
    stylesheet_(stylesheet),
    body_(""),
    script_(""),
    dtime_(dtime)
{}

void kb::PageBuilder::set_title(c_str_ref_t label)
{
    title_ = label;
}

void kb::PageBuilder::set_header(c_str_ref_t label)
{
    header_ = label;
}

void kb::PageBuilder::add_block(Block * blk)
{
    body_ += blk->generate().first;
    script_ += blk->generate().second;
}

const kb::str_t kb::PageBuilder::get_page() const
{
    str_t page = "<!DOCTYPE html><html><head>";
    page += "<title>" + title_ + "</title>";
    page += "<style>" + stylesheet_;
    page += "</style></head><body>";
    page += "<h1>" + header_ + "</h1>";
    page += "<div class=\"grid\">" + body_ + "</div>";
    page += "<br><hr><p>PageBuilder 1.2 - Turkin Nikolai</p>";

    page += "<script>";
    page += "const WIDGET_TYPE = Object.freeze({IN: Symbol(\"IN\"), OUT: Symbol(\"OUT\"), INOUT: Symbol(\"INOUT\")});";
    page += "var xml_queue = [];";
    page += "var xhttp = new XMLHttpRequest();";
    page += script_;
    page += "function xml_impl() {";
    page += "if (xml_queue.length !== 0) {";
    page += "const tmp = xml_queue.shift();";
    page += "switch (tmp.type) {";
    page += "case WIDGET_TYPE.INOUT:";
    page += "case WIDGET_TYPE.IN:";
    page += "console.log(tmp.hash, tmp.type, tmp.data, xml_queue.length);";
    page += "const req = tmp.hash + \"?data=\" + tmp.data;";
    page += "xhttp.open(\"GET\", req, true);";
    page += "xhttp.send();";
    page += "break;";
    page += "case WIDGET_TYPE.OUT:";
    page += "console.log(tmp.hash, tmp.type, tmp.data, xml_queue.length);";
    page += "xhttp.onreadystatechange = function() {";
    page += "if (this.readyState == 4 && this.status == 200) {";
    page += "document.getElementById(tmp.hash).innerHTML = this.responseText; } };";
    page += "xhttp.open(\"GET\", tmp.hash, true);";
    page += "xhttp.send();";
    page += "break;";
    page += "} } } setInterval(xml_impl, " + std::to_string(dtime_) + ");";
    page += "</script>";
    page += "</body></html>";
    return page;
}
