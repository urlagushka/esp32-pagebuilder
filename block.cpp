#include "block.hpp"

kb::Block::Block(c_str_ref_t label, c_str_ref_t subinfo):
    label_(label),
    subinfo_(subinfo)
{}

kb::c_str_ref_t kb::Block::get_label() const
{
    return label_;
}

void kb::Block::add_widget(Widget * wget)
{
    wgets_.push_back(wget);
}

const std::pair< kb::str_t, kb::str_t > kb::Block::generate() const
{
    str_t incl_body = "";
    str_t incl_script = "";
    for (auto wget: wgets_)
    {
        auto resp = wget->generate();
        incl_body += resp.first;
        incl_script += resp.second;
    }

    str_t body_part = "<div class=\"block\"><div class=\"top\"><p style=\"margin: 5px\" >";
    body_part += label_ + "</p></div><div class=\"mid\">";
    body_part += incl_body;
    body_part += "</div><div class=\"bot\">" + subinfo_ + "</div></div>";
    
    str_t script_part = incl_script;

    return std::make_pair(body_part, script_part);
}
