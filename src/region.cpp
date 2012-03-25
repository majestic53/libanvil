/*
 * region.cpp
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
#include "region.hpp"
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
 * Region constructor
 */
region::region(const region &other) : header(other.header), x(x), z(z) {

	// assign attributes
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i)
		tags[i] = other.tags[i];
}

/*
 * Region constructor
 */
region::region(int x, int z, const region_header &header, const chunk_tag (&tags)[region_dim::CHUNK_COUNT]) : header(header), x(x), z(z) {

	// assign attributes
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i)
		this->tags[i] = tags[i];
}

/*
 * Region assignment operator
 */
region &region::operator=(const region &other) {

	// check for self
	if(this == &other)
		return *this;

	// assign attributes
	header = other.header;
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i)
		tags[i] = other.tags[i];
	x = other.x;
	z = other.z;
	return *this;
}

/*
 * Region equals operator
 */
bool region::operator==(const region &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	if(header != other.header
			|| x != other.x
			|| z != other.z)
		return false;
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i)
		if(tags[i] != other.tags[i])
			return false;
	return true;
}

/*
 * Generate a new region
 */
void region::generate(int x, int z, region &reg) {

	// cleanup old tags and assign new chunks
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i) {
		reg.get_tag_at(i).clean_root();
		reg.get_tag_at(i) = chunk_tag();
		reg.get_header().set_info_at(i, chunk_info(0, 0, chunk_info::ZLIB, 0));
	}
	reg.set_x(x);
	reg.set_z(z);
}


/*
 * Generate a new chunk in a region
 */
void region::generate_chunk(unsigned int x, unsigned int z, region &reg) {
	unsigned char count;
	unsigned int length, offset;
	unsigned int pos = region_dim::HEADER_OFFSET;
	unsigned int index = z * region_dim::CHUNK_WIDTH + x;

	// check for valid index
	if(index >= region_dim::CHUNK_COUNT)
		throw std::out_of_range("index out-of-range");

	// cleanup old tags and assign new chunk
	reg.get_tag_at(index).clean_root();
	reg.get_tag_at(index) = chunk_tag();

	// generate new sub-tags
	compound_tag *level = new compound_tag("Level");
	list_tag *entities = new list_tag("Entities", generic_tag::COMPOUND),
			*tile_entities = new list_tag("TileEntities", generic_tag::COMPOUND),
			*sections = new list_tag("Sections", generic_tag::COMPOUND);
	byte_array_tag *biomes = new byte_array_tag("Biomes");
	long_tag *last_updated = new long_tag("LastUpdate");
	int_tag *x_pos = new int_tag("xPos"),
			*z_pos = new int_tag("zPos");
	byte_tag *terrain_populated = new byte_tag("TerrainPopulated");
	int_array_tag *height_map = new int_array_tag("HeightMap");
	if(!level
			|| !entities
			|| !tile_entities
			|| !sections
			|| !biomes
			|| !last_updated
			|| !x_pos
			|| !z_pos
			|| !terrain_populated
			|| !height_map)
		throw std::runtime_error("Failed to allocate new tag(s)");

	// assign new sub-tags to root
	level->push_back(entities);
	level->push_back(biomes);
	level->push_back(last_updated);
	level->push_back(x_pos);
	level->push_back(z_pos);
	level->push_back(tile_entities);
	level->push_back(terrain_populated);
	level->push_back(height_map);
	level->push_back(sections);
	reg.get_tag_at(index).get_root_tag().push_back(level);

	// update header to reflect changes
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i) {

		// skip over unfilled chunks
		if(!reg.is_filled(i)
				&& i != index)
			continue;
		length = reg.get_tag_at(i).get_data().size();
		count = (length / region_dim::SECTOR_SIZE) + 1;
		offset = pos / region_dim::SECTOR_SIZE;
		reg.get_header().set_info_at(i, chunk_info((offset << 8) | count, length, chunk_info::ZLIB, 0));
		pos += count * region_dim::SECTOR_SIZE;
	}
}

/*
 * Returns a region's tag at a given index
 */
chunk_tag &region::get_tag_at(unsigned int index) {

	// check for valid index
	if(index >= region_dim::CHUNK_COUNT)
		throw std::out_of_range("index out-of-range");
	return tags[index];
}

/*
 * Returns a region's chunk filled status
 */
bool region::is_filled(unsigned int index) {

	// check for valid index
	if(index >= region_dim::CHUNK_COUNT)
		throw std::out_of_range("index out-of-range");
	return !header.get_info_at(index).empty();
}

/*
 * Sets a region's tags
 */
void region::set_tags(const chunk_tag (&tags)[region_dim::CHUNK_COUNT]) {

	// set info
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i)
		this->tags[i] = tags[i];
}

/*
 * Sets a region tag at a given index
 */
void region::set_tag_at(unsigned int index, chunk_tag &tag) {

	// check for valid index
	if(index >= region_dim::CHUNK_COUNT)
		throw std::out_of_range("index out-of-range");
	tags[index] = tag;
}

/*
 * Returns a string representation of a region
 */
std::string region::to_string(void) {
	std::stringstream ss;

	// form string representation
	ss << "(" << x << ", " << z << "): " << header.to_string() << std::endl;
	for(unsigned int i = 0; i < region_dim::CHUNK_COUNT; ++i) {
		if(header.get_info_at(i).empty())
			continue;
		ss << i << ": " << header.get_info_at(i).to_string() << std::endl;
	}
	return ss.str();
}
