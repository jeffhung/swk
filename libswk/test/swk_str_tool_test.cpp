#include <swk/config.hpp>
#include <swk/str_tool.hpp>
#include <swk/dtool.hpp>
#include <string>
#include <vector>
#include <iostream>

const char* text1 = "WordCount example reads text files and counts how often words occur. The input is text files and the output is text files, each line of which contains a word and the count of how often it occured, separated by a tab.";

int main()
{
	std::vector<std::string> tokens = swk::str_tokenize(text1);
	for (std::vector<std::string>::const_iterator it = tokens.begin();
	     it != tokens.end();
	     ++it) {
		SWK_DVAR(*it);
	}
	return 0;
}

