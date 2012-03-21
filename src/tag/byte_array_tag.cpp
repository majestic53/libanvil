/*
 * byte_array_tag.cpp
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
#include "byte_array_tag.hpp"

/*
 * Byte array tag assignment operator
 */
byte_array_tag &byte_array_tag::operator=(const byte_array_tag &other) {

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
 * Byte array tag equals operator
 */
bool byte_array_tag::operator==(const generic_tag &other) {

	// check for self
	if(this == &other)
		return true;

	// convert into same type
	const byte_array_tag *other_tag = dynamic_cast<const byte_array_tag *>(&other);
	if(!other_tag)
		return false;

	// check attributes
	if(name != other.name
			|| type != other.type
			|| value.size() != other_tag->value.size())
		return false;
	for(unsigned int i = 0; i < value.size(); ++i)
		if(value.at(i) != other_tag->value.at(i))
			return false;
	return true;
}

/*
 * Return a byte array tag's data
 */
std::vector<char> byte_array_tag::get_data(void)  {
	short len;
	unsigned int array_len;
	const char *name, *name_len, *array_len_value;
	std::vector<char> data;

	// form data representation
	len = this->name.size();
	name = this->name.data();
	array_len = this->value.size();
	name_len = reinterpret_cast<const char *>(&len);
	array_len_value = reinterpret_cast<const char *>(&array_len);
	data.insert(data.end(), sizeof(type), *reinterpret_cast<const char *>(&type));
	for(unsigned int i = 0; i < sizeof(len); ++i)
		data.insert(data.end(), name_len[i]);
	for(unsigned short i = 0; i < len; ++i)
		data.insert(data.end(), name[i]);
	for(unsigned int i = 0; i < sizeof(array_len); ++i)
		data.insert(data.end(), array_len_value[i]);
	for(unsigned int i = 0; i < array_len; ++i)
		data.insert(data.end(), value[i]);
	return data;
}

/*
 * Return a string representation of a byte array tag
 */
std::string byte_array_tag::to_string(unsigned int tab) {
	std::stringstream ss;

	// form string representation
	ss << generic_tag::to_string(tab);
	if(!value.empty()) {
		ss << " (" << value.size() << ") { ";
		for(unsigned int i = 0; i < value.size(); ++i)
			ss << (int) value.at(i) << ", ";
		ss << "}";
	}
	return ss.str();
}
