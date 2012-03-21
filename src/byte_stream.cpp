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
byte_stream::byte_stream(const std::string &buff) {
	pos = 0;
	for(unsigned int i = 0; i < buff.length(); ++i)
		this->buff.push_back(buff.at(i));
	swap = NO_SWAP_ENDIAN;
}

/*
 * Byte stream constructor
 */
byte_stream::byte_stream(std::vector<char> &buff) {
	pos = 0;
	this->buff = buff;
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
	pos = other.pos;
	buff = other.buff;
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
	if(pos != other.pos)
		return false;
	for(unsigned int i = 0; i < buff.size(); ++i)
		if(buff.at(i) != other.buff.at(i))
			return false;
	return true;
}

/*
 * Byte stream input
 */
bool byte_stream::operator<<(const std::string &input) {

	// append to the end of the stream
	for(unsigned int i = 0; i < input.size(); ++i)
		buff.push_back(input.at(i));
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
bool byte_stream::operator>>(char &output) {

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
bool byte_stream::operator>>(short &output) {

	// check if end of stream is reached
	if(available() == END_OF_STREAM)
		return END_OF_STREAM;

	// read short from stream
	return read_stream<short>(output);
}

/*
 * Byte stream output
 */
bool byte_stream::operator>>(int &output) {

	// check if end of stream is reached
	if(available() == END_OF_STREAM)
		return END_OF_STREAM;

	// read short from stream
	return read_stream<int>(output);
}

/*
 * Byte stream output
 */
bool byte_stream::operator>>(long &output) {

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
	unsigned int remaining = buff.size() - pos;
	if(remaining <= 0)
		return END_OF_STREAM;
	return remaining;
}

/*
 * Convert between endian types
 */
void byte_stream::swap_endian(std::vector<char> &data) {
	std::vector<char> rev;
	rev.resize(data.size());

	// reverse the order of elements
	for(unsigned int i = 0; i < data.size(); ++i)
		rev.at(rev.size() - i) = data.at(i);
	data = rev;
}

/*
 * Returns a string representation of the stream
 */
std::string byte_stream::to_string(void) {
	std::stringstream ss;

	// form string representation
	ss << (good() ? "ACTIVE" : "INACTIVE") << ", size: " << buff.size() << ", pos: " << pos;
	if(available())
		ss << ", curr: " << (int) buff[pos];
	if(swap)
		ss << " (SWAP ENDIAN)";
	return ss.str();
}
