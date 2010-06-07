#ifndef SWK_JOB_HPP_INCLUDED
#define SWK_JOB_HPP_INCLUDED

#include <swk/config.hpp>
#include <swk/dtool.hpp>
#include <swk/file_input.hpp>
#include <swk/file_split.hpp>
#include <swk/line_record_reader.hpp>
#include <swk/file_output.hpp>
#include <memory>
#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>

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

	void run()
	{
		mc_type mc;
		std::vector<swk::file_split> splits = ifmt_.list_splits();
		SWK_DVAR(splits.size());
		for (std::vector<swk::file_split>::const_iterator s = splits.begin();
		     s != splits.end();
		     ++s) {
			std::cout << *s << std::endl;
			swk::line_record_reader<> rr(*s);
			while (rr.advance()) {
				std::pair<uint64_t, std::string> c = rr.current();
				std::cout << "[" << c.first << "] " << c.second;
				mapper_type()(c.first, c.second, mc);
			}
//			std::cout << *s << std::endl;
		}
//		SWK_DMVEC(mc.mb_);

#if 0 // TODO:
      // serialize mc.mb_
      // propogate serialized mc.mb_ over network and shuffle keys in mc.mb_
      // unserialize to rc.rb_.
#else
		typename rc_type::bucket_type rb = mc.mb_; // reducer bucket
#endif
		rc_type rc(rb, ofmt_);

		for (typename rc_type::bucket_type::const_iterator ri = rc.rb_.begin(); // ri: reducer input (entry)
		     ri != rc.rb_.end();
		     ++ri) {
			reducer_type()(ri->first, ri->second, rc);
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

