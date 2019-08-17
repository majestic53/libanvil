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
#include <stdexcept>
#include <vector>
#include "../include/byte_stream.h"
#include "../include/chunk_info.h"
#include "../include/compression.h"
#include "../include/region_dim.h"
#include "../include/region_file_writer.h"

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
	unsigned char count;
	unsigned int offset, remaining;
	std::vector<char> header_data;
	unsigned int pos = region_dim::HEADER_OFFSET;
	byte_stream region_stream(byte_stream::SWAP_ENDIAN);

	// attempt to open file
	file.open(path.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
	if(!file.is_open())
		throw std::runtime_error("Failed to open output file");

	// iterate through tags
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i) {

		// skip unfilled chunks
		if(!reg.is_filled(i))
			continue;

		// compress chunk
		std::vector<char> chunk_data = reg.get_tag_at(i).get_data();
		compression::deflate_(chunk_data);

		// adjust header
		reg.get_header().get_info_at(i).set_length(chunk_data.size());
		count = (chunk_data.size() / region_dim::SECTOR_SIZE) + 1;
		offset = pos / region_dim::SECTOR_SIZE;
		reg.get_header().get_info_at(i).set_offset((offset << 8) | count);

		// append chunk header & chunk to region stream
		region_stream << (int) reg.get_header().get_info_at(i).get_length();
		region_stream << (char) reg.get_header().get_info_at(i).get_type();
		region_stream << chunk_data;

		// add remaining zeros to fill out sector
		remaining = region_dim::SECTOR_SIZE - (reg.get_header().get_info_at(i).get_length() % region_dim::SECTOR_SIZE) - (sizeof(int) + sizeof(char));
		for(unsigned int j = 0; j < remaining; ++j)
			region_stream << (char) 0;

		// move position forward
		pos += count * region_dim::SECTOR_SIZE;
	}

	// write header to file
	header_data = reg.get_header().get_data();
	file.write(header_data.data(), header_data.size());

	// write chunks to file
	file.write(region_stream.rdbuf(), region_stream.size());

	// close file
	file.close();
}
