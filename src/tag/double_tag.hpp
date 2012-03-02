/*
 * double_tag.hpp
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

#ifndef DOUBLE_TAG_HPP_
#define DOUBLE_TAG_HPP_

#include "generic_tag.hpp"

class double_tag : public generic_tag {
public:

	/*
	 * Double tag value
	 */
	double value;

	/*
	 * Double tag constructor
	 */
	double_tag(void) : generic_tag(DOUBLE), value(0) { return; }

	/*
	 * Double tag constructor
	 */
	double_tag(const double_tag &other) : generic_tag(other.name, DOUBLE), value(other.value) { return; }

	/*
	 * Double tag constructor
	 */
	double_tag(double value) : generic_tag(DOUBLE), value(value) { return; }

	/*
	 * Double tag constructor
	 */
	double_tag(const std::string &name, double value) : generic_tag(name, DOUBLE), value(value) { return; }

	/*
	 * Double tag destructor
	 */
	~double_tag(void) { return; }

	/*
	 * Double tag assignment
	 */
	double_tag &operator=(const double_tag &other);

	/*
	 * Double tag equals
	 */
	bool operator==(const double_tag &other);

	/*
	 * Double tag not equals
	 */
	bool operator!=(const double_tag &other) { return !(*this == other); }

	/*
	 * Returns a double tags value
	 */
	void *get_value(void) { return &value; }

	/*
	 * Returns a string representation of a double tag
	 */
	std::string to_string(void);
};

#endif
