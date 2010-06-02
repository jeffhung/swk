#include <swk/mr4/mapper.hpp>
#include <swk/mr4/reducer.hpp>
#include <swk/mr4/job.hpp>
#include <swk/fs_local.hpp>
#include <swk/str_split.hpp>
#include <string>
#include <vector>
#include <stdint.h>

struct wordcount_mapper : public swk::mr4::mapper<uint32_t, std::string,
                                                  std::string, uint32_t>
{
	void operator()(const uint32_t& key,
	                const std::string& value,
	                context& ctx)
	{
		SWK_DOUT << value;
		std::vector<std::string> tokens = swk::str_split(value);
		for (std::vector<std::string>::const_iterator it = tokens.begin();
		     it != tokens.end();
		     ++it) {
			SWK_DVAR(*it);
			ctx.push(*it, uint32_t(1));
		}
	}

}; // class wordcount

struct wordcount_reducer : public swk::mr4::reducer<std::string, uint32_t,
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
		typedef swk::mr4::job<wordcount_mapper, wordcount_reducer> job_type;
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

