#ifndef SWK_JOB_HPP_INCLUDED
#define SWK_JOB_HPP_INCLUDED

#include <swk/dtool.hpp>
#include <string>
#include <vector>
#include <stdint.h>
#include <iostream>

namespace swk {

template <class M, class R, class FS = fs_local>
class job
{
public:

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
		M m;
		typename M::context mc;
		for (std::vector<std::string>::const_iterator ip = input_paths.begin();
		     ip != input_paths.end();
		     ++ip) {
			typename FS::ichannel ic(ip->c_str());
			std::string line;
			uint32_t no = 0;
			while (std::getline(ic, line)) {
				SWK_DOUT << line;
				++no;
				m.map(no, line, mc);
			}
		}
		SWK_DMVEC(mc.outputs_);
	}

private:

	std::vector<std::string> input_paths;
	std::string output_dir;

};

} // namespace swk

#endif /* SWK_JOB_HPP_INCLUDED */

