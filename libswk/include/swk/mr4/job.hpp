#ifndef SWK_MR4_JOB_HPP_INCLUDED
#define SWK_MR4_JOB_HPP_INCLUDED

#include <swk/dtool.hpp>
#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>

namespace swk {
namespace mr4 {

template <class M, class R, class FS = fs_local>
class job
{
public:

	typedef M mapper_type;
	typedef R reducer_type;
	typedef M::ik_type mik_type;
	typedef M::iv_type miv_type;
	typedef M::ok_type mok_type;
	typedef M::ov_type mov_type;
	typedef R::ik_type rik_type;
	typedef R::iv_type riv_type;
	typedef R::ok_type rok_type;
	typedef R::ov_type rov_type;

	typedef M::context mc_type;
	typedef R::context rc_type;

//	SWK_STATIC_ASSERT(
//		swk::and<
//			swk::convertable<mok_type, rik_type>::value,
//			swk::convertable<mov_type, riv_type>::value
//		>::value
//	);

	void add_input_path(const std::string& path)
	{
		input_paths.push_back(path);
	}

	void set_output_dir(const std::string& dir)
	{
		output_dir = dir;
	}

	void run()
	{
		mapper_type m;
		mc_type mc;
		for (std::vector<std::string>::const_iterator ip = input_paths.begin(); // ip: input path
		     ip != input_paths.end();
		     ++ip) {
			typename FS::ichannel ic(ip->c_str());
			mik_type no = 0;
			miv_type line;
			while (std::getline(ic, line)) {
				SWK_DOUT << line;
				++no;
				m(no, line, mc);
			}
		}
		SWK_DMVEC(mc.mb_);

#if 0 // TODO:
      // serialize mc.mb_
      // propogate serialized mc.mb_ over network and shuffle keys in mc.mb_
      // unserialize to rc.rb_.
#else
		typename rc_type::bucket_type rb = mc.mb_; // reducer bucket
#endif

		reducer_type r;
		rc_type rc(rb);
		for (rc_type::bucket_type::type::const_iterator ri = rc.rb_.begin(); // ri: reducer input (entry)
		     ri != rc.rb_.end();
		     ++ri) {
			r(ri->first, ri->second, rc);
		}
	}

private:

	std::vector<std::string> input_paths;
	std::string output_dir;

};

} // namespace swk::mr4
} // namespace swk

#endif /* SWK_MR4_JOB_HPP_INCLUDED */

