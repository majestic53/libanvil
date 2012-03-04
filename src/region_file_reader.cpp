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
#include "region_chunk_info.hpp"
#include "region_file_reader.hpp"
#include "tag/byte_array_tag.hpp"
#include "tag/int_array_tag.hpp"
#include "tag/list_tag.hpp"

/*
 * Region file reader constructor
 */
region_file_reader::region_file_reader(void) : fill_count(0) {

	// assign attribute values
	for(unsigned int i = 0; i < region_dim::REGION_AREA; ++i)
		fill[i] = false;
}

/*
 * Region file reader constructor
 */
region_file_reader::region_file_reader(const region_file_reader &other): file(other.file), fill_count(other.fill_count) {

	// assign attribute values
	for(unsigned int i = 0; i < region_dim::REGION_AREA; ++i) {
		data[i] = other.data[i];
		fill[i] = other.fill[i];
	}
}

/*
 * Region file reader constructor
 */
region_file_reader::region_file_reader(const std::string &path) {
	unsigned int pos;
	region_chunk_info info;

	// open file at path
	file = region_file(path);
	fill_count = 0;

	// assign attribute values
	for(unsigned int z = 0; z < region_dim::REGION_Z; ++z)
		for(unsigned int x = 0; x < region_dim::REGION_X; ++x) {
			pos = z * region_dim::REGION_Z + x;
			file.get_chunk_info(x, z, info);
			if(!info.get_position()) {
				fill[pos] = false;
				continue;
			}
			fill[pos] = true;
			fill_count++;
		}
}

/*
 * Region file reader assignment
 */
region_file_reader &region_file_reader::operator=(const region_file_reader &other) {

	// check for self
	if(this == &other)
		return *this;

	// assign all attributes
	fill_count = other.fill_count;
	file = other.file;
	for(unsigned int i = 0; i < region_dim::REGION_AREA; ++i) {
		fill[i] = other.fill[i];
		data[i] = other.data[i];
	}
	return *this;
}

/*
 * Region file reader equals
 */
bool region_file_reader::operator==(const region_file_reader &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	if(fill_count != other.fill_count
			|| file != other.file)
		return false;
	for(unsigned int i = 0; i < region_dim::REGION_AREA; ++i)
		if(data[i] != other.data[i]
		                         || fill[i] != other.fill[i])
			return false;
	return true;
}

/*
 * Cache data at coord if not already cached
 */
void region_file_reader::cache_coord(unsigned int x, unsigned int z, unsigned int pos) {

	// retrieve chunk data if it is not cached
	if(fill[pos]
	        && data[pos].empty())
		file.get_chunk_tag(x, z, data[pos]);
}

/*
 * Returns a chunk tag biome value at a given x, z & b coord
 */
int8_t region_file_reader::get_biome_at(unsigned int x, unsigned int z, unsigned int b_x, unsigned int b_z) {
	std::vector<generic_tag *> biome;
	unsigned int pos = varify_coord(x, z, region_dim::REGION_X, region_dim::REGION_AREA),
			b_pos = varify_coord(b_x, b_z, region_dim::CHUNK_X, region_dim::CHUNK_AREA);

	// retrieve chunk data if it is not cached
	cache_coord(x, z, pos);
	biome = data[pos].get_tag_by_name("Biomes");

	// return a zero biome value if no biomes exist
	if(biome.empty())
		return 0;

	return static_cast<byte_array_tag *>(biome.at(0))->value.at(b_pos);
}

/*
 * Returns a chunk tag biomes at a given x, z coord
 */
std::vector<int8_t> region_file_reader::get_biomes_at(unsigned int x, unsigned int z) {
	std::vector<generic_tag *> biome;
	std::vector<int8_t> biomes;
	unsigned int pos = varify_coord(x, z, region_dim::REGION_X, region_dim::REGION_AREA);

	// retrieve chunk data if it is not cached
	cache_coord(x, z, pos);
	biome = data[pos].get_tag_by_name("Biomes");

	// return an empty biome vector if no biomes exist
	if(biome.empty())
		return biomes;

	return static_cast<byte_array_tag *>(biome.at(0))->value;
}

/*
 * Returns a chunk tag height value at a given x, z & b coord
 */
int32_t region_file_reader::get_height_at(unsigned int x, unsigned int z, unsigned int b_x, unsigned int b_z) {
	std::vector<generic_tag *> heights;
	unsigned int pos = varify_coord(x, z, region_dim::REGION_X, region_dim::REGION_AREA),
			b_pos = varify_coord(b_x, b_z, region_dim::CHUNK_X, region_dim::CHUNK_AREA);

	// retrieve chunk data if it is not cached
	cache_coord(x, z, pos);
	heights = data[pos].get_tag_by_name("HeightMap");

	// return a zero height value if no heightmap exists
	if(heights.empty())
		return 0;

	return static_cast<int_array_tag *>(heights.at(0))->value.at(b_pos);
}

/*
 * Returns a chunk tag height map at a given x, z coord
 */
std::vector<int32_t> region_file_reader::get_heightmap_at(unsigned int x, unsigned int z) {
	std::vector<int32_t> height_blocks;
	std::vector<generic_tag *> heights;
	unsigned int pos = varify_coord(x, z, region_dim::REGION_X, region_dim::REGION_AREA);

	// retrieve chunk data if it is not cached
	cache_coord(x, z, pos);
	heights = data[pos].get_tag_by_name("HeightMap");

	// return an empty heightmap vector if no heightmap exists
	if(heights.empty())
		return height_blocks;

	return static_cast<int_array_tag *>(heights.at(0))->value;
}

/*
 * Returns a chunk tag block value at given x, z & b coord
 */
int32_t region_file_reader::get_block_at(unsigned int x, unsigned int z, unsigned int b_x, unsigned int b_y, unsigned int b_z) {
	unsigned int sect;
	std::vector<int8_t> sect_blocks;
	std::vector<generic_tag *> section;

	unsigned int pos = varify_coord(x, z, region_dim::REGION_X, region_dim::REGION_AREA);

	// retrieve chunk data if it is not cached
	cache_coord(x, z, pos);
	section = data[pos].get_tag_by_name("Blocks");

	// return an air block if no blocks exists in a given chunk
	if(section.empty())
		return 0;

	// check if y coord exists in file
	if((sect = b_y / region_dim::SECTION_Y) >= section.size())
		return 0;

	// retrieve block from the appropriate section
	sect_blocks = static_cast<byte_array_tag *>(section.at(sect))->value;

	// TODO: check for "AddBlock" tag and apply to block id

	return sect_blocks.at(((b_y % 16) * 16 + b_z) * 16 + b_x);
}

/*
 * Returns chunk tag blocks at a given x, z coord
 */
std::vector<int32_t> region_file_reader::get_blocks_at(unsigned int x, unsigned int z) {
	std::vector<generic_tag *> section;
	std::vector<int8_t> sect_blocks;
	std::vector<int32_t> all_blocks;
	unsigned int pos = varify_coord(x, z, region_dim::REGION_X, region_dim::REGION_AREA);

	// retrieve chunk data if it is not cached
	cache_coord(x, z, pos);
	section = data[pos].get_tag_by_name("Blocks");

	// return an empty vector if no blocks exists in a given chunk
	if(section.empty())
		return all_blocks;

	// iterate through a series of sections combining the blocks
	for(int i = section.size() - 1; i >= 0; --i) {
			sect_blocks = static_cast<byte_array_tag *>(section.at(i))->value;
			all_blocks.insert(all_blocks.begin(), sect_blocks.begin(), sect_blocks.end());
	}

	// TODO: check for "AddBlock" tag and apply to block ids

	return all_blocks;
}

/*
 * Returns a chunk tag at a given x, z coord
 */
region_chunk_tag &region_file_reader::get_tag_at(unsigned int x, unsigned int z) {
	unsigned int pos = varify_coord(x, z, region_dim::REGION_X, region_dim::REGION_AREA);

	// retrieve chunk data if it is not cached
	cache_coord(x, z, pos);
	return data[pos];
}

/*
 * Returns a string representation of a region file reader
 */
std::string region_file_reader::to_string(void) {
	std::stringstream ss;

	// form string representation
	ss << "filled: " << fill_count << "/" << region_dim::REGION_AREA;
	if(!file.get_path().empty())
		ss << ", path: " << file.get_path();
	return ss.str();
}

/*
 * Varify that chunk coord are valid
 */
unsigned int region_file_reader::varify_coord(unsigned int x, unsigned int z, unsigned int width, unsigned max) {
	unsigned int pos = z * width + x;

	// check if x, z coord are out-of-bounds
	if(pos >= max) {
		unsigned int coord[] = {x, z};
		std::vector<unsigned int> coord_vec(coord, coord + 2);
		throw region_file_exc(region_file_exc::OUT_OF_BOUNDS, coord_vec);
	}
	return pos;
}
