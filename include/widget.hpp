#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <string>

namespace kb
{
    using str_t = std::string;
    using str_ref_t = str_t &;
    using c_str_ref_t = const str_t &;

    enum class WIDGET_TYPE
    {
        IN,
        OUT,
        INOUT
    };

    class Widget
    {
        public:
            Widget() = delete;
            Widget(c_str_ref_t src, c_str_ref_t label, WIDGET_TYPE wtype);
            virtual ~Widget() = default;

            c_str_ref_t get_hash() const;
            const WIDGET_TYPE & get_type() const;

            virtual const std::pair< str_t, str_t > generate() const = 0;
        protected:
            str_t hash_;
            str_t label_;

            WIDGET_TYPE type_;
    };
}

#endif
