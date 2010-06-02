#include <swk/file_input_format.hpp>
#include <swk/file_split.hpp>
#include <vector>
#include <iostream>

int main()
{
	try {
		swk::file_input_format<> iformat;
		iformat.add_path("data1.txt");
		iformat.add_path("data2.txt");
		iformat.add_path("data3.txt");
		iformat.add_path("telecomm_v1.xml");
		std::vector<swk::file_split> splits = iformat.list_splits();
		for (std::vector<swk::file_split>::const_iterator s = splits.begin();
		     s != splits.end();
		     ++s) {
			std::cout << *s << std::endl;
		}
		return 0;
	}
	catch (std::exception e) {
		return 1;
	}
}

