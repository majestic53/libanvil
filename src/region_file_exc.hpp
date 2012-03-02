/*
 * region_file_exc.hpp
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

#ifndef REGION_FILE_EXC_HPP_
#define REGION_FILE_EXC_HPP_

#include <sstream>
#include <string>
#include <vector>

class region_file_exc {
private:

	/*
	 * Exception code
	 */
	unsigned int exc;

	/*
	 * Exception message
	 */
	std::string message;

public:

	/*
	 * Supported exception codes
	 */
	enum EXC_CODE { UNDEFINED, ALLOC_FAIL, INVALID_PATH, OUT_OF_BOUNDS, UNSUPPORTED_COMPRESSION,
					UNKNOWN_COMPRESSION, UNKNOWN_TAG_TYPE, STREAM_READ_ERROR, UNFILLED_CHUNK, };
	static const std::string MESSAGE[];
	static const unsigned int MESSAGE_COUNT = 9;

	/*
	 * Region file exception constructor
	 */
	region_file_exc(void) : exc(UNDEFINED) { return; };

	/*
	 * Region file exception constructor
	 */
	region_file_exc(unsigned int exc) : exc(exc) { return; };

	/*
	 * Region file exeception constructor
	 */
	template <class T>
	region_file_exc(unsigned int exc, const T &message) : exc(exc) {
		std::stringstream ss;
		ss << message;
		this->message = ss.str();
	}

	/*
	 * Region file exeception constructor
	 */
	template <class T>
	region_file_exc(unsigned int exc, std::vector<T> &message) : exc(exc) {
		std::stringstream ss;
		for(unsigned int i = 0; i < message.size() - 1; ++i)
			ss << message.at(i) << ", ";
		ss << message.at(message.size() - 1);
		this->message = ss.str();
	}

	/*
	 * Region file exception destructor
	 */
	virtual ~region_file_exc(void) { return; }

	/*
	 * Region file exception assignment
	 */
	region_file_exc &operator=(const region_file_exc &other);

	/*
	 * Region file exception equals
	 */
	bool operator==(const region_file_exc &other);

	/*
	 * Region file exception not equals
	 */
	bool operator!=(const region_file_exc &other) { return !(*this == other); }

	/*
	 * Returns an exception code
	 */
	unsigned int get_exception(void) { return exc; }

	/*
	 * Returns an exception message
	 */
	std::string get_message(void) { return message; }

	/*
	 * Sets an exception code
	 */
	void set_exception(unsigned int exc) { this->exc = exc; }

	/*
	 * Sets an exception message
	 */
	void set_message(const std::string &message) { this->message = message; }

	/*
	 * Returns a string representation of an exception
	 */
	std::string to_string(void);
};

#endif
