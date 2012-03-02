/*
 * compound_tag.hpp
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

#ifndef COMPOUND_TAG_HPP_
#define COMPOUND_TAG_HPP_

#include <vector>
#include "generic_tag.hpp"

class compound_tag : public generic_tag {
public:

	/*
	 * Compound tag value
	 */
	std::vector<generic_tag *> value;

	/*
	 * Compound tag constructor
	 */
	compound_tag(void) : generic_tag(COMPOUND) { return; }

	/*
	 * Compound tag constructor
	 */
	compound_tag(const compound_tag &other) : generic_tag(other.name, COMPOUND), value(other.value) { return; }

	/*
	 * Compound tag constructor
	 */
	compound_tag(std::vector<generic_tag *> value) : generic_tag(COMPOUND), value(value) { return; }

	/*
	 * Compound tag constructor
	 */
	compound_tag(const std::string &name, std::vector<generic_tag *> &value) : generic_tag(name, COMPOUND), value(value) { return; }

	/*
	 * Compound tag destructor
	 */
	~compound_tag(void) { value.clear(); }

	/*
	 * Compound tag assignment
	 */
	compound_tag &operator=(const compound_tag &other);

	/*
	 * Compound tag equals
	 */
	bool operator==(const compound_tag &other);

	/*
	 * Compound tag not equals
	 */
	bool operator!=(const compound_tag &other) { return !(*this == other); }

	/*
	 * Add a tag to a compound tag
	 */
	void add(generic_tag *tag) { value.push_back(tag); }

	/*
	 * Returns a tag at a given index in a compound tag
	 */
	generic_tag *at(unsigned int index);

	/*
	 * Returns the empty status of a compound tag
	 */
	bool empty(void) { return value.empty(); }

	/*
	 * Returns a compound tag value
	 */
	void *get_value(void) { return &value; }

	/*
	 * Returns the size of a compound tag
	 */
	unsigned int size(void) { return value.size(); }

	/*
	 * Returns a string representation of a compound tag
	 */
	std::string to_string(void);
};

#endif
