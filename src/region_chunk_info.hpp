/*
 * region_chunk_info.hpp
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

#ifndef REGION_CHUNK_INFO_HPP_
#define REGION_CHUNK_INFO_HPP_

#include <ctime>
#include <string>

class region_chunk_info {
private:

	/*
	 * Chunk last modified time
	 */
	time_t modified;

	/*
	 * Chunk size, position & compression type
	 */
	unsigned int pos, size, type;

public:

	/*
	 * Compression types
	 */
	enum COMPRESSION { UNDEFINED, GZIP, ZLIB };

	/*
	 * Region chunk info constructor
	 */
	region_chunk_info(void);

	/*
	 * Region chunk info constructor
	 */
	region_chunk_info(const region_chunk_info &other);

	/*
	 * Region chunk info constructor
	 */
	region_chunk_info(unsigned int type, unsigned int size, unsigned int pos, time_t modified) : modified(modified), pos(pos), size(size), type(type) { return; }

	/*
	 * Region chunk info destructor
	 */
	virtual ~region_chunk_info(void) { return; }

	/*
	 * Region chunk info assignment
	 */
	region_chunk_info &operator=(const region_chunk_info &other);

	/*
	 * Region chunk info equals
	 */
	bool operator==(const region_chunk_info &other);


	/*
	 * Region chunk info not equals
	 */
	bool operator!=(const region_chunk_info &other) { return !(*this == other); }

	/*
	 * Returns region chunk info filled status
	 */
	bool filled(void) { return pos; }

	/*
	 * Returns a region chunk info's last modified time
	 */
	time_t get_modified(void) { return modified; }

	/*
	 * Returns a region chunk info's position
	 */
	unsigned int get_position(void) { return pos; }

	/*
	 * Returns a region chunk info's size
	 */
	unsigned int get_size(void) { return size; }

	/*
	 * Returns a region chunk info's type
	 */
	unsigned int get_type(void) { return type; }

	/*
	 * Sets a region chunk info's last modified time
	 */
	void set_modified(time_t modified) { this->modified = modified; }

	/*
	 * Sets a region chunk info's position
	 */
	void set_position(unsigned int pos) { this->pos = pos; }

	/*
	 * Sets a region chunk info's size
	 */
	void set_size(unsigned int size) { this->size = size; }

	/*
	 * Sets a region chunk info's type
	 */
	void set_type(unsigned int type) { this->type = type; }

	/*
	 * Returns a string representation of a region chunk info
	 */
	std::string to_string(void);
};

#endif
