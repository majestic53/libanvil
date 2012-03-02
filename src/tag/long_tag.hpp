/*
 * long_tag.hpp
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

#ifndef LONG_TAG_HPP_
#define LONG_TAG_HPP_

#include "generic_tag.hpp"

class long_tag : public generic_tag {
public:

	/*
	 * Long tag value
	 */
	int64_t value;

	/*
	 * Long tag constructor
	 */
	long_tag(void) : generic_tag(LONG), value(0) { return; }

	/*
	 * Long tag constructor
	 */
	long_tag(const long_tag &other) : generic_tag(other.name, LONG), value(other.value) { return; }

	/*
	 * Long tag constructor
	 */
	long_tag(int64_t value) : generic_tag(LONG), value(value) { return; }

	/*
	 * Long tag constructor
	 */
	long_tag(const std::string &name, int64_t value) : generic_tag(name, LONG), value(value) { return; }

	/*
	 * Long tag destructor
	 */
	~long_tag(void) { return; }

	/*
	 * Long tag assignment
	 */
	long_tag &operator=(const long_tag &other);

	/*
	 * Long tag equals
	 */
	bool operator==(const long_tag &other);

	/*
	 * Long tag not equals
	 */
	bool operator!=(const long_tag &other) { return !(*this == other); }

	/*
	 * Returns a long tags value
	 */
	void *get_value(void) { return &value; }

	/*
	 * Returns a string representation of a long tag
	 */
	std::string to_string(void);
};

#endif
