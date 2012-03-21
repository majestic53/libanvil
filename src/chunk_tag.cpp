/*
 * chunk_tag.cpp
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

#include "chunk_tag.hpp"
#include "tag/byte_tag.hpp"
#include "tag/byte_array_tag.hpp"
#include "tag/compound_tag.hpp"
#include "tag/double_tag.hpp"
#include "tag/end_tag.hpp"
#include "tag/float_tag.hpp"
#include "tag/int_tag.hpp"
#include "tag/int_array_tag.hpp"
#include "tag/list_tag.hpp"
#include "tag/long_tag.hpp"
#include "tag/short_tag.hpp"
#include "tag/string_tag.hpp"

/*
 * Chunk tag assignment operator
 */
chunk_tag &chunk_tag::operator=(const chunk_tag &other) {

	// check for self
	if(this == &other)
		return *this;

	// assign attributes
	root = other.root;
	return *this;
}

/*
 * Chunk tag equals operator
 */
bool chunk_tag::operator==(const chunk_tag &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	return root == other.root;
}

/*
 * Clean chunk tag root tag (recursively)
 */
void chunk_tag::clean_root(void) {

	// iterate through sub-tags
	for(unsigned int i = 0; i < root.size(); ++i)
		clean_tag(root.at(i));
}

/*
 * Clean chunk tag (recursively)
 */
void chunk_tag::clean_tag(generic_tag *tag) {

	// clean tag based on type
	switch(tag->get_type()) {
		case generic_tag::COMPOUND: {
			compound_tag *cmp = static_cast<compound_tag *>(tag);
			for(unsigned int i = 0; i < cmp->size(); ++i)
				clean_tag(cmp->at(i));
			delete cmp;
		} break;
		case generic_tag::LIST: {
			list_tag *lst = static_cast<list_tag *>(tag);
			for(unsigned int i = 0; i < lst->size(); ++i)
				clean_tag(lst->at(i));
			delete lst;
		} break;
		default: delete tag;
			break;
	}
}

/*
 * Returns a chunk tag sub-tag at a given name
 */
std::vector<generic_tag *> chunk_tag::get_sub_tag_by_name(const std::string &name) {
	std::vector<generic_tag *> sub_tag;
	get_tag_by_name_helper(name, &root, sub_tag);
	return sub_tag;
}

/*
 * Returns a chunk tag sub-tag at a given name helper
 */
void chunk_tag::get_tag_by_name_helper(const std::string &name, generic_tag *tag, std::vector<generic_tag *> &tags) {

	// check for matching name
	if(tag->get_name() == name)
		tags.push_back(tag);

	// iterate through sub-tags based on type
	switch(tag->get_type()) {
		case generic_tag::COMPOUND: {
			compound_tag *cmp = dynamic_cast<compound_tag *>(tag);
			if(!cmp)
				return;
			for(unsigned int i = 0; i < cmp->size(); ++i)
				get_tag_by_name_helper(name, cmp->at(i), tags);
		} break;
		case generic_tag::LIST: {
			list_tag *lst = dynamic_cast<list_tag *>(tag);
			if(!lst)
				return;
			for(unsigned int i = 0; i < lst->size(); ++i)
				get_tag_by_name_helper(name, lst->at(i), tags);
		} break;
	}
}
