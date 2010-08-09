/* Floating point representation utility library
 * Copyright (C) 2010 Mike Miller <mtmiller@ieee.org>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

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
