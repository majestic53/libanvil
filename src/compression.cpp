/*
 * compression.cpp
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

#include <cstring>
#include <zlib.h>
#include "compression.hpp"

/*
 * Deflate a char buffer
 */
bool compression::deflate_(std::vector<char> &data) {
	int ret;
	z_stream zs;
	char buff[SEG_SIZE];
	std::vector<char> out_data;

	// initialize zlib structure
	memset(&zs, 0, sizeof(zs));
	if(deflateInit(&zs, Z_BEST_COMPRESSION) != Z_OK)
		return false;
	zs.next_in = (Bytef *) data.data();
	zs.avail_in = data.size();

	// deflate blocks
	do {
		zs.next_out = reinterpret_cast<Bytef *>(buff);
		zs.avail_out = SEG_SIZE;

		// deflate data and place in out_data
		ret = deflate(&zs, Z_FINISH);
		out_data.insert(out_data.end(), buff, buff + zs.total_out);
	} while(ret == Z_OK);

	// check for errors
	deflateEnd(&zs);
	if (ret != Z_STREAM_END)
		return false;

	// assign to data
	data = out_data;
	return true;
}

/*
 * Inflate a char buffer
 */
bool compression::inflate_(std::vector<char> &data) {
	int ret;
	z_stream zs;
	char buff[SEG_SIZE];
	std::vector<char> out_data;
	unsigned long prev_out = 0;

	// initialize zlib structure
	memset(&zs, 0, sizeof(zs));
	if(inflateInit(&zs) != Z_OK)
		return false;

	zs.next_in = (Bytef *) data.data();
	zs.avail_in = data.size();

	// inflate blocks
	do {
		zs.next_out = reinterpret_cast<Bytef *>(buff);
		zs.avail_out = SEG_SIZE;

		// inflate data and place in out_data
		ret = inflate(&zs, 0);
		out_data.insert(out_data.end(), buff, buff + (zs.total_out - prev_out));
		prev_out = zs.total_out;
	} while(ret == Z_OK);

	// check for errors
	inflateEnd(&zs);
	if (ret != Z_STREAM_END)
		return false;

	// assign to data
	data = out_data;
	return true;
}
