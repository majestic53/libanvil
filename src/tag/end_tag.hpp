/*
 * end_tag.hpp
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

#ifndef END_TAG_HPP_
#define END_TAG_HPP_

#include "generic_tag.hpp"

class end_tag : public generic_tag {
public:

	/*
	 * End tag constructor
	 */
	end_tag(void) : generic_tag(END) { return; }

	/*
	 * End tag constructor
	 */
	end_tag(const end_tag &other) : generic_tag(other.name, END) { return; }

	/*
	 * End tag destructor
	 */
	~end_tag(void) { return; }

	/*
	 * End tag assignment
	 */
	end_tag &operator=(const end_tag &other);

	/*
	 * End tag equals
	 */
	bool operator==(const end_tag &other) { return generic_tag::operator ==(other); }

	/*
	 * End tag not equals
	 */
	bool operator!=(const end_tag &other) { return !(*this == other); }

	/*
	 * Returns an end tags value
	 */
	void *get_value(void) { return NULL; }

	/*
	 * Returns a string representation of an end tag
	 */
	std::string to_string(void);
};

#endif
