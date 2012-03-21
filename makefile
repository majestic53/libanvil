# Libanvil Makefile
# Copyright (C) 2012 David Jolly

CC=g++
SRC=src/
TAG=src/tag/
OUT=libanvil.a
FLAG=-std=c++0x -O3 -funroll-all-loops

all: tag anvil build

build: 
	ar rcs $(OUT) $(SRC)byte_stream.o $(SRC)chunk_info.o $(SRC)chunk_tag.o $(SRC)compression.o $(SRC)region.o $(SRC)region_file.o $(SRC)region_file_reader.o $(SRC)region_file_writer.o $(SRC)region_header.o $(TAG)byte_array_tag.o $(TAG)byte_tag.o $(TAG)compound_tag.o $(TAG)double_tag.o $(TAG)end_tag.o $(TAG)float_tag.o $(TAG)generic_tag.o $(TAG)int_array_tag.o $(TAG)int_tag.o $(TAG)list_tag.o $(TAG)long_tag.o $(TAG)short_tag.o $(TAG)string_tag.o

clean:
	rm -f $(OUT)
	rm -f $(SRC)*.o
	rm -f $(TAG)*.o

anvil: byte_stream.o chunk_info.o chunk_tag.o compression.o region.o region_file.o region_file_reader.o region_file_writer.o region_header.o

byte_array_tag.o: $(TAG)byte_array_tag.cpp $(TAG)byte_array_tag.hpp
	$(CC) $(FLAG) -c $(TAG)byte_array_tag.cpp -o $(TAG)byte_array_tag.o

byte_stream.o: $(SRC)byte_stream.cpp $(SRC)byte_stream.hpp
	$(CC) $(FLAG) -c $(SRC)byte_stream.cpp -o $(SRC)byte_stream.o

byte_tag.o: $(TAG)byte_tag.cpp $(TAG)byte_tag.hpp
	$(CC) $(FLAG) -c $(TAG)byte_tag.cpp -o $(TAG)byte_tag.o

chunk_info.o: $(SRC)chunk_info.cpp $(SRC)chunk_info.hpp
	$(CC) $(FLAG) -c $(SRC)chunk_info.cpp -o $(SRC)chunk_info.o

chunk_tag.o: $(SRC)chunk_tag.cpp $(SRC)chunk_tag.hpp
	$(CC) $(FLAG) -c $(SRC)chunk_tag.cpp -o $(SRC)chunk_tag.o

compression.o: $(SRC)compression.cpp $(SRC)compression.hpp
	$(CC) $(FLAG) -c $(SRC)compression.cpp -o $(SRC)compression.o

compound_tag.o: $(TAG)compound_tag.cpp $(TAG)compound_tag.hpp
	$(CC) $(FLAG) -c $(TAG)compound_tag.cpp -o $(TAG)compound_tag.o

double_tag.o: $(TAG)double_tag.cpp $(TAG)double_tag.hpp
	$(CC) $(FLAG) -c $(TAG)double_tag.cpp -o $(TAG)double_tag.o

end_tag.o: $(TAG)end_tag.cpp $(TAG)end_tag.hpp
	$(CC) $(FLAG) -c $(TAG)end_tag.cpp -o $(TAG)end_tag.o

float_tag.o: $(TAG)float_tag.cpp $(TAG)float_tag.hpp
	$(CC) $(FLAG) -c $(TAG)float_tag.cpp -o $(TAG)float_tag.o

generic_tag.o: $(TAG)generic_tag.cpp $(TAG)generic_tag.hpp
	$(CC) $(FLAG) -c $(TAG)generic_tag.cpp -o $(TAG)generic_tag.o

int_array_tag.o: $(TAG)int_array_tag.cpp $(TAG)int_array_tag.hpp
	$(CC) $(FLAG) -c $(TAG)int_array_tag.cpp -o $(TAG)int_array_tag.o

int_tag.o: $(TAG)int_tag.cpp $(TAG)int_tag.hpp
	$(CC) $(FLAG) -c $(TAG)int_tag.cpp -o $(TAG)int_tag.o

list_tag.o: $(TAG)list_tag.cpp $(TAG)list_tag.hpp
	$(CC) $(FLAG) -c $(TAG)list_tag.cpp -o $(TAG)list_tag.o

long_tag.o: $(TAG)long_tag.cpp $(TAG)long_tag.hpp
	$(CC) $(FLAG) -c $(TAG)long_tag.cpp -o $(TAG)long_tag.o

region.o: $(SRC)region.cpp $(SRC)region.hpp
	$(CC) $(FLAG) -c $(SRC)region.cpp -o $(SRC)region.o

region_file.o: $(SRC)region_file.cpp $(SRC)region_file.hpp
	$(CC) $(FLAG) -c $(SRC)region_file.cpp -o $(SRC)region_file.o

region_file_reader.o: $(SRC)region_file_reader.cpp $(SRC)region_file_reader.hpp
	$(CC) $(FLAG) -c $(SRC)region_file_reader.cpp -o $(SRC)region_file_reader.o

region_file_writer.o: $(SRC)region_file_writer.cpp $(SRC)region_file_writer.hpp
	$(CC) $(FLAG) -c $(SRC)region_file_writer.cpp -o $(SRC)region_file_writer.o

region_header.o: $(SRC)region_header.cpp $(SRC)region_header.hpp
	$(CC) $(FLAG) -c $(SRC)region_header.cpp -o $(SRC)region_header.o

short_tag.o: $(TAG)short_tag.cpp $(TAG)short_tag.hpp
	$(CC) $(FLAG) -c $(TAG)short_tag.cpp -o $(TAG)short_tag.o

string_tag.o: $(TAG)string_tag.cpp $(TAG)string_tag.hpp
	$(CC) $(FLAG) -c $(TAG)string_tag.cpp -o $(TAG)string_tag.o

tag: byte_array_tag.o byte_tag.o compound_tag.o double_tag.o end_tag.o float_tag.o generic_tag.o int_array_tag.o int_tag.o list_tag.o long_tag.o short_tag.o string_tag.o
