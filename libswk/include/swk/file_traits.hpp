// ---------------------------------------------------------------------------
// SWK - A map/reduce framework written in C++.
// Copyright (c) 2010, Jeff Hung
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 
//  - Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  - Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  - Neither the name of the copyright holders nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// ---------------------------------------------------------------------------
// $Date$
// $Rev$
// $Author$
// ---------------------------------------------------------------------------
// revid: "@(#) $Id$"
// ---------------------------------------------------------------------------

#ifndef SWK_FILE_TRAITS_HPP_INCLUDED
#define SWK_FILE_TRAITS_HPP_INCLUDED

#include <swk/config.hpp>
#include <swk/misc.hpp>
#include <boost/io/ios_state.hpp>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

namespace swk {

template <class FS>
struct base_file_traits
{

	enum { splittable };

//	/** Opens file in @p path with proper open mode. */
//	void open(std::ifstream& ic, const std::string& path);

	/**
	 * Find next record boundary in input channel @p ic, starting at @p
	 * start.
	 */
	size_t find_boundary(std::ifstream& ic, size_t start);

}; // class swk::base_file_traits<>

/**
 * Traits of raw files where content are treated as a byte array and split at
 * anywhere.
 */
template <class FS>
struct raw_file_traits : public base_file_traits<FS>
{
	enum { splittable = 1 };

//	void open(std::ifstream& ic, const std::string& path)
//	{
//		ic.open(path.c_str(), std::ios::in | std::ios::binary);
//	}

	size_t find_boundary(std::ifstream& ic, size_t start)
	{
		// In raw file, anywhere can be the boundary. So that's use start,
		// which is decided by *_input_format, as the boundary.
		return start;
	}

}; // class swk::raw_file_traits

/**
 * Traits of text files where content are treated as lines of texts and split
 * at line ends. All three CR, LF, and CRLF are recognized.
 */
template <class FS>
struct text_file_traits
{
	enum { splittable = 1 };

//	void open(std::ifstream& ic, const std::string& path)
//	{
//		ic.open(path.c_str(), std::ios::in);
//	}

	static size_t find_boundary(std::ifstream& ic, size_t start)
	{
		static const char* LINE_ENDS[] = { "\x0a", "\x0c", "\x0a\x0c", 0 };
		boost::io::ios_all_saver ips(ic);
		do {
			std::ifstream::char_type buffer[8];
			ic.seekg(start);
			if (ic) {
				ic.read(buffer, sizeof(buffer) - 1);
				size_t size = ic.gcount();
				buffer[size] = '\0'; // null end it to pass to strstr()
				for (size_t i = 0; LINE_ENDS[i]; ++i) {
					char* p = strstr(buffer, LINE_ENDS[i]);
					if (p) {
						return start + (p - buffer) + strlen(LINE_ENDS[i]);
					}
				}
				start += size;
			}
		} while (ic);
		return start;
	}

}; // class swk::text_file_traits

} // namespace swk

#endif /* SWK_FILE_TRAITS_HPP_INCLUDED */



