/*
 * byte_array_tag.hpp
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

#ifndef BYTE_ARRAY_TAG_HPP_
#define BYTE_ARRAY_TAG_HPP_

#include <cstdint>
#include <vector>
#include "generic_tag.hpp"

class byte_array_tag : public generic_tag {
public:

	/*
	 * Byte array tag value
	 */
	std::vector<int8_t> value;

	/*
	 * Byte array tag constructor
	 */
	byte_array_tag(void) : generic_tag(BYTE_ARRAY) { return; }

	/*
	 * Byte array tag constructor
	 */
	byte_array_tag(const byte_array_tag &other) : generic_tag(other.name, BYTE_ARRAY), value(other.value) { return; }

	/*
	 * Byte array tag constructor
	 */
	byte_array_tag(std::vector<int8_t> value) : generic_tag(BYTE_ARRAY), value(value) { return; }

	/*
	 * Byte array tag constructor
	 */
	byte_array_tag(const std::string &name, std::vector<int8_t> &value) : generic_tag(name, BYTE_ARRAY), value(value) { return; }

	/*
	 * Byte array tag destructor
	 */
	~byte_array_tag(void) { value.clear(); }

	/*
	 * Byte array tag assignment
	 */
	byte_array_tag &operator=(const byte_array_tag &other);

	/*
	 * Byte array tag equals
	 */
	bool operator==(const byte_array_tag &other);

	/*
	 * Byte array tag not equals
	 */
	bool operator!=(const byte_array_tag &other) { return !(*this == other); }

	/*
	 * Add a byte to a byte array tag
	 */
	void add(int8_t byte) { value.push_back(byte); }

	/*
	 * Returns a byte value at a given index in a byte array tag
	 */
	int8_t at(unsigned int index);

	/*
	 * Returns the empty status of a byte array tag
	 */
	bool empty(void) { return value.empty(); }

	/*
	 * Returns a byte array tags value
	 */
	void *get_value(void) { return &value; }

	/*
	 * Returns the size of a byte array tag
	 */
	unsigned int size(void) { return value.size(); }

	/*
	 * Returns a string representation of a byte array tag
	 */
	std::string to_string(void);
};

#endif
