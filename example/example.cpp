/*
 * LibAnvil
 * Copyright (C) 2012 - 2020 David Jolly
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

#include <iostream>
#include <stdexcept>
#include <vector>
#include "../include/region_file_reader.h"

int
main(int argc, char *argv[]) {

	// instantiate a file reader
	region_file_reader reader;

	// sanity check
	if(argc != 2) {
		std::cerr << "Usage: anvil <path-to-region-file>" << std::endl;
		return EXIT_FAILURE;
	}

	try {

		// open a region file
		reader = region_file_reader(argv[1]);
		reader.read();

		// iterate through all possible chunks within a region
		for(unsigned int z = 0; z < region_dim::CHUNK_WIDTH; ++z)
			for(unsigned int x = 0; x < region_dim::CHUNK_WIDTH; ++x) {

				// create vectors to hold block/height data
				std::vector<int> blocks, heights;

				// this keeps an exception from being thrown
				// when a non-existant chunk is requested
				if(!reader.is_filled(x, z))
					continue;

				// if everything goes well, retrieve the block/height data
				blocks = reader.get_blocks_at(x, z);
				heights = reader.get_heightmap_at(x, z);

				// ...
			}

	// catch all exception that may occur
	} catch(std::runtime_error &exc) {
		std::cerr << exc.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
