#ifndef FLOATING_POINT_REPRESENTATION_IO_HPP
#define FLOATING_POINT_REPRESENTATION_IO_HPP

#include <sstream>
#include "floating_point_representation.hpp"

template<typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, const floating_point_representation& r)
{
    const char sep = ' ';
    std::ostringstream s;
    s.flags(os.flags());
    s.imbue(os.getloc());
    s.precision(os.precision());

    if (r.size()) {
        int i = r.mantissa_bits() + r.exponent_bits();
        s << r.bitchar(i);
        s << sep;
        while (i > r.mantissa_bits()) { s << r.bitchar(--i); }
        s << sep;
        while (i > 0) { s << r.bitchar(--i); }
    }
    return os << s.str();
}

#endif // FLOATING_POINT_REPRESENTATION_IO_HPP
