#ifndef SWK_FILE_TRAITS_HPP_INCLUDED
#define SWK_FILE_TRAITS_HPP_INCLUDED

#include <swk/misc.hpp>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

namespace swk {

template <class FS>
struct base_file_traits
{

	enum { splittable };

//	/** Opens file in @p path with proper open mode. */
//	void open(std::ifstream& ic, const std::string& path);

	/**
	 * Find next record boundary in input channel @p ic, starting at @p
	 * start.
	 */
	size_t find_boundary(std::ifstream& ic, size_t start);

}; // class swk::base_file_traits<>

/**
 * Traits of raw files where content are treated as a byte array and split at
 * anywhere.
 */
template <class FS>
struct raw_file_traits : public base_file_traits<FS>
{
	enum { splittable = 1 };

//	void open(std::ifstream& ic, const std::string& path)
//	{
//		ic.open(path.c_str(), std::ios::in | std::ios::binary);
//	}

	size_t find_boundary(std::ifstream& ic, size_t start)
	{
		// In raw file, anywhere can be the boundary. So that's use start,
		// which is decided by *_input_format, as the boundary.
		return start;
	}

}; // class swk::raw_file_traits

/**
 * Traits of text files where content are treated as lines of texts and split
 * at line ends. All three CR, LF, and CRLF are recognized.
 */
template <class FS>
struct text_file_traits
{
	enum { splittable = 1 };

//	void open(std::ifstream& ic, const std::string& path)
//	{
//		ic.open(path.c_str(), std::ios::in);
//	}

	static size_t find_boundary(std::ifstream& ic, size_t start)
	{
		static const char* LINE_ENDS[] = { "\x0a", "\x0c", "\x0a\x0c", 0 };
		ifstream_position_saver ips(ic);
		do {
			std::ifstream::char_type buffer[8];
			ic.seekg(start);
			size_t size = ic.readsome(buffer, sizeof(buffer) - 1);
			buffer[size] = '\0'; // null end it to pass to strstr()
			for (size_t i = 0; LINE_ENDS[i]; ++i) {
				char* p = strstr(buffer, LINE_ENDS[i]);
				if (p) {
					return start + (p - buffer) + strlen(LINE_ENDS[i]);
				}
			}
			start += size;
		} while (ic);
		return start;
	}

}; // class swk::text_file_traits

} // namespace swk

#endif /* SWK_FILE_TRAITS_HPP_INCLUDED */



