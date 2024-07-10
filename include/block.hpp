#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <string>
#include <vector>

#include "widget.hpp"

namespace kb
{
    using str_t = std::string;
    using str_ref_t = str_t &;
    using c_str_ref_t = const str_t &;

    class Block
    {
        public:
            Block(c_str_ref_t label, c_str_ref_t subinfo);
            
            c_str_ref_t get_label() const;
            void add_widget(Widget * wget);
            const std::pair< str_t, str_t > generate() const;

        private:
            str_t label_;
            str_t subinfo_;
            std::vector< Widget * > wgets_;
    };
}

#endif
