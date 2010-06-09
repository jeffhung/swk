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

#ifndef SWK_JOB_HPP_INCLUDED
#define SWK_JOB_HPP_INCLUDED

#include <swk/config.hpp>
#include <swk/dtool.hpp>
#include <swk/file_input.hpp>
#include <swk/file_split.hpp>
#include <swk/line_record_reader.hpp>
#include <swk/file_output.hpp>
#include <swk/misc.hpp>
#include <boost/thread.hpp>
#include <memory>
#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>
#include <stdexcept>

namespace swk {

template < class M
         , class R
         , class IFMT = file_input<>
         , class OFMT = file_output<>
         >
class job
{
public:

	typedef M mapper_type;
	typedef R reducer_type;
	typedef typename M::ik_type mik_type;
	typedef typename M::iv_type miv_type;
	typedef typename M::ok_type mok_type;
	typedef typename M::ov_type mov_type;
	typedef typename R::ik_type rik_type;
	typedef typename R::iv_type riv_type;
	typedef typename R::ok_type rok_type;
	typedef typename R::ov_type rov_type;

	typedef typename M::context mc_type;
	typedef typename R::context rc_type;

//	SWK_STATIC_ASSERT(
//		swk::and<
//			swk::convertable<mok_type, rik_type>::value,
//			swk::convertable<mov_type, riv_type>::value
//		>::value
//	);

	job()
		: num_mappers(2)
		, num_reducers(1)
	{
	}

	void add_input_path(const std::string& path)
	{
		ifmt_.add_path(path);
	}

	void set_output_dir(const std::string& dir)
	{
		ofmt_.set_path(dir);
	}

	void set_num_mappers(size_t nm)
	{
		num_mappers = nm;
	}

	void set_num_reducers(size_t nr)
	{
		num_reducers = nr;
	}

	struct map_task_queue
	{
		map_task_queue(IFMT& ifmt)
			: splits(ifmt.list_splits())
			, next(0)
		{
		}

		std::vector<swk::file_split> splits;
		std::vector<swk::file_split>::size_type next;
		mc_type mc;
		boost::mutex mx; //!< protects this queue
	};

#if SWK_USE_THREADED_MAPPER
	struct mapper_thread
	{
		void operator()(map_task_queue* pmtq) const
		{
			try {
				while (true) {
					std::auto_ptr<swk::file_split> s;
					{
						boost::lock_guard<boost::mutex> lg(pmtq->mx);
						if (pmtq->next < pmtq->splits.size()) {
							s.reset(new swk::file_split(pmtq->splits.at(pmtq->next++)));
						}
					}
					if (!s.get()) {
						break; // while
					}
//					std::cerr << *s << std::endl;
					swk::line_record_reader<> rr(*s);
					while (rr.advance()) {
						std::pair<uint64_t, std::string> c = rr.current();
//						std::cout << "[" << c.first << "] " << c.second;
						{
							boost::lock_guard<boost::mutex> lg(pmtq->mx);
							mapper_type()(c.first, c.second, pmtq->mc);
						}
					}
					// We do not randomly wait here.
				}
			}
			catch (const std::exception& e) {
				std::cerr << "Exception thrown from thread function: " << e.what() << std::endl;
			}
			catch (...) {
				std::cerr << "Exception thrown from thread function." << std::endl;
			}
		}
	};
#endif // SWK_USE_THREADED_MAPPER

	void run()
	{
		map_task_queue mtq(ifmt_); // splits queue
		SWK_DVAR(mtq.splits.size());

#if SWK_USE_THREADED_MAPPER
		boost::thread_group mapper_threads;
		for (size_t nm = 0; nm < num_mappers; ++nm) {
			mapper_threads.add_thread(new boost::thread(mapper_thread(), &mtq));
		}
		SWK_DVAR(mapper_threads.size());
		mapper_threads.join_all();
#else // !SWK_USE_THREADED_MAPPER
		if (mtq.next < mtq.splits.size()) {
			swk::file_split& s = mtq.splits.at(mtq.next++);
			swk::line_record_reader<> rr(s);
			while (rr.advance()) {
				std::pair<uint64_t, std::string> c = rr.current();
//				std::cout << "[" << c.first << "] " << c.second;
				mapper_type()(c.first, c.second, mtq.mc);
			}
		}
#endif // SWK_USE_THREADED_MAPPER

		{
			boost::lock_guard<boost::mutex> lg(mtq.mx);
#if 0 // TODO:
      // serialize mc.mb_
      // propogate serialized mc.mb_ over network and shuffle keys in mc.mb_
      // unserialize to rc.rb_.
#else
			typename rc_type::bucket_type rb = mtq.mc.mb_; // reducer bucket
#endif
			rc_type rc(rb, ofmt_);

			for (typename rc_type::bucket_type::const_iterator ri = rc.rb_.begin(); // ri: reducer input (entry)
			     ri != rc.rb_.end();
			     ++ri) {
				reducer_type()(ri->first, ri->second, rc);
			}
		}
	}

private:

	IFMT ifmt_; //!< input format
	OFMT ofmt_; //!< output format
	size_t num_mappers;
	size_t num_reducers;

}; // class swk::job<>

} // namespace swk

#endif /* SWK_JOB_HPP_INCLUDED */

