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

#include <cstdlib>
#include <string>
#include <vector>

class byte_stream {
private:

	/*
	 * Stream buffer
	 */
	std::vector<char> buff;

	/*
	 * Stream buffer length/position
	 */
	unsigned int pos;

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
		std::vector<char> data;

		// assign type T from stream
		unsigned int width = sizeof(T);
		for(unsigned int i = 0; i < width; i++) {
			if(available() == END_OF_STREAM)
				return END_OF_STREAM;
			data.push_back(buff.at(pos++));
		}
		if(swap)
			swap_endian(data);
		var = 0;
		for(unsigned int i = 0; i < width - 1; i++)
			var |= data.at(i) << 8 * ((width - 1) - i);
		var |= data.at(width - 1);
		return SUCCESS;
	}

	/*
	 * Read byte stream into variable
	 * (float, double)
	 */
	template<class T>
	unsigned int read_stream_float(T &var) {
		std::vector<char> data;

		// assign type T from stream
		unsigned int width = sizeof(T);
		for(unsigned int i = 0; i < width; i++) {
			if(available() == END_OF_STREAM)
				return END_OF_STREAM;
			data.push_back(buff[pos++]);
		}
		if(swap)
			swap_endian(data);
		var = atof((char *) data.data());
		return SUCCESS;
	}

	/*
	 * Convert between endian types
	 */
	void swap_endian(std::vector<char> &data);

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
	byte_stream(void) : pos(0), swap(NO_SWAP_ENDIAN) { return; }

	/*
	 * Byte stream constructor
	 */
	byte_stream(const byte_stream &other) : buff(other.buff), pos(other.pos), swap(other.swap) { return; }

	/*
	 * Byte stream constructor
	 */
	byte_stream(const std::string &buff);

	/*
	 * Byte stream constructor
	 */
	byte_stream(std::vector<char> &buff);

	/*
	 * Byte stream destructor
	 */
	virtual ~byte_stream(void) { return; }

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
	bool operator>>(char &output);

	/*
	 * Byte stream output
	 */
	bool operator>>(short &output);

	/*
	 * Byte stream output
	 */
	bool operator>>(int &output);

	/*
	 * Byte stream output
	 */
	bool operator>>(long &output);

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
	const char *rdbuf(void) { return buff.data(); }

	/*
	 * Resets the streams position
	 */
	void reset(void) { pos = 0; }

	/*
	 * Returns the streams total size
	 */
	unsigned int size(void) { return buff.size(); }

	/*
	 * Returns a string representation of the stream
	 */
	std::string to_string(void);
};

#endif
