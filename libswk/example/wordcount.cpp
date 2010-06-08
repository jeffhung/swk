#include <swk/mapper.hpp>
#include <swk/reducer.hpp>
#include <swk/job.hpp>
#include <swk/fs_local.hpp>
#include <swk/str_tool.hpp>
#include <string>
#include <vector>
#include <stdint.h>

struct wordcount_mapper : public swk::mapper<uint32_t, std::string,
                                             std::string, uint32_t>
{
	void operator()(const uint32_t& key,
	                const std::string& value,
	                context& ctx)
	{
//		SWK_DVAR(value);
		std::vector<std::string> tokens = swk::str_tokenize(value);
		for (std::vector<std::string>::const_iterator it = tokens.begin();
		     it != tokens.end();
		     ++it) {
//			SWK_DVAR(*it);
			ctx.push(*it, uint32_t(1));
		}
	}

}; // class wordcount

struct wordcount_reducer : public swk::reducer<std::string, uint32_t,
                                               std::string, uint32_t>
{
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
		typedef swk::job<wordcount_mapper, wordcount_reducer> job_type;
		job_type wc;
		wc.add_input_path("data1.txt");
		wc.add_input_path("data2.txt");
		wc.add_input_path("data3.txt");
		wc.add_input_path("hbase-overview.txt");
		wc.set_output_dir("output");
		wc.run();
		return 0;
	}
	catch (std::exception e) {
		return 1;
	}
}

