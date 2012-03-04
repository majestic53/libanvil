/*
 * region_file.hpp
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

#ifndef REGION_FILE_HPP_
#define REGION_FILE_HPP_

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <boost/regex.hpp>
#include "byte_stream.hpp"
#include "region_chunk_info.hpp"
#include "region_chunk_tag.hpp"
#include "region_file_exc.hpp"
#include "tag/byte_array_tag.hpp"
#include "tag/byte_tag.hpp"
#include "tag/compound_tag.hpp"
#include "tag/double_tag.hpp"
#include "tag/end_tag.hpp"
#include "tag/float_tag.hpp"
#include "tag/generic_tag.hpp"
#include "tag/int_tag.hpp"
#include "tag/int_array_tag.hpp"
#include "tag/list_tag.hpp"
#include "tag/long_tag.hpp"
#include "tag/short_tag.hpp"
#include "tag/string_tag.hpp"

class region_file {
private:

	/*
	 * ZLib inflation segment size
	 */
	static const unsigned int SEGMENT_SIZE = 16384;

	/*
	 * Array of chunk files
	 */
	region_chunk_info *info;

	/*
	 * Region file
	 */
	std::ifstream file;

	/*
	 * Number of chunks filled
	 */
	unsigned int filled;

	/*
	 * Region file path
	 */
	std::string path;

	/*
	 * Region file coord
	 */
	int x, z;

	/*
	 * Returnd region chunk data at a given x, z coord
	 */
	void get_chunk_data(unsigned int x, unsigned int z, std::vector<int8_t> &data);

	/*
	 * ZLib inflation routine
	 */
	void inflate_zlib(std::vector<int8_t> &in, std::vector<int8_t> &out);

	/*
	 * Reads an array tag value from stream
	 */
	template <class T>
	void read_array_value(byte_stream &stream, std::vector<T> &value) {
		int32_t len;
		T byte_ele;

		// check stream status
		if(!stream.good())
			throw region_file_exc(region_file_exc::STREAM_READ_ERROR, stream.position());

		// retrieve value
		stream >> len;
		len = abs(len);
		for(int i = 0; i < len; ++i) {
			stream >> byte_ele;
			value.push_back(byte_ele);
		}
	}

	/*
	 * Reads a compound tag value from stream
	 */
	void read_compound_value(byte_stream &stream, std::vector<generic_tag *> &value);

	/*
	 * Reads a list tag value from stream
	 */
	void read_list_value(byte_stream &stream, std::vector<generic_tag *> &value);

	/*
	 * Reads a number tag value from stream
	 */
	template <class T>
	void read_number_value(byte_stream &stream, T &value) {

		// check stream status
		if(!stream.good())
			throw region_file_exc(region_file_exc::STREAM_READ_ERROR, stream.position());

		// retrieve value
		stream >> value;
	}

	/*
	 * Reads a string tag value from stream
	 */
	void read_string_value(byte_stream &stream, std::string &value);

	/*
	 * Creates a tag from stream
	 */
	generic_tag *read_tag(const std::string &name, unsigned int type, byte_stream &stream);

public:

	/*
	 * Region file pattern
	 */
	static const boost::regex PATTERN;

	/*
	 * Region file sector size
	 */
	static const unsigned int SECTOR_SIZE = 4096;

	/*
	 * Region file constructor
	 */
	region_file(void);

	/*
	 * Region file constructor
	 */
	region_file(const region_file &other);

	/*
	 * Region file constructor
	 */
	region_file(const std::string &path);

	/*
	 * Region file destructor
	 */
	virtual ~region_file(void);

	/*
	 * Region file assignment
	 */
	region_file &operator=(const region_file &other);

	/*
	 * Region file equals
	 */
	bool operator==(const region_file &other);

	/*
	 * Region file not equals
	 */
	bool operator!=(const region_file &other) { return !(*this == other); }

	/*
	 * Convert between endians
	 */
	template<class T>
	static void convert_endian(T &value) {

		// convert value to character array
		char *endian = reinterpret_cast<char *>(&value);

		// reverse character array
		std::reverse(endian, endian + sizeof(T));
	}

	/*
	 * Returns region chunk information at a given x, z coord
	 */
	void get_chunk_info(unsigned int x, unsigned int z, region_chunk_info &info);

	/*
	 * Returns chunk data tag at a given x, z coord
	 */
	void get_chunk_tag(unsigned int x, unsigned int z, region_chunk_tag &tag);

	/*
	 * Returns total region chunks filled within a region file
	 */
	unsigned int get_filled(void) { return filled; }

	/*
	 * Returns region file path
	 */
	std::string get_path(void) { return path; }

	/*
	 * Returns region file x coord
	 */
	int get_region_x_coord(void) { return x; }

	/*
	 * Returns region file z coord
	 */
	int get_region_z_coord(void) { return z; }

	/*
	 * Returns true if a specified path is a region file
	 */
	static bool is_region_file(const std::string &path, int &x, int &z);

	/*
	 * Reads in a series of region chunks
	 */
	void read(void) { read(path); }

	/*
	 * Reads in a series of region chunks from a given path
	 */
	void read(const std::string &path);

	/*
	 * Returns a string representation of a region file
	 */
	std::string to_string(void);
};

#endif
