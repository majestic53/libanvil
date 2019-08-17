LibAnvil
=

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)

Libanvil is a C++ library for reading and writing Minecraft "Anvil" files

Table of Contents
=

1. [About](https://github.com/majestic53/libanvil#about) -- About the project
2. [Building](https://github.com/majestic53/libanvil#building) -- How to build the project
2. [Building](https://github.com/majestic53/libanvil#usage) -- How to use the project
3. [Changelog](https://github.com/majestic53/libanvil#changelog) -- Log of project changes

About
=

The project is implemented in C++ and exposes a simple API, described in ```include/region*.h``` and ```libanvil.a```.

### What It Can Do


* Open Minecraft "Anvil" map files (.mca)
* Retrieve various bits of data (per chunk):
	* Biome data at a given x, z coord
	* HeightMap data at a given x, z coord
	* Block data at a given x, y, z coord
	* (or any tag with a known name)

### What It Can't Do

* Read extended block ids (ie. those blocks that use the "AddBlocks" tag)
	* This will be fixed soon, once more information becomes available!
* Create/Write .mca files

Building
=

Instructions for compiling libanvil from source code

### Requirements (tested on)

* g++ 4.4.3 or newer
* make 3.8 or newer
* boost regex 1.42 or newer
* zlib 1.2.3.3 or newer

### For Debian

```
sudo apt-get install build-essential make zlib-dev libboost1.42-all-dev
```

### Building (produces a static lib)

```
make
```

### To use static library

```
g++ -o <EXECUTABLE NAME> <MAIN>.cpp -std=c++0x -lboost_regex -lz -I <PATH_TO_LIBNBT> -L <PATH_TO_LIBNBT> -lanvil
```

Usage
=

The easiest way to access block/heightmap data for each chunk is to use the region_file_reader object. No cleanup is necessary. All allocations/deallocations are handled internally within the reader.

### To instantiate a region_file_reader object, either

```c
region_file_reader reader;
reader = region_file_reader("path-to-region-file");
```

OR

```
region_file_reader reader("path-to-region-file");
```

### To read in block/heightmap data

```c
std::vector<int> blocks, heights;

...

blocks = reader.get_blocks_at(x, z);
heights = reader.get_heightmap_at(x, z);
```

### Parsing block/heightmap data

Data is stored in the chunks from the top-left to bottom right, and all coord are relative to the chunk itself.

```
Block {x, y, z} = (y * 16 + z) * 16 + x
HeightMap {x, z} = x + z * 16
```

### Putting it all together

```c
#include <iostream>
#include <stdexcept>
#include <vector>
#include "region_file_reader.h"

int main(int argc, char *argv[]) {

	// instantiate a file reader
	region_file_reader reader;

	// create vectors to hold block/height data
	std::vector<int> blocks, heights;

	try {

		// open a region file
		reader = region_file_reader("path-to-region-file");
		reader.read();

		// iterate through all possible chunks within a region
		for(unsigned int z = 0; z < 32; ++z)
			for(unsigned int x = 0; x < 32; ++x) {

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
		return 1;
	}
	return 0;
}
```

Changelog
=

### Version 0.1.1933

*Updated: 8/16/2019*

* Project refactoring

### Version 0.1.1705

*Updated: 2/6/2017*

* Minor bug fix in long NBT tag
* Updated documentation

*Changelog truncated (see file history for full log)*
