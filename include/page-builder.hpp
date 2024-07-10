#ifndef PAGE_BUILDER_HPP
#define PAGE_BUILDER_HPP

#include <string>

#include "block.hpp"

namespace kb
{
    using str_t = std::string;
    using str_ref_t = str_t &;
    using c_str_ref_t = const str_t &;

    class PageBuilder
    {
        public:
            PageBuilder() = delete;
            PageBuilder(c_str_ref_t stylesheet);
            
            void set_title(c_str_ref_t label);
            void set_header(c_str_ref_t label);
            
            void add_block(Block * blk);
            
            const str_t get_page() const;
            
        private:
            str_t title_;
            str_t header_;
            str_t stylesheet_;
            str_t body_;
            str_t script_;
    };
}

#endif
