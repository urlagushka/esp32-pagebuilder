#ifndef LIVE_LABEL_HPP
#define LIVE_LABEL_HPP

#include "widget.hpp"
#include "block.hpp"

namespace kb
{
    using str_t = std::string;
    using str_ref_t = str_t &;
    using c_str_ref_t = const str_t &;

    class LiveLabel:
        public Widget
    {
        using Widget::Widget;
        public:
            LiveLabel(const Block * src, c_str_ref_t label, std::size_t dtime);
            const std::pair< str_t, str_t > generate() const override;
        private:
            std::size_t dtime_;
    };
}

#endif
