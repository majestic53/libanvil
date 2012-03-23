/*
 * list_tag.cpp
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
#include "../byte_stream.hpp"
#include "compound_tag.hpp"
#include "end_tag.hpp"

/*
 * Compound tag assignment operator
 */
compound_tag &compound_tag::operator=(const compound_tag &other) {

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
 * Compound tag equals operator
 */
bool compound_tag::operator==(const generic_tag &other) {

	// check for self
	if(this == &other)
		return true;

	// convert into same type
	const compound_tag *other_tag = dynamic_cast<const compound_tag *>(&other);
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
 * Return a compound tag's data
 */
std::vector<char> compound_tag::get_data(bool list_ele)  {
	end_tag end;
	byte_stream stream(byte_stream::SWAP_ENDIAN);

	// form data representation
	if(!list_ele) {
		stream << (char) type;
		stream << (short) name.size();
		stream << name;
	}
	for(unsigned int i = 0; i < value.size(); ++i)
		stream << value.at(i)->get_data(false);
	stream << end.get_data(false);
	return stream.vbuf();
}

/*
 * Return a string representation of a compound tag
 */
std::string compound_tag::to_string(unsigned int tab) {
	std::stringstream ss;

	// form string representation
	ss << generic_tag::to_string(tab) << " (" << value.size() << ") {";
	if(!value.empty()) {
		ss << std::endl;
		for(unsigned int i = 0; i < value.size(); ++i)
			ss << value.at(i)->to_string(tab + 1) << std::endl;
		generic_tag::append_tabs(tab, ss);
	}
	ss << "}";
	return ss.str();
}
