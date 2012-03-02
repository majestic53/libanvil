/*
 * generic_tag.hpp
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

#ifndef GENERIC_TAG_HPP_
#define GENERIC_TAG_HPP_

#include <string>

class generic_tag {
public:

	/*
	 * Tag name
	 */
	std::string name;

	/*
	 * Tag type
	 */
	char type;

	/*
	 * Supported tag types
	 */
	enum TYPE { END, BYTE, SHORT, INT, LONG, FLOAT, DOUBLE, BYTE_ARRAY, STRING, LIST, COMPOUND, INT_ARRAY };

	/*
	 * Generic tag constructor
	 */
	generic_tag(void) : type(END) { return; }

	/*
	 * Generic tag constructor
	 */
	generic_tag(const generic_tag &other) : name(other.name), type(other.type) { return; }

	/*
	 * Generic tag constructor
	 */
	generic_tag(char type) : type(END) { return; }

	/*
	 * Generic tag constructor
	 */
	generic_tag(const std::string &name, char type) : name(name), type(type) { return; }

	/*
	 * Generic tag destructor
	 */
	virtual ~generic_tag(void) { return; }

	/*
	 * Generic tag assignment
	 */
	generic_tag &operator=(const generic_tag &other);

	/*
	 * Generic tag equals
	 */
	bool operator==(const generic_tag &other);

	/*
	 * Generic tag not equals
	 */
	bool operator!=(const generic_tag &other) { return !(*this == other); }

	/*
	 * Returns a generic tags name
	 */
	std::string get_name(void) { return name; }

	/*
	 * Returns a generic tags type
	 */
	char get_type(void) { return type; }

	/*
	 * Returns a generic tags value;
	 */
	virtual void *get_value(void) { return this->get_value(); }

	/*
	 * Returns a string representation of a generic tag
	 */
	virtual std::string to_string(void);

	/*
	 * Returns a string representatrion of a tag type
	 */
	static std::string type_to_string(char type);
};

#endif
