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

#include <swk/mr2/mapper.hpp>
#include <swk/mr2/reducer.hpp>
#include <swk/mr2/job.hpp>
#include <swk/fs_local.hpp>
#include <swk/str_tool.hpp>
#include <string>
#include <vector>
#include <stdint.h>

class wordcount_mapper : public swk::mr2::mapper<uint32_t, std::string,
                                                 std::string, uint32_t>
{
public:

	void operator()(const uint32_t& key,
	                const std::string& value,
	                context& ctx)
	{
		SWK_DOUT << value;
		std::vector<std::string> tokens = swk::str_tokenize(value);
		for (std::vector<std::string>::const_iterator it = tokens.begin();
		     it != tokens.end();
		     ++it) {
			SWK_DVAR(*it);
			ctx.push(*it, uint32_t(1));
		}
	}

}; // class wordcount

class wordcount_reducer : public swk::mr2::reducer<std::string, uint32_t,
                                                   std::string, uint32_t>
{
public:

	void operator()(const std::string& key,
	                const std::vector<uint32_t>& values,
	                context& ctx)
	{
		uint32_t sum = 0;
		for (std::vector<uint32_t>::const_iterator it = values.begin();
		     it != values.end();
		     ++it) {
			sum += *it;
		}
		ctx.push(key, sum);
	}
};

int main()
{
	try {
		typedef swk::mr2::job<wordcount_mapper, wordcount_reducer> job_type;
		job_type wc;
		wc.add_input_path("data1.txt");
		wc.add_input_path("data2.txt");
		wc.add_input_path("data3.txt");
		wc.set_output_dir("output");
		wc.run();
		return 0;
	}
	catch (std::exception e) {
		return 1;
	}
}

