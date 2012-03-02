/*
 * list_tag.hpp
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

#ifndef LIST_TAG_HPP_
#define LIST_TAG_HPP_

#include <vector>
#include "generic_tag.hpp"

class list_tag : public generic_tag {
public:

	/*
	 * List tag value
	 */
	std::vector<generic_tag *> value;

	/*
	 * List tag constructor
	 */
	list_tag(void) : generic_tag(LIST) { return; }

	/*
	 * List tag constructor
	 */
	list_tag(const list_tag &other) : generic_tag(other.name, LIST), value(other.value) { return; }

	/*
	 * List tag constructor
	 */
	list_tag(std::vector<generic_tag *> value) : generic_tag(LIST), value(value) { return; }

	/*
	 * List tag constructor
	 */
	list_tag(const std::string &name, std::vector<generic_tag *> &value) : generic_tag(name, LIST), value(value) { return; }

	/*
	 * List tag destructor
	 */
	~list_tag(void) { value.clear(); }

	/*
	 * List tag assignment
	 */
	list_tag &operator=(const list_tag &other);

	/*
	 * List tag equals
	 */
	bool operator==(const list_tag &other);

	/*
	 * List tag not equals
	 */
	bool operator!=(const list_tag &other) { return !(*this == other); }

	/*
	 * Add a tag to a list tag
	 */
	void add(generic_tag *tag) { value.push_back(tag); }

	/*
	 * Returns a tag at a given index in a list tag
	 */
	generic_tag *at(unsigned int index);

	/*
	 * Returns the empty status of a list tag
	 */
	bool empty(void) { return value.empty(); }

	/*
	 * Returns a list tag value
	 */
	void *get_value(void) { return &value; }

	/*
	 * Returns the size of a list tag
	 */
	unsigned int size(void) { return value.size(); }

	/*
	 * Returns a string representation of a list tag
	 */
	std::string to_string(void);
};

#endif
