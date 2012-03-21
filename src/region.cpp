/*
 * region.cpp
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

#include <sstream>
#include <stdexcept>
#include "region.hpp"

/*
 * Region constructor
 */
region::region(const region &other) : header(other.header), x(x), z(z) {

	// assign attributes
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i)
		tags[i] = other.tags[i];
}

/*
 * Region constructor
 */
region::region(int x, int z, const region_header &header, const chunk_tag (&tags)[region_dim::CHUNK_COUNT]) : header(header), x(x), z(z) {

	// assign attributes
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i)
		this->tags[i] = tags[i];
}

/*
 * Region assignment operator
 */
region &region::operator=(const region &other) {

	// check for self
	if(this == &other)
		return *this;

	// assign attributes
	header = other.header;
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i)
		tags[i] = other.tags[i];
	x = other.x;
	z = other.z;
	return *this;
}

/*
 * Region equals operator
 */
bool region::operator==(const region &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	if(header != other.header
			|| x != other.x
			|| z != other.z)
		return false;
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i)
		if(tags[i] != other.tags[i])
			return false;
	return true;
}

/*
 * Returns a region's tag at a given index
 */
chunk_tag &region::get_tag_at(unsigned int index) {

	// check for valid index
	if(index >= region_dim::CHUNK_COUNT)
		throw std::out_of_range("index out-of-range");
	return tags[index];
}

/*
 * Sets a region's tags
 */
void region::set_tags(const chunk_tag (&tags)[region_dim::CHUNK_COUNT]) {

	// set info
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i)
		this->tags[i] = tags[i];
}

/*
 * Sets a region tag at a given index
 */
void region::set_tag_at(unsigned int index, chunk_tag &tag) {

	// check for valid index
	if(index >= region_dim::CHUNK_COUNT)
		throw std::out_of_range("index out-of-range");
	tags[index] = tag;
}

/*
 * Returns a string representation of a region
 */
std::string region::to_string(void) {
	std::stringstream ss;

	// form string representation
	ss << "(" << x << ", " << z << "): " << header.to_string() << std::endl;
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i) {
		if(header.get_info_at(i).empty())
			continue;
		ss << i << ": " << header.get_info_at(i).to_string() << std::endl;
	}
	return ss.str();
}
