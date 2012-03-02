/*
 * byte_stream.hpp
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

#ifndef BYTE_STREAM_HPP_
#define BYTE_STREAM_HPP_

#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

class byte_stream {
private:

	/*
	 * Stream buffer
	 */
	int8_t *buff;

	/*
	 * Stream buffer length/position
	 */
	unsigned int len, pos;

	/*
	 * Swap endian
	 */
	bool swap;

	/*
	 * Read byte stream into variable
	 * (char, short, int, long)
	 */
	template<class T>
	unsigned int read_stream(T &var) {

		// assign type T from stream
		unsigned int width = sizeof(T);
		char *data = new char[width];
		for(unsigned int i = 0; i < width; i++) {
			if(available() == END_OF_STREAM)
				return END_OF_STREAM;
			data[i] = buff[pos++];
		}
		if(swap)
			swap_endian<char>(data, width);
		var = 0;
		for(unsigned int i = 0; i < width - 1; i++)
			var |= data[i] << 8 * ((width - 1) - i);
		var |= data[width - 1];
		delete[] data;
		return SUCCESS;
	}

	/*
	 * Read byte stream into variable
	 * (float, double)
	 */
	template<class T>
	unsigned int read_stream_float(T &var) {

		// assign type T from stream
		unsigned int width = sizeof(T);
		char *data = new char[width];
		for(unsigned int i = 0; i < width; i++) {
			if(available() == END_OF_STREAM)
				return END_OF_STREAM;
			data[i] = buff[pos++];
		}
		if(swap)
			swap_endian<char>(data, width);
		var = atof((char *) data);
		delete[] data;
		return SUCCESS;
	}

	/*
	 * Convert between endianesses
	 */
	template<class T>
	void swap_endian(T *&buff, unsigned int len) {

		// create a temp array to hold the reverse
		T *reverse = new T[len];
		for(unsigned int i = 0; i < len; i++)
			reverse[i] = buff[(len - 1) - i];
		delete[] buff;
		buff = reverse;
	}

public:

	/*
	 * Status indicators
	 */
	static const unsigned int END_OF_STREAM = 0;
	static const unsigned int SUCCESS = 1;

	/*
	 * Swap flags
	 */
	static const int NO_SWAP_ENDIAN = 0x0;
	static const int SWAP_ENDIAN = 0x1;

	/*
	 * Byte stream constructor
	 */
	byte_stream(void);

	/*
	 * Byte stream constructor
	 */
	byte_stream(const byte_stream &other);

	/*
	 * Byte stream constructor
	 */
	byte_stream(const std::string &input);

	/*
	 * Byte stream constructor
	 */
	byte_stream(std::vector<int8_t> &input);

	/*
	 * Byte stream destructor
	 */
	virtual ~byte_stream(void) { delete[] buff; }

	/*
	 * Byte stream assignment
	 */
	byte_stream &operator=(const byte_stream &other);

	/*
	 * Byte stream equals
	 */
	bool operator==(const byte_stream &other);

	/*
	 * Byte stream not equals
	 */
	bool operator!=(const byte_stream &other) { return !(*this == other); }

	/*
	 * Byte stream input
	 */
	bool operator<<(const std::string &input);

	/*
	 * Byte stream input (flag)
	 */
	bool operator<<(int flag);

	/*
	 * Byte stream output
	 */
	bool operator>>(int8_t &output);

	/*
	 * Byte stream output
	 */
	bool operator>>(int16_t &output);

	/*
	 * Byte stream output
	 */
	bool operator>>(int32_t &output);

	/*
	 * Byte stream output
	 */
	bool operator>>(int64_t &output);

	/*
	 * Byte stream output
	 */
	bool operator>>(float &output);

	/*
	 * Byte stream output
	 */
	bool operator>>(double &output);

	/*
	 * Returns the available bytes left in the stream
	 */
	unsigned int available(void);

	/*
	 * Returns the status of the stream
	 */
	bool good(void) { return available() != END_OF_STREAM; }

	/*
	 * Returns the endian swap status of the stream
	 */
	bool is_swap(void) { return swap; }

	/*
	 * Returns the current position of the stream
	 */
	unsigned int position(void) { return pos; }

	/*
	 * Returns the entire contents of the stream buffer
	 */
	int8_t *rdbuf(void) { return buff; }

	/*
	 * Resets the streams position
	 */
	void reset(void) { pos = 0; }

	/*
	 * Returns the streams total size
	 */
	unsigned int size(void) { return len; }

	/*
	 * Returns a string representation of the stream
	 */
	std::string to_string(void);
};

#endif
