/*
 * region_file.cpp
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
#include "region_file.hpp"

/*
 * Region file pattern
 */
const boost::regex region_file::PATTERN = boost::regex("r\\.([-]?[0-9]+)\\.([-]?[0-9]+)\\.mca");

/*
 * Region file assignment operator
 */
region_file &region_file::operator=(const region_file &other) {

	// check for self
	if(this == &other)
		return *this;

	// assign attributes
	path = other.path;
	reg = other.reg;
	return *this;
}

/*
 * Region file equals operator
 */
bool region_file::operator==(const region_file &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	return path == other.path
			&& reg == other.reg;
}

/*
 * Convert between endian types
 */
void region_file::convert_endian(std::vector<char> &data) {
	std::vector<char> rev;
	rev.resize(data.size());

	// reverse the order of elements
	for(unsigned int i = 0; i < data.size(); ++i)
		rev.at(rev.size() - i) = data.at(i);
	data = rev;
}

/*
 * Returns true if a specified path is a region file
 */
bool region_file::is_region_file(const std::string &path, int &x, int &z) {

	// parse the filename for coordinants
	boost::cmatch ref;
	std::stringstream stream;
	std::string name = path.substr(path.find_last_of('/') + 1);
	if(!boost::regex_match(name.c_str(), ref, PATTERN))
		return false;
	stream << ref[1];
	stream >> x;
	stream.clear();
	stream << ref[2];
	stream >> z;
	return true;
}

/*
 * Returns a string representation of a region file
 */
std::string region_file::to_string(void) {
	std::stringstream ss;

	// form string representation
	if(!path.empty())
		ss << "Path: " << path << std::endl;
	ss << reg.to_string();
	return ss.str();
}
