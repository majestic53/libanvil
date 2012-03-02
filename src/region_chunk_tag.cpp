/*
 * region_chunk_tag.cpp
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

#include "region_chunk_tag.hpp"
#include "region_file_exc.hpp"

/*
 * Region chunk tag constructor
 */
region_chunk_tag::region_chunk_tag(const region_chunk_tag &other) {

	// copy root tag
	this->root = NULL;
	if(!copy(other.root, this->root))
		this->root = NULL;
}

/*
 * Region chunk tag constructor
 */
region_chunk_tag::region_chunk_tag(generic_tag *root) {

	// copy root tag
	this->root = NULL;
	if(!copy(root, this->root))
		this->root = NULL;
}

/*
 * Region chunk tag assignment
 */
region_chunk_tag &region_chunk_tag::operator=(const region_chunk_tag &other) {

	// check for self
	if(this == &other)
		return *this;

	// set attributes
	if(root)
		cleanup(root);
	if(!copy(other.root, root))
		root = NULL;
	return *this;
}

/*
 * Region chunk tag equals
 */
bool region_chunk_tag::operator==(const region_chunk_tag &other) {

	// check for self
	if(this == &other)
		return true;

	// check for valid roots
	if(!root
			&& !other.root)
		return true;
	else if(!root
			|| !other.root)
		return false;
	return equals(root, other.root);
}

/*
 * Cleanup a series of tags
 */
void region_chunk_tag::cleanup(generic_tag *&tag) {
	compound_tag *cmp_tag = NULL;
	list_tag *lst_tag = NULL;

	// check for valid tag
	if(!tag)
		return;

	// cleanup each tag based off its type
	switch(tag->get_type()) {
		case generic_tag::COMPOUND:
			cmp_tag = static_cast<compound_tag *>(tag);
			for(unsigned int i = 0; i < cmp_tag->size(); ++i) {
				generic_tag *sub_tag = cmp_tag->at(i);
				cleanup(sub_tag);
			}
			cmp_tag->value.clear();
			delete cmp_tag;
			break;
		case generic_tag::LIST:
			lst_tag = static_cast<list_tag *>(tag);
			for(unsigned int i = 0; i < lst_tag->size(); ++i) {
				generic_tag *sub_tag = lst_tag->at(i);
				cleanup(sub_tag);
			}
			lst_tag->value.clear();
			delete lst_tag;
			break;
		default: delete tag;
			break;
	}
}

/*
 * Copies the contents of a root tag into another
 */
bool region_chunk_tag::copy(generic_tag *src, generic_tag *&dest) {
	compound_tag *cmp_tag = NULL;
	list_tag *lst_tag = NULL;
	generic_tag *new_tag = NULL;
	std::vector<generic_tag *> value;

	// check for valid root
	if(!src)
		return false;

	// copy tags based off type
	switch(src->get_type()) {
		case generic_tag::COMPOUND:
			cmp_tag = static_cast<compound_tag *>(src);
			for(unsigned int i = 0; i < cmp_tag->size(); ++i) {
				if(!copy(cmp_tag->at(i), new_tag))
					return false;
				value.push_back(new_tag);
			}
			dest = new compound_tag(src->get_name(), value);
			if(!dest)
				return false;
			break;
		case generic_tag::LIST:
			lst_tag = static_cast<list_tag *>(src);
			for(unsigned int i = 0; i < lst_tag->size(); ++i) {
				if(!copy(lst_tag->at(i), new_tag))
					return false;
				value.push_back(new_tag);
			}
			dest = new list_tag(src->get_name(), value);
			break;
		default:
			switch(src->get_type()) {
				case generic_tag::BYTE_ARRAY:
					dest = new byte_array_tag(*static_cast<byte_array_tag *>(src));
					break;
				case generic_tag::BYTE:
					dest = new byte_tag(*static_cast<byte_tag *>(src));
					break;
				case generic_tag::DOUBLE:
					dest = new double_tag(*static_cast<double_tag *>(src));
					break;
				case generic_tag::END:
					dest = new end_tag(*static_cast<end_tag *>(src));
					break;
				case generic_tag::FLOAT:
					dest = new float_tag(*static_cast<float_tag *>(src));
					break;
				case generic_tag::INT:
					dest = new int_tag(*static_cast<int_tag *>(src));
					break;
				case generic_tag::INT_ARRAY:
					dest = new int_array_tag(*static_cast<int_array_tag *>(src));
					break;
				case generic_tag::LONG:
					dest = new long_tag(*static_cast<long_tag *>(src));
					break;
				case generic_tag::SHORT:
					dest = new short_tag(*static_cast<short_tag *>(src));
					break;
				case generic_tag::STRING:
					dest = new string_tag(*static_cast<string_tag *>(src));
					break;
				default:
					throw region_file_exc(region_file_exc::UNKNOWN_TAG_TYPE, src->get_type());
					break;
			}
			break;
	}
	return true;
}

/*
 * Returns chunk tag equivalence of two tags
 */
bool region_chunk_tag::equals(generic_tag *tag1, generic_tag *tag2) {

	// check for self
	if(tag1 == tag2)
		return true;

	// check for valid tags
	if(!tag1
			|| !tag2)
		return false;

	// check for equaivalent tags
	if(tag1->get_type() != tag2->get_type())
		return false;
	switch(tag1->get_type()) {
		case generic_tag::COMPOUND:
			if((compound_tag) *static_cast<compound_tag *>(tag1) != *static_cast<compound_tag *>(tag2))
				return false;
			break;
		case generic_tag::LIST:
			if(*static_cast<list_tag *>(tag1) != *static_cast<list_tag *>(tag2))
				return false;
			break;
		case generic_tag::BYTE_ARRAY:
			if(*static_cast<byte_array_tag *>(tag1) != *static_cast<byte_array_tag *>(tag2))
				return false;
			break;
		case generic_tag::BYTE:
			if(*static_cast<byte_tag *>(tag1) != *static_cast<byte_tag *>(tag2))
				return false;
			break;
		case generic_tag::DOUBLE:
			if(*static_cast<double_tag *>(tag1) != *static_cast<double_tag *>(tag2))
				return false;
			break;
		case generic_tag::END:
			if(*static_cast<end_tag *>(tag1) != *static_cast<end_tag *>(tag2))
				return false;
			break;
		case generic_tag::FLOAT:
			if(*static_cast<float_tag *>(tag1) != *static_cast<float_tag *>(tag2))
				return false;
			break;
		case generic_tag::INT:
			if(*static_cast<int_tag *>(tag1) != *static_cast<int_tag *>(tag2))
				return false;
			break;
		case generic_tag::INT_ARRAY:
			if(*static_cast<int_array_tag *>(tag1) != *static_cast<int_array_tag *>(tag2))
				return false;
			break;
		case generic_tag::LONG:
			if(*static_cast<long_tag *>(tag1) != *static_cast<long_tag *>(tag2))
				return false;
			break;
		case generic_tag::SHORT:
			if(*static_cast<short_tag *>(tag1) != *static_cast<short_tag *>(tag2))
				return false;
			break;
		case generic_tag::STRING:
			if(*static_cast<string_tag *>(tag1) != *static_cast<string_tag *>(tag2))
				return false;
			break;
		default:
			return false;
			break;
	}
	return true;
}

/*
 * Return a region chunk tag tag at a given name
 */
std::vector<generic_tag *> region_chunk_tag::get_tag_by_name(const std::string &name) {
	std::vector<generic_tag *> tags;
	get_tag_by_name_helper(name, root, tags);
	return tags;
}

/*
 * Get tag by name helper
 */
void region_chunk_tag::get_tag_by_name_helper(const std::string &name, generic_tag *root, std::vector<generic_tag *> &tags) {
	compound_tag *cmp_tag = NULL;
	list_tag *lst_tag = NULL;

	// check for valid root
	if(!root)
		return;

	// check tag for matching name
	if(root->get_name() == name)
		tags.push_back(root);

	// iterate through all complex types
	switch(root->get_type()) {
		case generic_tag::COMPOUND:
			cmp_tag = static_cast<compound_tag *>(root);
			for(unsigned int i = 0; i < cmp_tag->size(); ++i)
				get_tag_by_name_helper(name, cmp_tag->at(i), tags);
			break;
		case generic_tag::LIST:
			lst_tag = static_cast<list_tag *>(root);
			for(unsigned int i = 0; i < lst_tag->size(); ++i)
				get_tag_by_name_helper(name, lst_tag->at(i), tags);
			break;
	}
}

/*
 * Returns a string representation of a region chunk tag
 */
std::string region_chunk_tag::to_string(void) {
	if(!root)
		return "Empty";
	return root->to_string();
}
