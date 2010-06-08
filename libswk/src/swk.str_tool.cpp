#include <swk/config.hpp>
#include <swk/str_tool.hpp>
#include <swk/dtool.hpp>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>

namespace swk {

std::vector<std::string> str_tokenize(const std::string& s)
{
	std::vector<std::string> tokens;
	std::istringstream iss(s);
	std::string token;
	while (iss >> token) {
		tokens.push_back(token);
	}
	return tokens;
}

} // namespace swk
