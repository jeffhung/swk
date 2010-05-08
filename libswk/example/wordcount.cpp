#include <swk/mapper.hpp>
#include <swk/reducer.hpp>
#include <swk/job.hpp>
#include <swk/fs_local.hpp>
#include <swk/str_split.hpp>
#include <string>
#include <vector>
#include <stdint.h>

class wordcount_mapper : swk::mapper<uint32_t, std::string,
                                     std::string, uint32_t,
                                     swk::fs_local>
{
public:

	typedef swk::mapper<uint32_t, std::string,
	                    std::string, uint32_t,
	                    swk::fs_local>::context context;

	void map(const uint32_t& key,
	         const std::string& value,
	         context& ctx)
	{
		std::vector<std::string> tokens = swk::str_split(value);
		for (std::vector<std::string>::const_iterator it = tokens.begin();
		     it != tokens.end();
		     ++it) {
			ctx.push(*it, 1);
		}
	}

}; // class wordcount

class wordcount_reducer : swk::reducer<std::string, uint64_t,
                                       std::string, uint64_t,
                                       swk::fs_local>
{
	void reduce(const std::string& key,
	            const std::vector<uint64_t>& values,
	            context& ctx)
	{
		uint64_t sum = 0;
		for (std::vector<uint64_t>::const_iterator it = values.begin();
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
		typedef swk::job<wordcount_mapper, wordcount_reducer> wordcount_job;
		wordcount_job wc;
		wc.add_input_path("input1.txt");
		wc.add_input_path("input2.txt");
		wc.add_input_path("input3.txt");
		wc.set_output_dir("output");
		wc.run();
		return 0;
	}
	catch (std::exception e) {
		return 1;
	}
}

