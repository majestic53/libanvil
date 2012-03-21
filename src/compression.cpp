/*
 * compression.cpp
 *
 *  Created on: Mar 18, 2012
 *      Author: david
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
