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

#ifndef SWK_LINE_RECORD_READER_HPP_INCLUDED
#define SWK_LINE_RECORD_READER_HPP_INCLUDED

#include <swk/config.hpp>
#include <swk/fs_local.hpp>
#include <swk/file_traits.hpp>
#include <swk/misc.hpp>
#include <boost/io/ios_state.hpp>
#include <fstream>
#include <string>
#include <utility>
#include <stdexcept>

namespace swk {

template <class FS = fs_local>
class line_record_reader /* : public record_reader<uint64_t, std::string> */
{
public:

	line_record_reader(const file_split& split)
		: split_(split)
		, line_beg_(split.start())
		, line_end_(split.start())
		, ic_(split.path().c_str(), std::ios::binary)
	{
	}

	std::pair<uint64_t, std::string> current()
	{
		if (line_end_ <= line_beg_) {
			throw std::runtime_error("No current value yet. Please advance() first.");
		}
//		SWK_DVAR(line_beg_);
//		SWK_DVAR(line_end_);
		size_t length = line_end_ - line_beg_;
//		SWK_DVAR(length);
		boost::io::ios_all_saver ips(ic_);
		auto_buffer<> buffer(length);
		ic_.seekg(line_beg_);
		if (ic_) {
//			SWK_DVAR(line_beg_);
//			SWK_DVAR(line_end_);
//			SWK_DVAR(length);
			if (ic_.read(buffer.get(), length)) {
				std::pair<uint64_t, std::string> c;
				c.first = line_beg_;
				c.second = std::string(buffer.get(), length);
//				SWK_DVAR(c.second);
//				std::cerr << "@" << length << "@" << c.second << "||";
				return c;
			}
		}
		throw std::runtime_error("Failed to get current key/value.");
	}

	bool advance()
	{
		line_beg_ = line_end_;
		if (line_beg_ > split_.end()) {
			return false;
		}
		size_t le = std::min(
			text_file_traits<FS>::find_boundary(ic_, line_beg_),
			split_.end()
		);
//		SWK_DVAR(line_beg_);
//		SWK_DVAR(line_end_);
//		SWK_DVAR(le);
		if (le <= line_beg_) {
			return false;
		}
		line_end_ = le;
		return true;
	}

private:

	file_split split_;
	size_t line_beg_;
	size_t line_end_;
	std::ifstream ic_;

}; // class swk::line_record_reader

} // namespace swk

#endif /* SWK_LINE_RECORD_READER_HPP_INCLUDED */

