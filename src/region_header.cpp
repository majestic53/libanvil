/*
 * region_header.cpp
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
#include "byte_stream.hpp"
#include "region_header.hpp"

/*
 * Region header constructor
 */
region_header::region_header(void) {

	// initialize attributes
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i)
		info[i] = chunk_info();
}

/*
 * Region header constructor
 */
region_header::region_header(const region_header &other) {

	// set attributes
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i)
		info[i] = other.info[i];
}

/*
 * Region header constructor
 */
region_header::region_header(const chunk_info (&info)[region_dim::CHUNK_COUNT]) {

	// set attributes
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i)
		this->info[i] = info[i];
}

/*
 * Region header assignment operator
 */
region_header &region_header::operator=(const region_header &other) {

	// check for self
	if(this == &other)
		return *this;

	// set attributes
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i)
		info[i] = other.info[i];
	return *this;
}

/*
 * Region header equals operator
 */
bool region_header::operator==(const region_header &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i)
		if(info[i] != other.info[i])
			return false;
	return true;
}

/*
 * Return a region header as character vector
 */
std::vector<char> region_header::get_data(void) {
	byte_stream stream(byte_stream::SWAP_ENDIAN);

	// insert offsets
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i)
		stream << (int) info[i].get_offset();

	// insert timestamps
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i)
		stream << (int) info[i].get_modified();
	return stream.vbuf();
}

/*
 * Return a region header's region count
 */
unsigned int region_header::get_count(void) {
	unsigned int count = 0;

	// count all occupied regions
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i)
		if(!info[i].empty())
			++count;
	return count;
}

/*
 * Return a region header's info at a given index
 */
chunk_info &region_header::get_info_at(unsigned int index) {

	// check for valid index
	if(index >= region_dim::CHUNK_COUNT)
		throw std::out_of_range("index out-of-range");
	return info[index];
}

/*
 * Set a region header's info
 */
void region_header::set_info(const chunk_info (&info)[region_dim::CHUNK_COUNT]) {

	// set info
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i)
		this->info[i] = info[i];
}

/*
 * Set a region header's info at a given index
 */
void region_header::set_info_at(unsigned int index, const chunk_info &info) {

	// check for valid index
	if(index >= region_dim::CHUNK_COUNT)
		throw std::out_of_range("index out-of-range");
	this->info[index] = info;
}

/*
 * Return a string representation of a region header
 */
std::string region_header::to_string(void) {
	std::stringstream ss;

	// form string representation
	ss << "Count: " << get_count() << "/" << region_dim::CHUNK_COUNT;
	return ss.str();
}
