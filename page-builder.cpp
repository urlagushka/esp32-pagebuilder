#include "page-builder.hpp"

kb::PageBuilder::PageBuilder(c_str_ref_t stylesheet):
    title_(""),
    header_(""),
    stylesheet_(stylesheet),
    body_(""),
    script_("")
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
    page += "<br><hr><p>PageBuilder 1.0 - Turkin Nikolai</p>";
    page += "<script>" + script_ + "</script>";
    page += "</body></html>";
    return page;
}
