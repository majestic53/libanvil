/*
 * chunk_info.cpp
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
#include "chunk_info.hpp"

/*
 * Chunk info assignment operator
 */
chunk_info &chunk_info::operator=(const chunk_info &other) {

	// check for self
	if(this == &other)
		return *this;

	// assign attributes
	length = other.length;
	modified = other.modified;
	offset = other.offset;
	type = other.type;
	return *this;
}

/*
 * Chunk info equals operator
 */
bool chunk_info::operator==(const chunk_info &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	return length == other.length
			&& modified == other.modified
			&& offset == other.offset
			&& type == other.type;
}

/*
 * Returns a string representation of a chunk
 */
std::string chunk_info::to_string(void) {
	std::stringstream ss;

	// form string representation
	ss << "[";
	switch(type) {
		case GZIP: ss << "GZIP";
			break;
		case ZLIB: ss << "ZLIB";
			break;
		default: ss << "UNKNOWN";
			break;
	}
	ss << "] off: " << offset << ", len: " << length << ", modified: " << modified;
	return ss.str();
}
