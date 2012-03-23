 /*
 * region_file_reader.cpp
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
#include <vector>
#include "chunk_info.hpp"
#include "chunk_tag.hpp"
#include "compression.hpp"
#include "region_dim.hpp"
#include "region_file_reader.hpp"
#include "tag/byte_tag.hpp"
#include "tag/byte_array_tag.hpp"
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

/*
 * Region file reader assignment operator
 */
region_file_reader &region_file_reader::operator=(const region_file_reader &other) {

	// check for self
	if(this == &other)
		return *this;

	// assign attributes
	path = other.path;
	reg = other.reg;
	return *this;
}

/*
 * Region file reader equals operator
 */
bool region_file_reader::operator==(const region_file_reader &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	return path == other.path
			&& reg == other.reg;
}

/*
 * Returns a region biome value at a given x, z & b coord
 */
char region_file_reader::get_biome_at(unsigned int x, unsigned int z, unsigned int b_x, unsigned int b_z) {
	std::vector<generic_tag *> biome;
	unsigned int pos = z * region_dim::CHUNK_WIDTH + x,
			b_pos = b_z * region_dim::BLOCK_WIDTH + b_x;

	// check coordinates
	if(pos >= region_dim::CHUNK_COUNT
			|| b_pos >= region_dim::BLOCK_COUNT)
		throw std::out_of_range("coordinates out-of-range");

	// collect biome tags
	biome = reg.get_tag_at(pos).get_sub_tag_by_name("Biomes");
	if(biome.empty())
		return 0;
	return static_cast<byte_array_tag *>(biome.at(0))->at(b_pos);
}

/*
 * Returns a region's biomes at a given x, z coord
 */
std::vector<char> region_file_reader::get_biomes_at(unsigned int x, unsigned int z) {
	std::vector<char> biomes;
	std::vector<generic_tag *> biome;
	unsigned int pos = z * region_dim::CHUNK_WIDTH + x;

	// check coordinates
	if(pos >= region_dim::CHUNK_COUNT)
		throw std::out_of_range("coordinates out-of-range");

	// collect biome tags
	biome = reg.get_tag_at(pos).get_sub_tag_by_name("Biomes");
	if(biome.empty())
		return biomes;
	return static_cast<byte_array_tag *>(biome.at(0))->get_value();
}

/*
 * Returns a region block value at given x, z & b coord
 */
int region_file_reader::get_block_at(unsigned int x, unsigned int z, unsigned int b_x, unsigned int b_y, unsigned int b_z) {
	std::vector<char> sect_blocks;
	std::vector<generic_tag *> section;
	unsigned int pos = z * region_dim::CHUNK_WIDTH + x, sect;

	// check coordinates
	if(pos >= region_dim::CHUNK_COUNT)
		throw std::out_of_range("coordinates out-of-range");
	section = reg.get_tag_at(pos).get_sub_tag_by_name("Blocks");

	// return an air block if no blocks exists in a given chunk
	if(section.empty())
		return 0;

	// check if y coord exists in file
	if((sect = b_y / region_dim::BLOCK_WIDTH) >= section.size())
		return 0;

	// retrieve block from the appropriate section
	sect_blocks = static_cast<byte_array_tag *>(section.at(sect))->get_value();

	// TODO: check for "AddBlock" tag and apply to block id

	return sect_blocks.at(((b_y % region_dim::BLOCK_WIDTH) * region_dim::BLOCK_WIDTH + b_z) * region_dim::BLOCK_WIDTH + b_x);
}

/*
 * Returns a region's blocks at a given x, z coord
 */
std::vector<int> region_file_reader::get_blocks_at(unsigned int x, unsigned int z) {
	std::vector<int> all_blocks;
	std::vector<char> sect_blocks;
	std::vector<generic_tag *> section;
	unsigned int pos = z * region_dim::CHUNK_WIDTH + x;

	// retrieve chunk data
	section = reg.get_tag_at(pos).get_sub_tag_by_name("Blocks");

	// return an empty vector if no blocks exists in a given chunk
	if(section.empty())
		return all_blocks;

	// iterate through a series of sections combining the blocks
	for(int i = section.size() - 1; i >= 0; --i) {
			sect_blocks = static_cast<byte_array_tag *>(section.at(i))->get_value();
			all_blocks.insert(all_blocks.begin(), sect_blocks.begin(), sect_blocks.end());
	}

	// TODO: check for "AddBlock" tag and apply to block ids

	return all_blocks;
}

/*
 * Returns a region's chunk tag at a given x, z coord
 */
chunk_tag &region_file_reader::get_chunk_tag_at(unsigned int x, unsigned int z) {
	unsigned int pos = z * region_dim::CHUNK_WIDTH + x;

	// check coordinates
	if(pos >= region_dim::CHUNK_COUNT)
		throw std::out_of_range("coordinates out-of-range");
	return reg.get_tag_at(pos);
}

/*
 * Returns a region height value at a given x, z & b coord
 */
int region_file_reader::get_height_at(unsigned int x, unsigned int z, unsigned int b_x, unsigned int b_z) {
	std::vector<generic_tag *> height;
	unsigned int pos = z * region_dim::CHUNK_WIDTH + x,
			b_pos = b_z * region_dim::BLOCK_WIDTH + b_x;

	// check coordinates
	if(pos >= region_dim::CHUNK_COUNT
			|| b_pos >= region_dim::BLOCK_COUNT)
		throw std::out_of_range("coordinates out-of-range");

	// collect biome tags
	height = reg.get_tag_at(pos).get_sub_tag_by_name("HeightMap");
	if(height.empty())
		return 0;
	return static_cast<int_array_tag *>(height.at(0))->at(b_pos);
}

/*
 * Returns a region's height map at a given x, z coord
 */
std::vector<int> region_file_reader::get_heightmap_at(unsigned int x, unsigned int z) {
	std::vector<int> heights;
	std::vector<generic_tag *> height;
	unsigned int pos = z * region_dim::CHUNK_WIDTH + x;

	// check coordinates
	if(pos >= region_dim::CHUNK_COUNT)
		throw std::out_of_range("coordinates out-of-range");

	// collect biome tags
	height = reg.get_tag_at(pos).get_sub_tag_by_name("HeightMap");
	if(height.empty())
		return heights;
	return static_cast<int_array_tag *>(height.at(0))->get_value();
}

/*
 * Return a region's filled status
 */
bool region_file_reader::is_filled(unsigned int x, unsigned int z) {
	unsigned int pos = z * region_dim::CHUNK_WIDTH + x;

	// check coordinates
	if(pos >= region_dim::CHUNK_COUNT)
		throw std::out_of_range("coordinates out-of-range");
	return reg.is_filled(pos);
}

/*
 * Read a tag from data
 */
generic_tag *region_file_reader::parse_tag(byte_stream &stream, bool is_list, char list_type) {
	char type;
	short name_len;
	std::string name;
	generic_tag *tag = NULL, *sub_tag = NULL;

	// check if stream is good
	if(!stream.good())
		throw std::runtime_error("Unexpected end of stream");

	// parse tag header
	if(is_list)
		type = list_type;
	else {
		type = read_value<char>(stream);
		if(type != generic_tag::END) {
			name_len = read_value<short>(stream);
			for(short i = 0; i < name_len; ++i)
				name += read_value<char>(stream);
		}
	}

	// parse tag based off type
	switch(type) {
		case generic_tag::END:
			tag = new end_tag;
			break;
		case generic_tag::BYTE:
			tag = new byte_tag(name, read_value<char>(stream));
			break;
		case generic_tag::SHORT:
			tag = new short_tag(name, read_value<short>(stream));
			break;
		case generic_tag::INT:
			tag = new int_tag(name, read_value<int>(stream));
			break;
		case generic_tag::LONG:
			tag = new long_tag(name, read_value<long>(stream));
			break;
		case generic_tag::FLOAT:
			tag = new float_tag(name, read_value<float>(stream));
			break;
		case generic_tag::DOUBLE:
			tag = new double_tag(name, read_value<double>(stream));
			break;
		case generic_tag::BYTE_ARRAY:
			tag = new byte_array_tag(name, read_array_value<char>(stream));
			break;
		case generic_tag::STRING:
			tag = new string_tag(name, read_string_value(stream));
			break;
		case generic_tag::LIST: {
			char ele_type = read_value<char>(stream);
			int ele_len = read_value<int>(stream);
			list_tag *lst_tag = new list_tag(name, ele_type);

			// parse all subtags and add to list
			for(int i = 0; i < ele_len; ++i) {
				sub_tag = parse_tag(stream, true, ele_type);
				lst_tag->push_back(sub_tag);
			}
			tag = lst_tag;
		} break;
		case generic_tag::COMPOUND: {
			compound_tag *cmp_tag = new compound_tag(name);

			// parse all sub_tags and add to compound
			do {
				sub_tag = parse_tag(stream, false, 0);
				if(!sub_tag)
					throw std::runtime_error("Failed to parse tag");
				if(sub_tag->get_type() != generic_tag::END)
					cmp_tag->push_back(sub_tag);
			} while(sub_tag->get_type() != generic_tag::END);
			delete sub_tag;
			tag = cmp_tag;
		} break;
		case generic_tag::INT_ARRAY:
			tag = new int_array_tag(name, read_array_value<int>(stream));
			break;
		default:
			throw std::runtime_error("Unknown tag type");
			break;
	}
	return tag;
}

/*
 * Read a chunk tag from data
 */
void region_file_reader::parse_chunk_tag(std::vector<char> &data, chunk_tag &tag) {
	char type;
	std::string name;
	generic_tag *sub_tag = NULL;

	// setup bytestream
	byte_stream bstream(data);
	bstream.set_swap(byte_stream::NO_SWAP_ENDIAN);

	// parse tags from root
	type = read_value<char>(bstream);
	if(type == generic_tag::END)
		return;
	else {
		short name_len = read_value<short>(bstream);
		for(short i = 0; i < name_len; ++i)
			name += read_value<char>(bstream);
		tag.get_root_tag().set_name(name);
		do {

			//parse subtag
			sub_tag = parse_tag(bstream, false, 0);
			if(!sub_tag)
				throw std::runtime_error("Failed to parse tag");
			if(sub_tag->get_type() != generic_tag::END)
				tag.get_root_tag().push_back(sub_tag);
		} while(sub_tag->get_type() != generic_tag::END);
		delete sub_tag;
	}
}

/*
 * Reads a file into region_file
 */
void region_file_reader::read(void) {
	int x, z;

	// attempt to open file
	file.open(path.c_str(), std::ios::in | std::ios::binary);
	if(!file.is_open())
		throw std::runtime_error("Failed to open input file");

	// parse the filename for coordinants
	if(!is_region_file(path, x, z))
		throw std::runtime_error("Malformated region filename");
	reg.set_x(x);
	reg.set_z(z);

	// read header data
	read_header();

	// read chunk data
	read_chunks();

	// close file
	file.close();
}

/*
 * Reads chunk data from a file
 */
void region_file_reader::read_chunks(void) {
	chunk_info info;

	// check if file is open
	if(!file.is_open())
		throw std::runtime_error("Failed to read chunk data");

	// iterate though header entries, reading in chunks if they exist
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i) {
		info = reg.get_header().get_info_at(i);

		// skip empty chunks
		if(info.empty())
			continue;

		// Retrieve raw data
		char raw_data[info.get_length()];
		std::vector<char> raw_vec;
		file.seekg(info.get_offset(), std::ios::beg);
		file.read((char *) raw_data, info.get_length());
		raw_vec.assign(raw_data, raw_data + info.get_length());

		// check for compression type
		switch(info.get_type()) {
		case chunk_info::GZIP:
			throw std::runtime_error("Unsupported compression type");
			break;
		case chunk_info::ZLIB:
			compression::inflate_(raw_vec);
			break;
		default:
			throw std::runtime_error("Unknown compression type");
			break;
		}

		// use data to fill chunk tag
		parse_chunk_tag(raw_vec, reg.get_tag_at(i));
	}
}

/*
 * Reads header data from a file
 */
void region_file_reader::read_header(void) {
	char type;
	int value;
	unsigned int offset;

	// check if file is open
	if(!file.is_open())
		throw std::runtime_error("Failed to read header data");

	// read position data into header
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i) {
		file.read(reinterpret_cast<char *>(&value), sizeof(value));
		convert_endian(value);
		reg.get_header().get_info_at(i).set_offset(value);
	}

	// read timestamp data into header
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i) {
		file.read(reinterpret_cast<char *>(&value), sizeof(value));
		convert_endian(value);
		reg.get_header().get_info_at(i).set_modified(value);
	}

	// read length and compression type data into header
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i) {
		offset = reg.get_header().get_info_at(i).get_offset();

		// skip all empty chunks
		if(!offset)
			continue;

		// collect length and compression data
		file.seekg((offset >> 8) * region_dim::SECTOR_SIZE, std::ios::beg);
		file.read(reinterpret_cast<char *>(&value), sizeof(value));
		convert_endian(value);
		reg.get_header().get_info_at(i).set_length(value);
		file.read(&type, sizeof(type));
		reg.get_header().get_info_at(i).set_type(type);
		reg.get_header().get_info_at(i).set_offset((unsigned int) file.tellg());
	}
}

/*
 * Reads a string tag value from stream
 */
std::string region_file_reader::read_string_value(byte_stream &stream) {
	short str_len;
	std::string value;

	// check stream status
	if(!stream.good())
		throw std::runtime_error("Unexpected end of stream");

	// retrieve value
	str_len = read_value<short>(stream);
	for(short i = 0; i < str_len; ++i)
		value += read_value<char>(stream);
	return value;
}
