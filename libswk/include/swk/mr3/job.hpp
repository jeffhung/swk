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
			typename FS::ichannel ic(ip->c_str());
			std::string line;
			uint32_t no = 0;
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

