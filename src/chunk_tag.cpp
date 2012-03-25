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

#include <stdexcept>
#include "chunk_tag.hpp"
#include "tag/byte_tag.hpp"
#include "tag/byte_array_tag.hpp"
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
 * Copy chunk tag
 */
void chunk_tag::copy(chunk_tag &other) {
	std::vector<generic_tag *> value;

	// clear old tag and assign new tag
	clean_root();
	root.set_name(other.get_root_tag().get_name());
	value = other.get_root_tag().get_value();
	for(unsigned int i = 0; i < value.size(); ++i) {
		generic_tag *sub_tag = NULL;
		sub_tag = copy_tag(value.at(i));
		if(!sub_tag)
			throw std::runtime_error("Failed to copy tag");
		else
			root.push_back(sub_tag);
	}
}

/*
 * Copy chunk tag (recursively)
 */
generic_tag *chunk_tag::copy_tag(generic_tag *src) {
	generic_tag *tag = NULL;

	// copy tag based on type
	switch(src->type) {
		case generic_tag::COMPOUND: {
			compound_tag *cmp = static_cast<compound_tag *>(src);
			compound_tag *c_cmp = new compound_tag(cmp->get_name());
			for(unsigned int i = 0; i < cmp->size(); ++i)
				c_cmp->push_back(copy_tag(cmp->at(i)));
			tag = c_cmp;
		} break;
		case generic_tag::LIST: {
			list_tag *lst = static_cast<list_tag *>(src);
			list_tag *c_lst = new list_tag(lst->get_name(), lst->get_element_type());
			for(unsigned int i = 0; i < lst->size(); ++i)
				c_lst->push_back(copy_tag(lst->at(i)));
			tag = c_lst;
		} break;
		default:
			case generic_tag::END: tag = new end_tag();
				break;
			case generic_tag::BYTE: tag = copy_tag_helper<byte_tag>(src);
				break;
			case generic_tag::SHORT: tag = copy_tag_helper<short_tag>(src);
				break;
			case generic_tag::INT: tag = copy_tag_helper<int_tag>(src);
				break;
			case generic_tag::LONG: tag = copy_tag_helper<long_tag>(src);
				break;
			case generic_tag::FLOAT: tag = copy_tag_helper<float_tag>(src);
				break;
			case generic_tag::DOUBLE: tag = copy_tag_helper<double_tag>(src);
				break;
			case generic_tag::BYTE_ARRAY: tag = copy_tag_helper<byte_array_tag>(src);
				break;
			case generic_tag::STRING: tag = copy_tag_helper<string_tag>(src);
				break;
			case generic_tag::INT_ARRAY: tag = copy_tag_helper<int_array_tag>(src);
				break;
	}
	return tag;
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
