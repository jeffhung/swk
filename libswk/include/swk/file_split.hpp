#ifndef SWK_FILE_SPLIT_HPP_INCLUDED
#define SWK_FILE_SPLIT_HPP_INCLUDED

#include <swk/config.hpp>
#include <swk/dtool.hpp>
#include <string>
#include <algorithm>
#include <ostream>

namespace swk {

/**
 * A section of an input file.
 */
class file_split
{
friend std::ostream& operator << (std::ostream& os, const file_split& s);
public:

	/**
	 * Construct a split with host information.
	 *
	 * @param path   path of the file in dfs
	 * @param start  starting position of the bytes in the file to process
	 * @param l number of the bytes in the file to process
	 */
	file_split(const std::string& path, size_t start, size_t l)
		: path_(path)
		, start_(start)
		, length_(l)
	{
	}

	file_split(const file_split& x)
		: path_(x.path_)
		, start_(x.start_)
		, length_(x.length_)
	{
	}

	file_split& operator = (const file_split& x)
	{
		if (this != &x) {
			file_split(x).swap(*this);
		}
		return *this;
	}

	void swap(file_split& x)
	{
		if (this != &x) {
			std::swap(path_, x.path_);
			std::swap(start_, x.start_);
			std::swap(length_, x.length_);
		}
	}

	size_t length() const
	{
		return length_;
	}

	/**
	 * Extend length @p n bytes.
	 */
	void extend(size_t n)
	{
		length_ += n;
	}

private:

	std::string path_;
	size_t start_;
	size_t length_;

}; // class swk::file_split

std::ostream& operator << (std::ostream& os, const file_split& s)
{
	os << "------> " << s.path_ << "@[" << s.start_ << "," << s.length_ << "]";
	os << std::endl;
	std::ifstream ifs(s.path_.c_str());
	ifs.seekg(s.start_);
//	char buffer[SWK_BLOCK_SIZE + 10] = { 0 };
	char buffer[4096] = { 0 };
	SWK_DVAR(s.length_);
	if (ifs.read(buffer, s.length_)) {
		os << buffer << "||";
	}
	return os;
}

} // namespace swk

#endif /* SWK_FILE_SPLIT_HPP_INCLUDED */

