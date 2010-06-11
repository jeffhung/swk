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

#ifndef SWK_FILE_OUTPUT_HPP_INCLUDED
#define SWK_FILE_OUTPUT_HPP_INCLUDED

#include <swk/config.hpp>
#include <swk/file_traits.hpp>
#include <swk/file_split.hpp>
#include <swk/fs_local.hpp>
#include <swk/debug_tool.hpp>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <utility>

namespace swk {

template <class OK, class OV>
class record_writer
{
public:

	typedef OK ok_type;
	typedef OV ov_type;

	record_writer(const std::string& path)
		: path_(path)
		, out_(0)
	{
	}

	~record_writer()
	{
		if (out_) {
			delete out_;
		}
	}

	void write(const ok_type& ok, const ov_type& ov)
	{
		if (out_ == 0) {
			out_ = new std::ofstream(path_.c_str());
		}
		out_ << ok << "\t" << ov << std::endl;
	}

private:

	std::string path_;
	std::ostream* out_;

}; // class swk::record_writer<>

/**
 * A section of an input file.
 */
template <class FS = fs_local, class FT = text_file_traits<FS> >
class file_output
{
public:

	file_output()
	{
	}

	template <class OK, class OV>
	std::auto_ptr< record_writer<OK, OV> > get_record_writer()
	{
		return new record_writer<OK, OV>(path_);
	}

	void set_path(const std::string& path)
	{
		path_ = path;
	}

	template <class OK, class OV>
	void write(const OK& ok, const OV& ov)
	{
		std::ofstream ofs(path_.c_str(), std::ios::app);
		ofs << ok << "\t" << ov << std::endl;
	}

private:

	std::string path_;

}; // class swk::file_output<>

} // namespace swk

#endif /* SWK_FILE_OUTPUT_HPP_INCLUDED */


