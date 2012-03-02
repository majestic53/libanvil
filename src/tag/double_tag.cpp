/*
 * double_tag.cpp
 * Copyright (C) 2012 David Jolly
 * ----------------------
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sstream>
#include "double_tag.hpp"

/*
 * Double tag assignment
 */
double_tag &double_tag::operator=(const double_tag &other) {

	// check for self
	if(this == &other)
		return *this;

	// set attributes
	generic_tag::operator =(other);
	value = other.value;
	return *this;
}

/*
 * Double tag equals
 */
bool double_tag::operator==(const double_tag &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	return generic_tag::operator ==(other)
			&& value == other.value;
}

/*
 * Returns a string representation of a double tag
 */
std::string double_tag::to_string(void) {
	std::stringstream ss;

	// create string representation
	ss << generic_tag::type_to_string(type);
	if(!name.empty())
		ss << " " << name;
	ss << ": " << value;
	return ss.str();
}
