/*
 * short_tag.hpp
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

#ifndef SHORT_TAG_HPP_
#define SHORT_TAG_HPP_

#include "generic_tag.hpp"

class short_tag : public generic_tag {
public:

	/*
	 * Short tag value
	 */
	int16_t value;

	/*
	 * Short tag constructor
	 */
	short_tag(void) : generic_tag(SHORT), value(0) { return; }

	/*
	 * Short tag constructor
	 */
	short_tag(const short_tag &other) : generic_tag(other.name, SHORT), value(other.value) { return; }

	/*
	 * Short tag constructor
	 */
	short_tag(int16_t value) : generic_tag(SHORT), value(value) { return; }

	/*
	 * Short tag constructor
	 */
	short_tag(const std::string &name, int16_t value) : generic_tag(name, SHORT), value(value) { return; }

	/*
	 * Short tag destructor
	 */
	~short_tag(void) { return; }

	/*
	 * Short tag assignment
	 */
	short_tag &operator=(const short_tag &other);

	/*
	 * Short tag equals
	 */
	bool operator==(const short_tag &other);

	/*
	 * Short tag not equals
	 */
	bool operator!=(const short_tag &other) { return !(*this == other); }

	/*
	 * Returns a short tags value
	 */
	void *get_value(void) { return &value; }

	/*
	 * Returns a string representation of a short tag
	 */
	std::string to_string(void);
};

#endif
