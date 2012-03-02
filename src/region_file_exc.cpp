/*
 * region_file_exc.cpp
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

#include "region_file_exc.hpp"

/*
 * Exception messages
 */
const std::string region_file_exc::MESSAGE[MESSAGE_COUNT] = {
		"Undefined exception",
		"Failed to allocate memory",
		"Invalid path",
		"Coord out of range",
		"Unsupported compression",
		"Unknown compression",
		"Unknown tag type",
		"Stream read error",
		"Attempt to read unfilled chunk",
};

/*
 * Region file exception assignment
 */
region_file_exc &region_file_exc::operator=(const region_file_exc &other) {

	// check for self
	if(this == &other)
		return *this;

	// set attributes
	exc = other.exc;
	message = other.message;
	return *this;
}

/*
 * Region file exception equals
 */
bool region_file_exc::operator==(const region_file_exc &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	return exc == other.exc
			&& message == other.message;
}

/*
 * Returns a string representation of an exception
 */
std::string region_file_exc::to_string(void) {
	std::stringstream ss;

	// form string representation
	ss << "Exception[" << exc << "]: " << MESSAGE[exc];
	if(!message.empty())
		ss << ": " << message;
	return ss.str();
}
