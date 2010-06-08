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

#ifndef SWK_MAPPER_HPP_INCLUDED
#define SWK_MAPPER_HPP_INCLUDED

#include <swk/config.hpp>
#include <swk/fs_local.hpp>
#include <swk/bucket.hpp>
#include <vector>
#include <map>
#include <utility>

namespace swk {

template <class IK, class IV, class OK, class OV>
class mapper_context
{
public:

	typedef IK ik_type;
	typedef IV iv_type;
	typedef OK ok_type;
	typedef OV ov_type;
	typedef typename bucket_map<OK, OV>::type bucket_type;

	void push(const OK& ok, const OV& ov)
	{
#if 0
		std::pair<typename bucket_type::iterator, bool> r
			= mb_.insert(std::make_pair(ok, typename bucket_type::mapped_type()));
		r.first->second.push_back(ov);
#else
		mb_[ok].push_back(ov);
#endif
	}

	bucket_type mb_;

}; // class swk::mapper_context

template <class IK, class IV, class OK, class OV>
class mapper
{
public:

	typedef IK ik_type;
	typedef IV iv_type;
	typedef OK ok_type;
	typedef OV ov_type;
	typedef mapper_context<IK, IV, OK, OV> context;

//	virtual void operator()(const ik_type& key,
//	                        const iv_type& value,
//	                        context& ctx) = 0;

}; // class swk::mapper

} // namespace swk

#endif /* SWK_MAPPER_HPP_INCLUDED */

