#include "widget.hpp"

kb::Widget::Widget(c_str_ref_t src, c_str_ref_t label, WIDGET_TYPE wtype):
    hash_(""),
    label_(label),
    type_(wtype)
{
    hash_ = "T" + std::to_string(std::hash< str_t >{}(src + label));
}

kb::c_str_ref_t kb::Widget::get_hash() const
{
    return hash_;
}

const kb::WIDGET_TYPE & kb::Widget::get_type() const
{
    return type_;
}
