/*
 * int_array_tag.hpp
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

#ifndef INT_ARRAY_TAG_HPP_
#define INT_ARRAY_TAG_HPP_

#include <cstdint>
#include <vector>
#include "generic_tag.hpp"

class int_array_tag : public generic_tag {
public:

	/*
	 * Int array tag value
	 */
	std::vector<int32_t> value;

	/*
	 * Byte array tag constructor
	 */
	int_array_tag(void) : generic_tag(INT_ARRAY) { return; }

	/*
	 * Int array tag constructor
	 */
	int_array_tag(const int_array_tag &other) : generic_tag(other.name, INT_ARRAY), value(other.value) { return; }

	/*
	 * Int array tag constructor
	 */
	int_array_tag(std::vector<int32_t> value) : generic_tag(INT_ARRAY), value(value) { return; }

	/*
	 * Int array tag constructor
	 */
	int_array_tag(const std::string &name, std::vector<int32_t> &value) : generic_tag(name, INT_ARRAY), value(value) { return; }

	/*
	 * Int array tag destructor
	 */
	~int_array_tag(void) { value.clear(); }

	/*
	 * Int array tag assignment
	 */
	int_array_tag &operator=(const int_array_tag &other);

	/*
	 * Int array tag equals
	 */
	bool operator==(const int_array_tag &other);

	/*
	 * Int array tag not equals
	 */
	bool operator!=(const int_array_tag &other) { return !(*this == other); }

	/*
	 * Add a int to a int array tag
	 */
	void add(int32_t val) { value.push_back(val); }

	/*
	 * Returns an int value at a given index in a int array tag
	 */
	int32_t at(unsigned int index);

	/*
	 * Returns the empty status of a int array tag
	 */
	bool empty(void) { return value.empty(); }

	/*
	 * Returns an int array tags value
	 */
	void *get_value(void) { return &value; }

	/*
	 * Returns the size of an int array tag
	 */
	unsigned int size(void) { return value.size(); }

	/*
	 * Returns a string representation of a int array tag
	 */
	std::string to_string(void);
};

#endif
