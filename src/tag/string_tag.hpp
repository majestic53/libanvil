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
#include <vector>
#include "generic_tag.hpp"

class string_tag : public generic_tag {
private:

	/*
	 * String tag value
	 */
	std::string value;

public:

	/*
	 * String tag constructor
	 */
	string_tag(void) : generic_tag(STRING) { return; }

	/*
	 * String tag constructor
	 */
	string_tag(const string_tag &other) : generic_tag(other.name, STRING) { value = other.value; };

	/*
	 * String tag constructor
	 */
	string_tag(const std::string &value) : generic_tag(STRING) { this->value = value; }

	/*
	 * String tag constructor
	 */
	string_tag(const std::string &name, const std::string &value) : generic_tag(name, STRING) { this->value = value; }

	/*
	 * String tag destructor
	 */
	virtual ~string_tag(void) { return; }

	/*
	 * String tag assignment operator
	 */
	string_tag &operator=(const string_tag &other);

	/*
	 * String tag equals operator
	 */
	bool operator==(const generic_tag &other);

	/*
	 * String tag not-equals operator
	 */
	bool operator!=(const generic_tag &other) { return !(*this == other); }

	/*
	 * Return a string tag's data
	 */
	std::vector<char> get_data(bool list_ele);

	/*
	 * Return a string tag's value
	 */
	std::string &get_value(void) { return value; }

	/*
	 * Set a string tag's value
	 */
	void set_value(std::string &value) { this->value = value; }

	/*
	 * Return a string representation of a string tag
	 */
	std::string to_string(unsigned int tab);
};

#endif
