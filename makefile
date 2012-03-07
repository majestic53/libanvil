# Libanvil Makefile
# Copyright (C) 2012 David Jolly

CC=g++
SRC=src/
TAG=src/tag/
OUT=libanvil.a
FLAG=-std=c++0x -O3 -funroll-all-loops

all: tag region build

build: 
	ar rcs $(OUT) $(SRC)byte_stream.o $(SRC)region_chunk_info.o $(SRC)region_chunk_tag.o $(SRC)region_file.o $(SRC)region_file_exc.o $(SRC)region_file_reader.o $(TAG)byte_array_tag.o $(TAG)byte_tag.o $(TAG)compound_tag.o $(TAG)double_tag.o $(TAG)end_tag.o $(TAG)float_tag.o $(TAG)generic_tag.o $(TAG)int_tag.o $(TAG)int_array_tag.o $(TAG)list_tag.o $(TAG)long_tag.o $(TAG)short_tag.o $(TAG)string_tag.o

clean:
	rm -f $(OUT)
	rm -f $(SRC)*.o
	rm -f $(TAG)*.o

byte_array_tag.o: $(TAG)byte_array_tag.cpp $(TAG)byte_array_tag.hpp
	$(CC) $(FLAG) -c $(TAG)byte_array_tag.cpp -o $(TAG)byte_array_tag.o

byte_stream.o: $(SRC)byte_stream.cpp $(SRC)byte_stream.hpp
	$(CC) $(FLAG) -c $(SRC)byte_stream.cpp -o $(SRC)byte_stream.o

byte_tag.o: $(TAG)byte_tag.cpp $(TAG)byte_tag.hpp
	$(CC) $(FLAG) -c $(TAG)byte_tag.cpp -o $(TAG)byte_tag.o

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

int_tag.o: $(TAG)int_tag.cpp $(TAG)int_tag.hpp
	$(CC) $(FLAG) -c $(TAG)int_tag.cpp -o $(TAG)int_tag.o

int_array_tag.o: $(TAG)int_array_tag.cpp $(TAG)int_array_tag.hpp
	$(CC) $(FLAG) -c $(TAG)int_array_tag.cpp -o $(TAG)int_array_tag.o

list_tag.o: $(TAG)list_tag.cpp $(TAG)list_tag.hpp
	$(CC) $(FLAG) -c $(TAG)list_tag.cpp -o $(TAG)list_tag.o

long_tag.o: $(TAG)long_tag.cpp $(TAG)long_tag.hpp
	$(CC) $(FLAG) -c $(TAG)long_tag.cpp -o $(TAG)long_tag.o

region: byte_stream.o region_chunk_info.o region_chunk_tag.o region_file.o region_file_exc.o region_file_reader.o

region_chunk_info.o: $(SRC)region_chunk_info.cpp $(SRC)region_chunk_info.hpp
	$(CC) $(FLAG) -c $(SRC)region_chunk_info.cpp -o $(SRC)region_chunk_info.o

region_chunk_tag.o: $(SRC)region_chunk_tag.cpp $(SRC)region_chunk_tag.hpp
	$(CC) $(FLAG) -c $(SRC)region_chunk_tag.cpp -o $(SRC)region_chunk_tag.o

region_file.o: $(SRC)region_file.cpp $(SRC)region_file.hpp
	$(CC) $(FLAG) -c $(SRC)region_file.cpp -o $(SRC)region_file.o

region_file_exc.o: $(SRC)region_file_exc.cpp $(SRC)region_file_exc.hpp
	$(CC) $(FLAG) -c $(SRC)region_file_exc.cpp -o $(SRC)region_file_exc.o

region_file_reader.o: $(SRC)region_file_reader.cpp $(SRC)region_file_reader.hpp
	$(CC) $(FLAG) -c $(SRC)region_file_reader.cpp -o $(SRC)region_file_reader.o

short_tag.o: $(TAG)short_tag.cpp $(TAG)short_tag.hpp
	$(CC) $(FLAG) -c $(TAG)short_tag.cpp -o $(TAG)short_tag.o

string_tag.o: $(TAG)string_tag.cpp $(TAG)string_tag.hpp
	$(CC) $(FLAG) -c $(TAG)string_tag.cpp -o $(TAG)string_tag.o

tag: byte_array_tag.o byte_tag.o compound_tag.o double_tag.o end_tag.o float_tag.o generic_tag.o int_tag.o int_array_tag.o list_tag.o long_tag.o short_tag.o string_tag.o
