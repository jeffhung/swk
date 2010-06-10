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

#ifndef SWK_MR3_JOB_HPP_INCLUDED
#define SWK_MR3_JOB_HPP_INCLUDED

#include <swk/dtool.hpp>
#include <swk/fs_local.hpp>
#include <swk/mr3/mapper_context.hpp>
#include <swk/mr3/reducer_context.hpp>
#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>

namespace swk {
namespace mr3 {

class job
{
public:
	virtual void run() =  0;

	void add_input_path(const std::string& path)
	{
		input_paths.push_back(path);
	}

	void set_output_dir(const std::string& dir)
	{
		output_dir = dir;
	}

protected:

	std::vector<std::string> input_paths;
	std::string output_dir;

};

template <class IK, class IV, class OK, class OV,
          class M, class R, class FS = fs_local>
class generic_job : public job
{
public:

	generic_job(M m, R r)
		: m_(m), r_(r)
	{
	}

	virtual void run()
	{
		typedef generic_mapper_context<IK, IV, OK, OV> mc_type;
		mc_type mc;
		for (std::vector<std::string>::const_iterator ip = input_paths.begin(); // ip: input path
		     ip != input_paths.end();
		     ++ip) {
			std::ifstream ic(ip->c_str());
			std::string line;
			uint64_t no = 0;
			while (std::getline(ic, line)) {
				SWK_DOUT << line;
				++no;
				m_(no, line, mc);
			}
		}
		SWK_DMVEC(mc.outputs_);

		generic_reducer_context<OK, OV, OK, OV> rc;
		for (typename mc_type::outputs_type::const_iterator me = mc.outputs_.begin(); // me: map entry
		     me != mc.outputs_.end();
		     ++me) {
			r_(me->first, me->second, rc);
		}
	}

private:

	M m_;
	R r_;

};

template <class IK, class IV, class OK, class OV, class M, class R>
std::auto_ptr<job> make_job(M m, R r)
{
	return std::auto_ptr<job>(new generic_job<IK, IV, OK, OV, M, R>(m, r));
}

} // namespace swk::mr3
} // namespace swk

#endif /* SWK_MR3_JOB_HPP_INCLUDED */

