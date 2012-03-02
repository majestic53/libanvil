/*
 * region_chunk_info.cpp
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
#include "region_chunk_info.hpp"

/*
 * Region chunk info constructor
 */
region_chunk_info::region_chunk_info(void) {
	pos = 0;
	size = 0;
	modified = 0;
	type = UNDEFINED;
}

/*
 * Region chunk info constructor
 */
region_chunk_info::region_chunk_info(const region_chunk_info &other) {
	pos = other.pos;
	size = other.size;
	modified = other.modified;
	type = other.type;
}

/*
 * Region chunk info assignment
 */
region_chunk_info &region_chunk_info::operator=(const region_chunk_info &other) {

	// check for self
	if(this == &other)
		return *this;

	// set attributes
	pos = other.pos;
	size = other.size;
	modified = other.modified;
	type = other.type;
	return *this;
}

/*
 * Region chunk info equals
 */
bool region_chunk_info::operator==(const region_chunk_info &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	return pos == other.pos
			&& size == other.size
			&& modified == other.modified
			&& type == other.type;
}

/*
 * Returns a string representation of a region chunk info
 */
std::string region_chunk_info::to_string(void) {
	std::stringstream ss;

	// form string representation
	ss << "[CHUNK] ";
	switch(type) {
		case GZIP: ss << "GZIP";
			break;
		case ZLIB: ss << "ZLIB";
			break;
		default: ss << "UNDEFINED";
			break;
	}
	ss << ", timestamp: " << modified << ", size: " << size << ", pos: " << pos;
	return ss.str();
}
