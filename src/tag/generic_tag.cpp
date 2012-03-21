/*
 * generic_tag.cpp
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

#include "generic_tag.hpp"

/*
 * Generic tag assignment operator
 */
generic_tag &generic_tag::operator=(const generic_tag &other) {

	// check for self
	if(this == &other)
		return *this;

	// assign attributes
	name = other.name;
	type = other.type;
	return *this;
}

/*
 * Generic tag equals operator
 */
bool generic_tag::operator==(const generic_tag &other) {

	// check if self
	if(this == &other)
		return true;

	// check attributes
	return name == other.name
			&& type == other.type;
}

/*
 * Append a certain number of tabs to a given stringstream
 */
void generic_tag::append_tabs(unsigned int tab, std::stringstream &ss) {
	for(unsigned int i = 0; i < tab; ++i)
		ss << "\t";
}

/*
 * Return a string representation of a generic tag
 */
std::string generic_tag::to_string(unsigned int tab) {
	std::stringstream ss;

	// form a string representation
	append_tabs(tab, ss);
	ss << type_to_string(type);
	if(!name.empty())
		ss << " " << name;
	return ss.str();
}

/*
 * Return a string representation of a tag type
 */
std::string generic_tag::type_to_string(unsigned char type) {
	std::stringstream ss;

	// form a string representation
	ss << "[";
	switch(type) {
		case END: ss << "END";
			break;
		case BYTE: ss << "BYTE";
			break;
		case SHORT: ss << "SHORT";
			break;
		case INT: ss << "INT";
			break;
		case LONG: ss << "LONG";
			break;
		case FLOAT: ss << "FLOAT";
			break;
		case DOUBLE: ss << "DOUBLE";
			break;
		case BYTE_ARRAY: ss << "BYTE ARRAY";
			break;
		case STRING: ss << "STRING";
			break;
		case LIST: ss << "LIST";
			break;
		case COMPOUND: ss << "COMPOUND";
			break;
		case INT_ARRAY: ss << "INT ARRAY";
			break;
		default: ss << "UNKNOWN";
			break;
	}
	ss << "]";
	return ss.str();
}
