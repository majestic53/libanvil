/*
 * region_file_reader.hpp
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

#ifndef REGION_FILE_READER_HPP_
#define REGION_FILE_READER_HPP_

#include <cstdint>
#include <string>
#include <vector>
#include "region_chunk_tag.hpp"
#include "region_dim.hpp"
#include "region_file.hpp"
#include "region_file_exc.hpp"

class region_file_reader {
private:

	/*
	 * Chunk tag data
	 */
	region_chunk_tag data[region_dim::REGION_AREA];

	/*
	 * Region file
	 */
	region_file file;

	/*
	 * Chunk fill count
	 */
	unsigned int fill_count;

	/*
	 * Chunk fill status
	 */
	bool fill[region_dim::REGION_AREA];

	/*
	 * Cache data at coord if not already cached
	 */
	void cache_coord(unsigned int x, unsigned int z, unsigned int pos);

	/*
	 * Varify that chunk coord are valid
	 */
	unsigned int varify_coord(unsigned int x, unsigned int z, unsigned int width, unsigned int max);

public:

	/*
	 * Region file reader constructor
	 */
	region_file_reader(void);

	/*
	 * Region file reader constructor
	 */
	region_file_reader(const region_file_reader &other);

	/*
	 * Region file reader constructor
	 */
	region_file_reader(const std::string &path);

	/*
	 * Region file reader destructor
	 */
	virtual ~region_file_reader(void) { return; }

	/*
	 * Region file reader assignment
	 */
	region_file_reader &operator=(const region_file_reader &other);

	/*
	 * Region file reader equals
	 */
	bool operator==(const region_file_reader &other);

	/*
	 * Region file reader not equals
	 */
	bool operator!=(const region_file_reader &other) { return !(*this == other); }

	/*
	 * Returns a chunk tag biome value at a given x, z & b coord
	 */
	int8_t get_biome_at(unsigned int x, unsigned int z, unsigned int b_x, unsigned int b_z);

	/*
	 * Returns a chunk tag biomes at a given x, z coord
	 */
	std::vector<int8_t> get_biomes_at(unsigned int x, unsigned int z);

	/*
	 * Returns a chunk tag height value at a given x, z & b coord
	 */
	int32_t get_height_at(unsigned int x, unsigned int z, unsigned int b_x, unsigned int b_z);

	/*
	 * Returns a chunk tag height map at a given x, z coord
	 */
	std::vector<int32_t> get_heightmap_at(unsigned int x, unsigned int z);

	/*
	 * Returns a chunk tag block value at given x, z & b coord
	 */
	int32_t get_block_at(unsigned int x, unsigned int z, unsigned int b_x, unsigned int b_y, unsigned int b_z);

	/*
	 * Returns chunk tag blocks at a given x, z coord
	 */
	std::vector<int32_t> get_blocks_at(unsigned int x, unsigned int z);

	/*
	 * Returns a chunk tag at a given x, z coord
	 */
	region_chunk_tag &get_tag_at(unsigned int x, unsigned int z);

	/*
	 * Returns a region file readers path
	 */
	region_file &get_file(void) { return file; }

	/*
	 * Returns a region file readers fill count
	 */
	unsigned int get_fill_count(void) { return fill_count; }

	/*
	 * Returns a region x coord
	 */
	int get_x_coord(void) { return file.get_region_x_coord(); }

	/*
	 * Returns a region z coord
	 */
	int get_z_coord(void) { return file.get_region_z_coord(); }

	/*
	 * Returns fill status at a given x, z coord
	 */
	bool is_filled(unsigned int x, unsigned int z) { return fill[varify_coord(x, z, region_dim::REGION_X, region_dim::REGION_AREA)]; }

	/*
	 * Returns a string representation of a region file reader
	 */
	std::string to_string(void);
};

#endif
