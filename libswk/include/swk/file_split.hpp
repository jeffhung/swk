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

#ifndef SWK_FILE_SPLIT_HPP_INCLUDED
#define SWK_FILE_SPLIT_HPP_INCLUDED

#include <swk/config.hpp>
#include <swk/debug_tool.hpp>
#include <swk/misc.hpp>
#include <string>
#include <algorithm>
#include <ostream>

namespace swk {

/**
 * A section of an input file.
 */
class file_split
{
friend std::ostream& operator << (std::ostream& os, const file_split& s);
public:

	/**
	 * Construct a split with host information.
	 *
	 * @param p path of the file in dfs
	 * @param s start position of the bytes in the file to process
	 * @param l number of the bytes in the file to process
	 */
	file_split(const std::string& p, size_t s, size_t l)
		: path_(p)
		, start_(s)
		, length_(l)
	{
	}

	file_split(const file_split& x)
		: path_(x.path_)
		, start_(x.start_)
		, length_(x.length_)
	{
	}

	file_split& operator = (const file_split& x)
	{
		if (this != &x) {
			file_split(x).swap(*this);
		}
		return *this;
	}

	void swap(file_split& x)
	{
		if (this != &x) {
			std::swap(path_, x.path_);
			std::swap(start_, x.start_);
			std::swap(length_, x.length_);
		}
	}

	const std::string& path() const
	{
		return path_;
	}

	size_t start() const
	{
		return start_;
	}

	size_t end() const
	{
		return start_ + length_;
	}

	size_t length() const
	{
		return length_;
	}

	/**
	 * Extend length @p n bytes.
	 */
	void extend(size_t n)
	{
		length_ += n;
	}

private:

	std::string path_;
	size_t start_;
	size_t length_;

}; // class swk::file_split

std::ostream& operator << (std::ostream& os, const file_split& s)
{
	os << "------> " << s.path_ << "@[" << s.start_ << "," << s.length_ << "]";
	os << std::endl;
	std::ifstream ifs(s.path_.c_str());
	ifs.seekg(s.start_);
//	char buffer[SWK_BLOCK_SIZE + 10] = { 0 };
//	char buffer[4096] = { 0 };
	auto_buffer<> buffer(s.length_ + 1);
//	SWK_DVAR(s.length_);
	if (ifs.read(buffer.get(), s.length_)) {
		os << buffer.get() << "||";
	}
	return os;
}

} // namespace swk

#endif /* SWK_FILE_SPLIT_HPP_INCLUDED */


