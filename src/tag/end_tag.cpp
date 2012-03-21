/*
 * end_tag.cpp
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

#include "end_tag.hpp"

/*
 * End tag assignment operator
 */
end_tag &end_tag::operator=(const end_tag &other) {

	// check for self
	if(this == &other)
		return *this;

	// assign attributes
	name = other.name;
	type = other.type;
	return *this;
}

/*
 * End tag equals operator
 */
bool end_tag::operator==(const generic_tag &other) {

	// check for self
	if(this == &other)
		return true;

	// convert into same type
	const end_tag *other_tag = dynamic_cast<const end_tag *>(&other);
	if(!other_tag)
		return false;

	// check attributes
	return name == other.name
			&& type == other.type;
}

/*
 * Return a end tag's data
 */
std::vector<char> end_tag::get_data(void)  {
	std::vector<char> data;

	// form data representation
	data.insert(data.end(), 0);
	return data;
}
