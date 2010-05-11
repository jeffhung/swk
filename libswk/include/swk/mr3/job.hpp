#ifndef SWK_MR3_JOB_HPP_INCLUDED
#define SWK_MR3_JOB_HPP_INCLUDED

#include <swk/dtool.hpp>
#include <swk/fs_local.hpp>
#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>

namespace swk {
namespace mr3 {

class mr_context
{
public:

	template <class K, class V>
	void push(const K& k, const V& v)
	{
	}
};

typedef mr_context mapper_context;
typedef mr_context reducer_context;

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

template <class M, class R, class FS = fs_local>
class generic_job : public job
{
public:

	virtual void run()
	{
//		M m;
//		mapper_context mc;
//		for (std::vector<std::string>::const_iterator ip = input_paths.begin(); // ip: input path
//		     ip != input_paths.end();
//		     ++ip) {
//			typename FS::ichannel ic(ip->c_str());
//			std::string line;
//			uint32_t no = 0;
//			while (std::getline(ic, line)) {
//				SWK_DOUT << line;
//				++no;
//				m(no, line, mc);
//			}
//		}
//		SWK_DMVEC(mc.outputs_);
//
//		R r;
//		reducer_context rc;
//		for (typename M::context::outputs_type::const_iterator me = mc.outputs_.begin(); // me: map entry
//		     me != mc.outputs_.end();
//		     ++me) {
//			r(me->first, me->second, rc);
//		}
	}
};

template <class M, class R>
std::auto_ptr<job> make_job(M m, R r)
{
	return std::auto_ptr<job>(new generic_job<M, R>());
}

} // namespace swk::mr3
} // namespace swk

#endif /* SWK_MR3_JOB_HPP_INCLUDED */

