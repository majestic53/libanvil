/*
 * float_tag.cpp
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
#include "float_tag.hpp"

/*
 * Float tag assignment operator
 */
float_tag &float_tag::operator=(const float_tag &other) {

	// check for self
	if(this == &other)
		return *this;

	// assign attributes
	name = other.name;
	type = other.type;
	value = other.value;
	return *this;
}

/*
 * Float tag equals operator
 */
bool float_tag::operator==(const generic_tag &other) {

	// check for self
	if(this == &other)
		return true;

	// convert into same type
	const float_tag *other_tag = dynamic_cast<const float_tag *>(&other);
	if(!other_tag)
		return false;

	// check attributes
	return name == other.name
			&& type == other.type
			&& value == other_tag->value;
}

/*
 * Return a float tag's data
 */
std::vector<char> float_tag::get_data(void)  {
	short len;
	const char *name, *name_len, *value;
	std::vector<char> data;

	// form data representation
	len = this->name.size();
	name = this->name.data();
	name_len = reinterpret_cast<const char *>(&len);
	value = reinterpret_cast<const char *>(&this->value);
	data.insert(data.end(), sizeof(type), *reinterpret_cast<const char *>(&type));
	for(unsigned int i = 0; i < sizeof(len); ++i)
		data.insert(data.end(), name_len[i]);
	for(unsigned short i = 0; i < len; ++i)
		data.insert(data.end(), name[i]);
	for(unsigned int i = 0; i < sizeof(this->value); ++i)
		data.insert(data.end(), value[i]);
	return data;
}

/*
 * Return a string representation of a float tag
 */
std::string float_tag::to_string(unsigned int tab) {
	std::stringstream ss;

	// form string representation
	ss << generic_tag::to_string(tab) << ": " << value;
	return ss.str();
}
