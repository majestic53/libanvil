/*
 * string_tag.hpp
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

#ifndef STRING_TAG_HPP_
#define STRING_TAG_HPP_

#include <string>
#include "generic_tag.hpp"

class string_tag : public generic_tag {
public:

	/*
	 * String tag value
	 */
	std::string value;

	/*
	 * String tag constructor
	 */
	string_tag(void) : generic_tag(STRING) { return; }

	/*
	 * String tag constructor
	 */
	string_tag(const string_tag &other) : generic_tag(other.name, STRING), value(other.value) { return; }

	/*
	 * String tag constructor
	 */
	string_tag(const std::string &value) : generic_tag(STRING), value(value) { return; }

	/*
	 * String tag constructor
	 */
	string_tag(const std::string &name, const std::string &value) : generic_tag(name, STRING), value(value) { return; }

	/*
	 * String tag destructor
	 */
	~string_tag(void) { return; }

	/*
	 * String tag assignment
	 */
	string_tag &operator=(const string_tag &other);

	/*
	 * String tag equals
	 */
	bool operator==(const string_tag &other);

	/*
	 * String tag not equals
	 */
	bool operator!=(const string_tag &other) { return !(*this == other); }

	/*
	 * Returns a string tags value
	 */
	void *get_value(void) { return &value; }

	/*
	 * Returns a string representation of a string tag
	 */
	std::string to_string(void);
};

#endif
