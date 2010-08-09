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

#include <iostream>
#include "floating_point_representation.hpp"
#include "floating_point_representation_io.hpp"

int main(int argc, char* argv[]) {
    using namespace std;

    int value = 0;
    if (argc > 1) {
        value = atoi(argv[1]);
    }

    floating_point_representation fbits;
    cout << fbits << endl;
    fbits = float(value);
    cout << fbits << endl;
    fbits = double(value);
    cout << fbits << endl;
    fbits = (long double)(value);
    cout << fbits << endl;
}
