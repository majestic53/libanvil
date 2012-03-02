/*
 * int_tag.hpp
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

#ifndef INT_TAG_HPP_
#define INT_TAG_HPP_

#include <cstdint>
#include "generic_tag.hpp"

class int_tag : public generic_tag {
public:

	/*
	 * Int tag value
	 */
	int32_t value;

	/*
	 * Int tag constructor
	 */
	int_tag(void) : generic_tag(INT), value(0) { return; }

	/*
	 * Int tag constructor
	 */
	int_tag(const int_tag &other) : generic_tag(other.name, INT), value(other.value) { return; }

	/*
	 * Int tag constructor
	 */
	int_tag(int32_t value) : generic_tag(INT), value(value) { return; }

	/*
	 * Int tag constructor
	 */
	int_tag(const std::string &name, int32_t value) : generic_tag(name, INT), value(value) { return; }

	/*
	 * Int tag destructor
	 */
	~int_tag(void) { return; }

	/*
	 * Int tag assignment
	 */
	int_tag &operator=(const int_tag &other);

	/*
	 * Int tag equals
	 */
	bool operator==(const int_tag &other);

	/*
	 * Int tag not equals
	 */
	bool operator!=(const int_tag &other) { return !(*this == other); }

	/*
	 * Returns an int tags value
	 */
	void *get_value(void) { return &value; }

	/*
	 * Returns a string representation of an int tag
	 */
	std::string to_string(void);
};

#endif
