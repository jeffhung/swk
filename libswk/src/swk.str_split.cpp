#include <swk/config.hpp>
#include <swk/str_split.hpp>
#include <swk/dtool.hpp>
#include <string>
#include <vector>
#include <cstring>

namespace swk {

std::vector<std::string> str_split(const std::string& s)
{
	std::vector<std::string> tokens;
	std::string::size_type b = 0;
	std::string::size_type e = 0;
	const char* WS = " \t\r\n";
	do {
		e = s.find_first_of(WS, b);
		if (e != std::string::npos) {
			std::string token = s.substr(b, (e - b));
			SWK_DVAR(token);
			b = s.find_first_not_of(WS, e);
		}
	} while ((b != std::string::npos) && (e != std::string::npos));
	return tokens;
}

} // namespace swk

