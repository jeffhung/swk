#ifndef SWK_JOB_HPP_INCLUDED
#define SWK_JOB_HPP_INCLUDED

#include <swk/dtool.hpp>
#include <boost/thread.hpp>
#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>

namespace swk {

template <class M, class R, class FS = fs_local>
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
		input_paths.push_back(path);
	}

	void set_output_dir(const std::string& dir)
	{
		output_dir = dir;
	}

	void set_num_mappers(size_t nm)
	{
		num_mappers = nm;
	}

	void set_num_reducers(size_t nr)
	{
		num_reducers = nr;
	}

	void run()
	{
		mc_type mc;
		for (std::vector<std::string>::const_iterator ip = input_paths.begin(); // ip: input path
		     ip != input_paths.end();
		     ++ip) {
			std::ifstream ic(ip->c_str());
			mik_type no = 0;
			miv_type line;
			while (std::getline(ic, line)) {
				SWK_DOUT << line;
				++no;
				mapper_type()(no, line, mc);
			}
		}
		SWK_DMVEC(mc.mb_);

#if 0 // TODO:
      // serialize mc.mb_
      // propogate serialized mc.mb_ over network and shuffle keys in mc.mb_
      // unserialize to rc.rb_.
#else
		typename rc_type::bucket_type::type rb = mc.mb_; // reducer bucket
#endif

		rc_type rc(rb);
		for (typename rc_type::bucket_type::type::const_iterator ri = rc.rb_.begin(); // ri: reducer input (entry)
		     ri != rc.rb_.end();
		     ++ri) {
			reducer_type()(ri->first, ri->second, rc);
		}
	}

private:

	std::vector<std::string> input_paths;
	std::string output_dir;
	size_t num_mappers;
	size_t num_reducers;

}; // class swk::job<>

} // namespace swk

#endif /* SWK_JOB_HPP_INCLUDED */

