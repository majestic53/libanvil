/*
 * region_chunk_tag.hpp
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

#ifndef REGION_CHUNK_TAG_HPP_
#define REGION_CHUNK_TAG_HPP_

#include <vector>
#include "tag/byte_array_tag.hpp"
#include "tag/byte_tag.hpp"
#include "tag/compound_tag.hpp"
#include "tag/double_tag.hpp"
#include "tag/end_tag.hpp"
#include "tag/float_tag.hpp"
#include "tag/generic_tag.hpp"
#include "tag/int_tag.hpp"
#include "tag/int_array_tag.hpp"
#include "tag/list_tag.hpp"
#include "tag/long_tag.hpp"
#include "tag/short_tag.hpp"
#include "tag/string_tag.hpp"

class region_chunk_tag {
private:

	/*
	 * Root region chunk tag
	 */
	generic_tag *root;

	/*
	 * Get tag by name helper
	 */
	void get_tag_by_name_helper(const std::string &name, generic_tag *root, std::vector<generic_tag *> &tags);

public:

	/*
	 * Region chunk tag constructor
	 */
	region_chunk_tag(void) : root(NULL) { return; }

	/*
	 * Region chunk tag constructor
	 */
	region_chunk_tag(const region_chunk_tag &other);

	/*
	 * Region chunk tag constructor
	 */
	region_chunk_tag(generic_tag *root);

	/*
	 * Region chunk tag destructor
	 */
	virtual ~region_chunk_tag(void) { cleanup(); }

	/*
	 * Region chunk tag assignment
	 */
	region_chunk_tag &operator=(const region_chunk_tag &other);

	/*
	 * Region chunk tag equals
	 */
	bool operator==(const region_chunk_tag &other);

	/*
	 * Region chunk tag not equals
	 */
	bool operator!=(const region_chunk_tag &other) { return !(*this == other); }

	/*
	 * Cleanup a root tag
	 */
	void cleanup(void) { cleanup(root); }

	/*
	 * Cleanup a series of tags
	 */
	static void cleanup(generic_tag *&tag);

	/*
	 * Copies the contents of a root tag into another
	 */
	bool copy(generic_tag *&dest) { return copy(root, dest); }

	/*
	 * Copies the contents of a tag into another
	 */
	static bool copy(generic_tag *src, generic_tag *&dest);

	/*
	 * Region chunk tag empty status
	 */
	bool empty(void) { return !root; }

	/*
	 * Returns chunk tag equivalence of two tags
	 */
	static bool equals(generic_tag *tag1, generic_tag *tag2);

	/*
	 * Return region chunk tag root tag
	 */
	generic_tag *&get_root_tag(void) { return root; }

	/*
	 * Return a region chunk tag tag at a given name
	 */
	std::vector<generic_tag *> get_tag_by_name(const std::string &name);

	/*
	 * Returns a string representation of a region chunk tag
	 */
	std::string to_string(void);
};

#endif
