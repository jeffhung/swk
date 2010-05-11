//#include <swk/mr2/mapper.hpp>
//#include <swk/mr2/reducer.hpp>
#include <swk/mr3/job.hpp>
#include <swk/fs_local.hpp>
#include <swk/str_split.hpp>
#include <string>
#include <vector>
#include <stdint.h>

void wordcount_mapper(const uint32_t& key, const std::string& value,
//                      swk::mr3::mapper_context<uint32_t, std::string, std::string, uint32_t>& ctx)
                      swk::mr3::mapper_context& ctx)
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

void wordcount_reducer(const std::string& key, const std::vector<uint32_t>& values,
//                       swk::mr3::reducer_context<std::string, uint32_t, std::string, uint32_t>& ctx)
                       swk::mr3::reducer_context& ctx)
{
	uint32_t sum = 0;
	for (std::vector<uint32_t>::const_iterator it = values.begin();
	     it != values.end();
	     ++it) {
		sum += *it;
	}
	ctx.push(key, sum);
}

int main()
{
	try {
		std::auto_ptr<swk::mr3::job> wc(swk::mr3::make_job<uint32_t, std::string, std::string, uint32_t>(
			wordcount_mapper, wordcount_reducer
		));
		wc->add_input_path("data1.txt");
		wc->add_input_path("data2.txt");
		wc->add_input_path("data3.txt");
		wc->set_output_dir("output");
		wc->run();
		return 0;
	}
	catch (std::exception e) {
		return 1;
	}
}

