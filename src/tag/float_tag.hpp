/*
 * float_tag.hpp
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

#ifndef FLOAT_TAG_HPP_
#define FLOAT_TAG_HPP_

#include "generic_tag.hpp"

class float_tag : public generic_tag {
public:

	/*
	 * Float tag value
	 */
	float value;

	/*
	 * Float tag constructor
	 */
	float_tag(void) : generic_tag(FLOAT), value(0) { return; }

	/*
	 * Float tag constructor
	 */
	float_tag(const float_tag &other) : generic_tag(other.name, FLOAT), value(other.value) { return; }

	/*
	 * Float tag constructor
	 */
	float_tag(float value) : generic_tag(FLOAT), value(value) { return; }

	/*
	 * Float tag constructor
	 */
	float_tag(const std::string &name, float value) : generic_tag(name, FLOAT), value(value) { return; }

	/*
	 * Float tag destructor
	 */
	~float_tag(void) { return; }

	/*
	 * Float tag assignment
	 */
	float_tag &operator=(const float_tag &other);

	/*
	 * Float tag equals
	 */
	bool operator==(const float_tag &other);

	/*
	 * Float tag not equals
	 */
	bool operator!=(const float_tag &other) { return !(*this == other); }

	/*
	 * Returns a float tags value
	 */
	void *get_value(void) { return &value; }

	/*
	 * Returns a string representation of a float tag
	 */
	std::string to_string(void);
};

#endif
