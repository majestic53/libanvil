/*
 * byte_stream.cpp
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

#include <sstream>
#include "byte_stream.hpp"

/*
 * Byte stream constructor
 */
byte_stream::byte_stream(void) {
	len = 0;
	pos = 0;
	buff = NULL;
	swap = NO_SWAP_ENDIAN;
}

/*
 * Byte stream constructor
 */
byte_stream::byte_stream(const byte_stream &other) {
	len = other.len;
	pos = other.pos;
	buff = new int8_t[other.len];
	if(!buff) {
		len = 0;
		pos = 0;
		return;
	}
	for(unsigned int i = 0; i < len; ++i)
		buff[i] = other.buff[i];
	swap = other.swap;
}

/*
 * Byte stream constructor
 */
byte_stream::byte_stream(const std::string &input) {
	len = input.length();
	pos = 0;
	buff = new int8_t[input.length()];
	if(!buff) {
		len = 0;
		pos = 0;
		return;
	}
	for(unsigned int i = 0; i < len; ++i)
		buff[i] = input[i];
	swap = NO_SWAP_ENDIAN;
}

/*
 * Byte stream constructor
 */
byte_stream::byte_stream(std::vector<int8_t> &input) {
	len = input.size();
	pos = 0;
	buff = new int8_t[input.size()];
	if(!buff) {
		len = 0;
		pos = 0;
		return;
	}
	for(unsigned int i = 0; i < len; ++i)
		buff[i] = input.at(i);
	swap = NO_SWAP_ENDIAN;
}

/*
 * Byte stream assignment
 */
byte_stream &byte_stream::operator=(const byte_stream &other) {

	// check for self
	if(this == &other)
		return *this;

	// set attributes
	len = other.len;
	pos = other.pos;
	buff = new int8_t[other.len];
	if(!buff) {
		len = 0;
		pos = 0;
		return *this;
	}
	for(unsigned int i = 0; i < len; ++i)
		buff[i] = other.buff[i];
	swap = other.swap;
	return *this;
}

/*
 * Byte stream equals
 */
bool byte_stream::operator==(const byte_stream &other) {

	// check for self
	if(this == &other)
		return true;

	// check attributes
	if(len != other.len
			|| pos != other.pos)
		return false;
	for(unsigned int i = 0; i < len; ++i)
		if(buff[i] != other.buff[i])
			return false;
	return true;
}

/*
 * Byte stream input
 */
bool byte_stream::operator<<(const std::string &input) {

	// create new buffer
	int8_t *n_buff = new int8_t[input.length()];
	if(!n_buff)
		return false;
	for(unsigned int i = 0; i < input.length(); ++i)
		n_buff[i] = input.at(i);

	// set attributes
	if(buff)
		delete[] buff;
	len = input.length();
	pos = 0;
	buff = n_buff;
	return true;
}

/*
 * Byte stream input (flag)
 */
bool byte_stream::operator<<(int flag) {

	// set state flags
	switch(flag) {
		case NO_SWAP_ENDIAN: swap = false;
			break;
		case SWAP_ENDIAN: swap = true;
			break;
		default: return false;
			break;
	}
	return true;
}

/*
 * Byte stream output
 */
bool byte_stream::operator>>(int8_t &output) {

	// check if end of stream is reached
	if(available() == END_OF_STREAM)
		return END_OF_STREAM;

	// assign char from stream
	output = buff[pos++];
	return SUCCESS;
}

/*
 * Byte stream output
 */
bool byte_stream::operator>>(int16_t &output) {

	// check if end of stream is reached
	if(available() == END_OF_STREAM)
		return END_OF_STREAM;

	// read short from stream
	return read_stream<short>(output);
}

/*
 * Byte stream output
 */
bool byte_stream::operator>>(int32_t &output) {

	// check if end of stream is reached
	if(available() == END_OF_STREAM)
		return END_OF_STREAM;

	// read short from stream
	return read_stream<int>(output);
}

/*
 * Byte stream output
 */
bool byte_stream::operator>>(int64_t &output) {

	// check if end of stream is reached
	if(available() == END_OF_STREAM)
		return END_OF_STREAM;

	// read short from stream
	return read_stream<long>(output);
}

/*
 * Byte stream output
 */
bool byte_stream::operator>>(float &output) {

	// check if end of stream is reached
	if(available() == END_OF_STREAM)
		return END_OF_STREAM;

	// read short from stream
	return read_stream_float<float>(output);
}

/*
 * Byte stream output
 */
bool byte_stream::operator>>(double &output) {

	// check if end of stream is reached
	if(available() == END_OF_STREAM)
		return END_OF_STREAM;

	// read short from stream
	return read_stream_float<double>(output);
}

/*
 * Returns the available bytes left in the stream
 */
unsigned int byte_stream::available(void) {
	unsigned int remaining = len - pos;
	if(remaining <= 0)
		return END_OF_STREAM;
	return remaining;
}

/*
 * Returns a string representation of the stream
 */
std::string byte_stream::to_string(void) {
	std::stringstream ss;

	// form string representation
	ss << "[STREAM] " << (good() ? "ACTIVE" : "INACTIVE") << ", size: " << len << ", pos: " << pos;
	if(available())
		ss << ", curr: " << buff[pos] << " (" << (int) buff[pos] << ")";
	if(swap)
		ss << " (SWAP ENDIAN)";
	return ss.str();
}
