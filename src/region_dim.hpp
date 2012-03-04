/*
 * region_dim.hpp
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

#ifndef REGION_DIM_HPP_
#define REGION_DIM_HPP_

class region_dim {
public:

	/*
	 * Max block id
	 */
	static const unsigned int MAX_BLOCK_ID = 4096;

	/*
	 * Chunk section dimensions
	 */
	static const unsigned int SECTION_X = 16;
	static const unsigned int SECTION_Z = 16;
	static const unsigned int SECTION_Y = 16;
	static const unsigned int SECTION_VOL = 4096;

	/*
	 * Chunk section count
	 */
	static const unsigned int SECTION_COUNT = 16;

	/*
	 * Chunk dimensions
	 */
	static const unsigned int CHUNK_X = 16;
	static const unsigned int CHUNK_Z = 16;
	static const unsigned int CHUNK_Y = 256;

	/*
	 * Chunk size
	 */
	static const unsigned int CHUNK_AREA = 256;

	/*
	 * Region dimensions
	 */
	static const unsigned int REGION_X = 32;
	static const unsigned int REGION_Z = 32;

	/*
	 * Region size
	 */
	static const unsigned int REGION_AREA = 1024;
};

#endif
