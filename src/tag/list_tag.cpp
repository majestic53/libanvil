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
#include "byte_array_tag.hpp"
#include "byte_tag.hpp"
#include "compound_tag.hpp"
#include "double_tag.hpp"
#include "end_tag.hpp"
#include "float_tag.hpp"
#include "generic_tag.hpp"
#include "int_tag.hpp"
#include "list_tag.hpp"
#include "long_tag.hpp"
#include "short_tag.hpp"
#include "string_tag.hpp"

/*
 * List tag assignment
 */
list_tag &list_tag::operator=(const list_tag &other) {

	// check for self
	if(this == &other)
		return *this;

	// set attributes
	generic_tag::operator =(other);
	value.assign(other.value.begin(), other.value.end());
	return *this;
}

/*
 * List tag equals
 */
bool list_tag::operator==(const list_tag &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	if(generic_tag::operator !=(other)
			|| value.size() != other.value.size())
		return false;
	for(unsigned int i = 0; i < value.size(); ++i) {
		if(value.at(i)->get_type() != other.value.at(i)->get_type())
			return false;
		switch(value.at(i)->get_type()) {
			case generic_tag::COMPOUND:
				if((compound_tag) *static_cast<compound_tag *>(value.at(i)) != *static_cast<compound_tag *>(other.value.at(i)))
					return false;
				break;
			case generic_tag::LIST:
				if(*static_cast<list_tag *>(value.at(i)) != *static_cast<list_tag *>(other.value.at(i)))
					return false;
				break;
			case generic_tag::BYTE_ARRAY:
				if(*static_cast<byte_array_tag *>(value.at(i)) != *static_cast<byte_array_tag *>(other.value.at(i)))
					return false;
				break;
			case generic_tag::BYTE:
				if(*static_cast<byte_tag *>(value.at(i)) != *static_cast<byte_tag *>(other.value.at(i)))
					return false;
				break;
			case generic_tag::DOUBLE:
				if(*static_cast<double_tag *>(value.at(i)) != *static_cast<double_tag *>(other.value.at(i)))
					return false;
				break;
			case generic_tag::END:
				if(*static_cast<end_tag *>(value.at(i)) != *static_cast<end_tag *>(other.value.at(i)))
					return false;
				break;
			case generic_tag::FLOAT:
				if(*static_cast<float_tag *>(value.at(i)) != *static_cast<float_tag *>(other.value.at(i)))
					return false;
				break;
			case generic_tag::INT:
				if(*static_cast<int_tag *>(value.at(i)) != *static_cast<int_tag *>(other.value.at(i)))
					return false;
				break;
			case generic_tag::LONG:
				if(*static_cast<long_tag *>(value.at(i)) != *static_cast<long_tag *>(other.value.at(i)))
					return false;
				break;
			case generic_tag::SHORT:
				if(*static_cast<short_tag *>(value.at(i)) != *static_cast<short_tag *>(other.value.at(i)))
					return false;
				break;
			case generic_tag::STRING:
				if(*static_cast<string_tag *>(value.at(i)) != *static_cast<string_tag *>(other.value.at(i)))
					return false;
				break;
			default:
				return false;
				break;
		}
	}
	return true;
}

/*
 * Returns a tag at a given index in a list tag
 */
generic_tag *list_tag::at(unsigned int index) {
	if(index >= value.size())
		return NULL;
	return value.at(index);
}

/*
 * Returns a string representation of a list tag
 */
std::string list_tag::to_string(void) {
	std::stringstream ss;

	// create string representation
	ss << generic_tag::type_to_string(type);
	if(!name.empty())
		ss << " " << name;
	ss << " (" << value.size() << ")";
	if(!value.empty()) {
		ss << " {" << std::endl;
		for(unsigned int i = 0; i < value.size(); ++i)
			ss << "\t" << value.at(i)->to_string() << std::endl;
		ss << "}";
	}
	return ss.str();
}
