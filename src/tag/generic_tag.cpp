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
 * Generic tag assignment
 */
generic_tag &generic_tag::operator=(const generic_tag &other) {

	// check for self
	if(this == &other)
		return *this;

	// set attributes
	type = other.type;
	name = other.name;
	return *this;
}

/*
 * Generic tag equals
 */
bool generic_tag::operator==(const generic_tag &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	return type == other.type
			&& name == other.name;
}

/*
 * Returns a string representation of a generic tag
 */
std::string generic_tag::to_string(void) {
	std::string out;

	// create string representation
	out.append(type_to_string(type));
	if(!name.empty())
		out.append(": " + name);
	return out;
}

/*
 * Returns a string representatrion of a tag type
 */
std::string generic_tag::type_to_string(char type) {
	std::string out("[");
	switch(type) {
		case END: out.append("END");
			break;
		case BYTE: out.append("BYTE");
			break;
		case SHORT: out.append("SHORT");
			break;
		case INT: out.append("INT");
			break;
		case LONG: out.append("LONG");
			break;
		case FLOAT: out.append("FLOAT");
			break;
		case DOUBLE: out.append("DOUBLE");
			break;
		case BYTE_ARRAY: out.append("BYTE ARRAY");
			break;
		case STRING: out.append("STRING");
			break;
		case LIST: out.append("LIST");
			break;
		case COMPOUND: out.append("COMPOUND");
			break;
		case INT_ARRAY: out.append("INT ARRAY");
			break;
		default: out.append("UNKNOWN");
			break;
	}
	out.append("]");
	return out;
}
