# LibAnvil
# Copyright (C) 2012 - 2020 David Jolly
#
# LibAnvil is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# LibAnvil is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

DIR_BIN_LIB=../bin/lib/
DIR_BUILD=../build/
DIR_INC=../include/
DIR_INC_TAG=../include/tag/
DIR_SRC=./
DIR_SRC_TAG=./tag/
FLAGS=-march=native -std=c++0x -Wall -Werror
LIB=libanvil.a

all: build archive

### LIBRARY ###

archive:
	@echo ''
	@echo '--- BUILDING LIBRARY -----------------------'

	ar rcs $(DIR_BIN_LIB)$(LIB) $(DIR_BUILD)base_byte_stream.o $(DIR_BUILD)base_chunk_info.o $(DIR_BUILD)base_chunk_tag.o \
			$(DIR_BUILD)base_compression.o $(DIR_BUILD)base_region.o $(DIR_BUILD)base_region_file.o \
			$(DIR_BUILD)base_region_file_reader.o $(DIR_BUILD)base_region_file_writer.o $(DIR_BUILD)base_region_header.o \
		$(DIR_BUILD)tag_byte_array_tag.o $(DIR_BUILD)tag_byte_tag.o $(DIR_BUILD)tag_compound_tag.o $(DIR_BUILD)tag_double_tag.o \
			$(DIR_BUILD)tag_end_tag.o $(DIR_BUILD)tag_float_tag.o $(DIR_BUILD)tag_generic_tag.o $(DIR_BUILD)tag_int_array_tag.o \
			$(DIR_BUILD)tag_int_tag.o $(DIR_BUILD)tag_list_tag.o $(DIR_BUILD)tag_long_tag.o $(DIR_BUILD)tag_long_array_tag.o \
			$(DIR_BUILD)tag_short_tag.o $(DIR_BUILD)tag_string_tag.o
	@echo '--- DONE -----------------------------------'

build: build_base build_tag

### BASE ###

build_base: base_byte_stream.o base_chunk_info.o base_chunk_tag.o base_compression.o base_region.o base_region_file.o base_region_file_reader.o \
	base_region_file_writer.o base_region_header.o

base_byte_stream.o: $(DIR_SRC)byte_stream.cpp $(DIR_INC)byte_stream.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC)byte_stream.cpp -o $(DIR_BUILD)base_byte_stream.o

base_chunk_info.o: $(DIR_SRC)chunk_info.cpp $(DIR_INC)chunk_info.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC)chunk_info.cpp -o $(DIR_BUILD)base_chunk_info.o

base_chunk_tag.o: $(DIR_SRC)chunk_tag.cpp $(DIR_INC)chunk_tag.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC)chunk_tag.cpp -o $(DIR_BUILD)base_chunk_tag.o

base_compression.o: $(DIR_SRC)compression.cpp $(DIR_INC)compression.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC)compression.cpp -o $(DIR_BUILD)base_compression.o

base_region.o: $(DIR_SRC)region.cpp $(DIR_INC)region.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC)region.cpp -o $(DIR_BUILD)base_region.o

base_region_file.o: $(DIR_SRC)region_file.cpp $(DIR_INC)region_file.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC)region_file.cpp -o $(DIR_BUILD)base_region_file.o

base_region_file_reader.o: $(DIR_SRC)region_file_reader.cpp $(DIR_INC)region_file_reader.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC)region_file_reader.cpp -o $(DIR_BUILD)base_region_file_reader.o

base_region_file_writer.o: $(DIR_SRC)region_file_writer.cpp $(DIR_INC)region_file_writer.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC)region_file_writer.cpp -o $(DIR_BUILD)base_region_file_writer.o

base_region_header.o: $(DIR_SRC)region_header.cpp $(DIR_INC)region_header.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC)region_header.cpp -o $(DIR_BUILD)base_region_header.o

### TAG ###

build_tag: tag_byte_array_tag.o tag_byte_tag.o tag_compound_tag.o tag_double_tag.o tag_end_tag.o tag_float_tag.o tag_generic_tag.o \
	tag_int_array_tag.o tag_int_tag.o tag_list_tag.o tag_long_tag.o tag_long_array_tag.o tag_short_tag.o tag_string_tag.o

tag_byte_array_tag.o: $(DIR_SRC_TAG)byte_array_tag.cpp $(DIR_INC_TAG)byte_array_tag.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC_TAG)byte_array_tag.cpp -o $(DIR_BUILD)tag_byte_array_tag.o

tag_byte_tag.o: $(DIR_SRC_TAG)byte_tag.cpp $(DIR_INC_TAG)byte_tag.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC_TAG)byte_tag.cpp -o $(DIR_BUILD)tag_byte_tag.o

tag_compound_tag.o: $(DIR_SRC_TAG)compound_tag.cpp $(DIR_INC_TAG)compound_tag.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC_TAG)compound_tag.cpp -o $(DIR_BUILD)tag_compound_tag.o

tag_double_tag.o: $(DIR_SRC_TAG)double_tag.cpp $(DIR_INC_TAG)double_tag.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC_TAG)double_tag.cpp -o $(DIR_BUILD)tag_double_tag.o

tag_end_tag.o: $(DIR_SRC_TAG)end_tag.cpp $(DIR_INC_TAG)end_tag.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC_TAG)end_tag.cpp -o $(DIR_BUILD)tag_end_tag.o

tag_float_tag.o: $(DIR_SRC_TAG)float_tag.cpp $(DIR_INC_TAG)float_tag.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC_TAG)float_tag.cpp -o $(DIR_BUILD)tag_float_tag.o

tag_generic_tag.o: $(DIR_SRC_TAG)generic_tag.cpp $(DIR_INC_TAG)generic_tag.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC_TAG)generic_tag.cpp -o $(DIR_BUILD)tag_generic_tag.o

tag_int_array_tag.o: $(DIR_SRC_TAG)int_array_tag.cpp $(DIR_INC_TAG)int_array_tag.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC_TAG)int_array_tag.cpp -o $(DIR_BUILD)tag_int_array_tag.o

tag_int_tag.o: $(DIR_SRC_TAG)int_tag.cpp $(DIR_INC_TAG)int_tag.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC_TAG)int_tag.cpp -o $(DIR_BUILD)tag_int_tag.o

tag_list_tag.o: $(DIR_SRC_TAG)list_tag.cpp $(DIR_INC_TAG)list_tag.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC_TAG)list_tag.cpp -o $(DIR_BUILD)tag_list_tag.o

tag_long_tag.o: $(DIR_SRC_TAG)long_tag.cpp $(DIR_INC_TAG)long_tag.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC_TAG)long_tag.cpp -o $(DIR_BUILD)tag_long_tag.o

tag_long_array_tag.o: $(DIR_SRC_TAG)long_array_tag.cpp $(DIR_INC_TAG)long_array_tag.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC_TAG)long_array_tag.cpp -o $(DIR_BUILD)tag_long_array_tag.o

tag_short_tag.o: $(DIR_SRC_TAG)short_tag.cpp $(DIR_INC_TAG)short_tag.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC_TAG)short_tag.cpp -o $(DIR_BUILD)tag_short_tag.o

tag_string_tag.o: $(DIR_SRC_TAG)string_tag.cpp $(DIR_INC_TAG)string_tag.h
	$(CXX) $(FLAGS) $(BUILD_FLAGS) -c $(DIR_SRC_TAG)string_tag.cpp -o $(DIR_BUILD)tag_string_tag.o
