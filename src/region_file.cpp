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
#include <zlib.h>
#include "region_dim.hpp"
#include "region_file.hpp"

/*
 * Region file pattern
 */
const boost::regex region_file::PATTERN = boost::regex("r\\.([-]?[0-9]+)\\.([-]?[0-9]+)\\.mca");

/*
 * Region file constructor
 */
region_file::region_file(const region_file &other) : filled(other.filled), path(other.path), x(other.x), z(other.z) {

	// assign all attributes
	for(unsigned int i = 0; i < region_dim::REGION_AREA; ++i)
		info[i] = other.info[i];
}

/*
 * Region file constructor
 */
region_file::region_file(const std::string &path) : filled(0), path(path), x(0), z(0) {

	// parse the filename for coordinants
	if(!is_region_file(path, x, z))
		throw region_file_exc(region_file_exc::INVALID_PATH, path);

	// retrieve region file information
	read();
}

/*
 * Region file assignment
 */
region_file &region_file::operator=(const region_file &other) {

	// check for self
	if(this == &other)
		return *this;

	// assign attributes
	file.close();
	filled = other.filled;
	path = other.path;
	x = other.x;
	z = other.z;
	for(unsigned int i = 0; i < region_dim::REGION_AREA; ++i)
		info[i] = other.info[i];
	return *this;
}

/*
 * Region file equals
 */
bool region_file::operator==(const region_file &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	if(filled != other.filled
			|| path != other.path
			|| x != other.x
			|| z != other.z)
		return false;
	for(unsigned int i = 0; i < region_dim::REGION_AREA; ++i)
		if(info[i] != other.info[i])
			return false;
	return true;
}

/*
 * Returnd region chunk data at a given x, z coord
 */
void region_file::get_chunk_data(unsigned int x, unsigned int z, std::vector<int8_t> &data) {
	unsigned int pos = x + z * region_dim::REGION_Z;

	// check if x, z coord are out-of-bounds
	if(pos >= region_dim::REGION_AREA) {
		unsigned int coord[] = {x, z};
		std::vector<unsigned int> coord_vec(coord, coord + 2);
		throw region_file_exc(region_file_exc::OUT_OF_BOUNDS, coord_vec);
	}

	// check if x, z coord is filled
	if(!region_chunk_info(this->info[pos]).get_position()) {
		unsigned int coord[] = {x, z};
		std::vector<unsigned int> coord_vec(coord, coord + 2);
		throw region_file_exc(region_file_exc::UNFILLED_CHUNK, coord_vec);
	}

	// gather chunk info
	region_chunk_info chunk_info = info[x + z * region_dim::REGION_Z];
	int comp_size = chunk_info.get_size();

	// check if chunk is empty
	if(chunk_info.get_position() == 0) {
		data.clear();
		return;
	}

	// open region file
	std::ifstream chunk_file;
	chunk_file.open(path.c_str(), std::ios::in | std::ios::binary);

	// check if file exists
	if(!chunk_file)
		throw region_file_exc(region_file_exc::INVALID_PATH, path);

	// read data from file
	std::vector<int8_t> comp_vec;
	int8_t comp_buff[comp_size];
	chunk_file.seekg(chunk_info.get_position(), std::ios::beg);
	chunk_file.read((char *) comp_buff, comp_size);
	comp_vec.assign(comp_buff, comp_buff + comp_size);

	// close file
	chunk_file.close();

	// decompress data
	switch(chunk_info.get_type()) {
		case region_chunk_info::GZIP:
			throw region_file_exc(region_file_exc::UNSUPPORTED_COMPRESSION, chunk_info.get_type());
			break;
		case region_chunk_info::ZLIB:
			inflate_zlib(comp_vec, data);
			break;
		default: throw region_file_exc(region_file_exc::UNKNOWN_COMPRESSION, chunk_info.get_type());
			break;
	}
}

/*
 * Returns region chunk information at a given x, z coord
 */
void region_file::get_chunk_info(unsigned int x, unsigned int z, region_chunk_info &info) {

	// check if x, z coord are out-of-bounds
	if(x + z * region_dim::REGION_Z >= region_dim::REGION_AREA) {
		unsigned int coord[] = {x, z};
		std::vector<unsigned int> coord_vec(coord, coord + 2);
		throw region_file_exc(region_file_exc::OUT_OF_BOUNDS, coord_vec);
	}

	// assign chunk info
	info = region_chunk_info(this->info[x + z * region_dim::REGION_Z]);
}

/*
 * Returns chunk data tag at a given x, z coord
 */
void region_file::get_chunk_tag(unsigned int x, unsigned int z, region_chunk_tag &tag) {

	// collect chunk data
	int8_t type;
	std::vector<int8_t> data;
	get_chunk_data(x, z, data);

	// setup stream from data
	byte_stream stream(data);
	stream << byte_stream::NO_SWAP_ENDIAN;

	// parse data for tags
	stream >> type;

	// cleanup and assign new tag
	region_chunk_tag::cleanup(tag.get_root_tag());
	tag.get_root_tag() = NULL;
	if(type == generic_tag::END)
		tag.get_root_tag() = new end_tag;
	else {
		int8_t ch;
		int16_t name_len;
		stream >> name_len;
		std::string name;
		for(int i = 0; i < name_len; i++) {
			stream >> ch;
			name += ch;
		}
		tag.get_root_tag() = read_tag(name, type, stream);
	}
}

/*
 * ZLib inflation routine
 */
void region_file::inflate_zlib(std::vector<int8_t> &in, std::vector<int8_t> &out) {
	z_stream str;
	int ret, pos = 0;

	// setup zlib object
	str.zalloc = Z_NULL;
	str.zfree = Z_NULL;
	str.opaque = Z_NULL;
	str.avail_in = 0;
	str.next_in = Z_NULL;

	// begin inflation
	ret = inflateInit(&str);
	do {
		int size = SEGMENT_SIZE;
		if((unsigned int) (in.size() - pos) < SEGMENT_SIZE)
			size = in.size() - pos;
		int8_t in_buff[size];
		int8_t out_buff[size];
		for(int i = 0; i < size; i++)
			in_buff[i] = in.at(pos + i);
		str.avail_in = size;
		str.next_in = (Bytef *) in_buff;
		do {
			str.avail_out = size;
			str.next_out = (Bytef *) out_buff;
			ret = inflate(&str, Z_NO_FLUSH);
			for(int i = 0; i < size; i++)
				out.push_back(out_buff[i]);
		} while(str.avail_out == 0);
		pos += size;
	} while(ret != Z_STREAM_END);

	// end inflation
	inflateEnd(&str);
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
 * Reads in a series of region chunks from a given path
 */
void region_file::read(const std::string &path) {
	int pos[region_dim::REGION_AREA];
	int time[region_dim::REGION_AREA];

	// open file at path
	file.open(path.c_str(), std::ios::in | std::ios::binary);

	// check if file exists
	if(!file)
		throw region_file_exc(region_file_exc::INVALID_PATH, path);

	// read in chunk positions & convert to little-endian
	for(unsigned int i = 0; i < region_dim::REGION_AREA; ++i) {
		file.read(reinterpret_cast<char *>(&pos[i]), sizeof(int));
		convert_endian(pos[i]);

		// increment filled if chunk is not empty
		if(pos[i] != 0)
			filled++;
	}

	// read in chunk timestamps & covert to little-endian
	for(unsigned int i = 0; i < region_dim::REGION_AREA; ++i) {
		file.read(reinterpret_cast<char *>(&time[i]), sizeof(int));
		convert_endian(time[i]);
	}

	// add chunks to array
	for(unsigned int i = 0; i < region_dim::REGION_AREA; i++) {
		int size = 0;
		char comp_type = 0;
		region_chunk_info chunk_info;

		// retrieve chunk size, compression type, & data if chunk exists
		if(pos[i] != 0) {
			file.seekg(0, std::ios::beg);
			file.seekg((pos[i] >> 8) * SECTOR_SIZE, std::ios::cur);
			file.read(reinterpret_cast<char *>(&size), sizeof(int));
			convert_endian(size);
			file.read(&comp_type, sizeof(char));
			pos[i] = file.tellg();
			chunk_info = region_chunk_info(comp_type, size, pos[i], time[i]);
		}

		// create all chunks
		info[i] = chunk_info;
	}

	// close file
	file.close();
}

/*
 * Reads a compound tag value from stream
 */
void region_file::read_compound_value(byte_stream &stream, std::vector<generic_tag *> &value) {
	int16_t name_len;
	int8_t ch, ele_type;
	std::string name;

	// check stream status
	if(!stream.good())
		throw region_file_exc(region_file_exc::STREAM_READ_ERROR, stream.position());

	// retrieve compound value
	do {
		stream >> ele_type;
		if(ele_type != generic_tag::END) {
			stream >> name_len;
			name.clear();
			for(int i = 0; i < name_len; i++) {
				stream >> ch;
				name += ch;
			}
			value.push_back(read_tag(name, ele_type, stream));
		}
	} while(ele_type != generic_tag::END);
}

/*
 * Reads a list tag value from stream
 */
void region_file::read_list_value(byte_stream &stream, std::vector<generic_tag *> &value) {
	int32_t len;
	int8_t ele_type;

	// check stream status
	if(!stream.good())
		throw region_file_exc(region_file_exc::STREAM_READ_ERROR, stream.position());

	// retrieve list value
	stream >> ele_type;
	stream >> len;
	len = abs(len);
	for(int i = 0; i < len; i++)
		value.push_back(read_tag("", ele_type, stream));
}

/*
 * Reads a string tag value from stream
 */
void region_file::read_string_value(byte_stream &stream, std::string &value) {
	int8_t ch;
	int16_t str_len;

	// check stream status
	if(!stream.good())
		throw region_file_exc(region_file_exc::STREAM_READ_ERROR, stream.position());

	// retrieve string value
	stream >> str_len;
	for(int i = 0; i < str_len; i++) {
		stream >> ch;
		value += ch;
	}
}

/*
 * Creates a tag from stream
 */
generic_tag *region_file::read_tag(const std::string &name, unsigned int type, byte_stream &stream) {

	// create tag
	generic_tag *tag = NULL;

	// assign tag based off type
	switch(type) {
		case generic_tag::BYTE: {
			int8_t b_val;
			read_number_value<int8_t>(stream, b_val);
			tag = new byte_tag(name, b_val);
		} break;
		case generic_tag::BYTE_ARRAY: {
			std::vector<int8_t> b_vec;
			read_array_value<int8_t>(stream, b_vec);
			tag = new byte_array_tag(name, b_vec);
		} break;
		case generic_tag::COMPOUND: {
			std::vector<generic_tag *> gen_vec;
			read_compound_value(stream, gen_vec);
			tag = new compound_tag(name, gen_vec);
		} break;
		case generic_tag::DOUBLE: {
			double d_val;
			read_number_value<double>(stream, d_val);
			tag = new double_tag(name, d_val);
		} break;
		case generic_tag::END:
			tag = new end_tag;
			break;
		case generic_tag::FLOAT: {
			float f_val;
			read_number_value<float>(stream, f_val);
			tag = new float_tag(name, f_val);
		} break;
		case generic_tag::INT: {
			int32_t i_val;
			read_number_value<int32_t>(stream, i_val);
			tag = new int_tag(name, i_val);
		} break;
		case generic_tag::INT_ARRAY: {
			std::vector<int32_t> i_vec;
			read_array_value<int32_t>(stream, i_vec);
			tag = new int_array_tag(name, i_vec);
		} break;
		case generic_tag::LIST: {
			std::vector<generic_tag *> gen_vec;
			read_list_value(stream, gen_vec);
			tag = new list_tag(name, gen_vec);
		} break;
		case generic_tag::LONG: {
			int64_t l_val;
			read_number_value<int64_t>(stream, l_val);
			tag = new long_tag(name, l_val);
		} break;
		case generic_tag::SHORT: {
			int16_t s_val;
			read_number_value<int16_t>(stream, s_val);
			tag = new short_tag(name, s_val);
		} break;
		case generic_tag::STRING: {
			std::string str_val;
			read_string_value(stream, str_val);
			tag = new string_tag(name, str_val);
		} break;
		default:
			throw region_file_exc(region_file_exc::UNKNOWN_TAG_TYPE, type);
	}
	return tag;
}

/*
 * Returns a string representation of a region file
 */
std::string region_file::to_string(void) {
	std::stringstream ss;

	// form string representation
	ss << "[REGION] (" << x << ", " << z << "), filled: " << filled << "/" << region_dim::REGION_AREA << ", path: " << path;
	return ss.str();
}
