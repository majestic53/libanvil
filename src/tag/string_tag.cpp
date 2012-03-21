/*
 * string_tag.cpp
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
#include "string_tag.hpp"

/*
 * String tag assignment operator
 */
string_tag &string_tag::operator=(const string_tag &other) {

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
 * String tag equals operator
 */
bool string_tag::operator==(const generic_tag &other) {

	// check for self
	if(this == &other)
		return true;

	// convert into same type
	const string_tag *other_tag = dynamic_cast<const string_tag *>(&other);
	if(!other_tag)
		return false;

	// check attributes
	return name == other.name
			&& type == other.type
			&& value == other_tag->value;
}

/*
 * Return a string tag's data
 */
std::vector<char> string_tag::get_data(void)  {
	short len, v_len;
	const char *name, *name_len, *value, *value_len;
	std::vector<char> data;

	// form data representation
	len = this->name.size();
	v_len = this->value.size();
	name = this->name.data();
	name_len = reinterpret_cast<const char *>(&len);
	value = this->value.data();
	value_len = reinterpret_cast<const char *>(&v_len);
	data.insert(data.end(), sizeof(type), *reinterpret_cast<const char *>(&type));
	for(unsigned int i = 0; i < sizeof(len); ++i)
		data.insert(data.end(), name_len[i]);
	for(unsigned short i = 0; i < len; ++i)
		data.insert(data.end(), name[i]);
	for(unsigned int i = 0; i < sizeof(v_len); ++i)
		data.insert(data.end(), value_len[i]);
	for(unsigned int i = 0; i < this->value.size(); ++i)
		data.insert(data.end(), value[i]);
	return data;
}

/*
 * Return a string representation of a string tag
 */
std::string string_tag::to_string(unsigned int tab) {
	std::stringstream ss;

	// form string representation
	ss << generic_tag::to_string(tab) << ": " << value;
	return ss.str();
}
