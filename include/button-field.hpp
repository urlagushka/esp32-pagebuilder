#ifndef BUTTON_FIELD_HPP
#define BUTTON_FIELD_HPP

#include "widget.hpp"
#include "block.hpp"

namespace kb
{
    using str_t = std::string;
    using str_ref_t = str_t &;
    using c_str_ref_t = const str_t &;

    class ButtonField:
        public Widget
    {
        using Widget::Widget;
        public:
            ButtonField(const Block * src, c_str_ref_t article, c_str_ref_t label);
            const std::pair< str_t, str_t > generate() const override;
        private:
            str_t article_;
    };
}

#endif
