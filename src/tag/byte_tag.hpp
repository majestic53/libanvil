/*
 * byte_tag.hpp
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

#ifndef BYTE_TAG_HPP_
#define BYTE_TAG_HPP_

#include <cstdint>
#include "generic_tag.hpp"

class byte_tag : public generic_tag {
public:

	/*
	 * Byte tag value
	 */
	int8_t value;

	/*
	 * Byte tag constructor
	 */
	byte_tag(void) : generic_tag(BYTE), value(0) { return; }

	/*
	 * Byte tag constructor
	 */
	byte_tag(const byte_tag &other) : generic_tag(other.name, BYTE), value(other.value) { return; }

	/*
	 * Byte tag constructor
	 */
	byte_tag(int8_t value) : generic_tag(BYTE), value(value) { return; }

	/*
	 * Byte tag constructor
	 */
	byte_tag(const std::string &name, int8_t value) : generic_tag(name, BYTE), value(value) { return; }

	/*
	 * Byte tag destructor
	 */
	~byte_tag(void) { return; }

	/*
	 * Byte tag assignment
	 */
	byte_tag &operator=(const byte_tag &other);

	/*
	 * Byte tag equals
	 */
	bool operator==(const byte_tag &other);

	/*
	 * Byte tag not equals
	 */
	bool operator!=(const byte_tag &other) { return !(*this == other); }

	/*
	 * Returns a byte tags value
	 */
	void *get_value(void) { return &value; }

	/*
	 * Returns a string representation of a byte tag
	 */
	std::string to_string(void);
};

#endif
