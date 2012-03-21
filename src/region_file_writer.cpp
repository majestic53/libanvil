/*
 * region_file_writer.cpp
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
#include "region_file_writer.hpp"

/*
 * Region file writer assignment operator
 */
region_file_writer &region_file_writer::operator=(const region_file_writer &other) {

	// check for self
	if(this == &other)
		return *this;

	// assign attributes
	path = other.path;
	reg = other.reg;
	return *this;
}

/*
 * Region file writer equals operator
 */
bool region_file_writer::operator==(const region_file_writer &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	return path == other.path
			&& reg == other.reg;
}

/*
 * Write a region file to file
 */
void region_file_writer::write(void) {

	// TODO: write to file

}
