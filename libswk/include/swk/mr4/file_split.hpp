#ifndef SWK_MR4_FILE_SPLIT_HPP_INCLUDED
#define SWK_MR4_FILE_SPLIT_HPP_INCLUDED

#include <string>
#include <algorithm>
#include <ostream>

namespace swk {
namespace mr4 {

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
	 * @param length number of the bytes in the file to process
	 */
	file_split(const std::string& path, size_t start, size_t length)
		: path_(path)
		, start_(start)
		, length_(length)
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

private:

	std::string path_;
	size_t start_;
	size_t length_;

}; // class swk::mr4::file_split

std::ostream& operator << (std::ostream& os, const file_split& s)
{
	os << s.path_ << "@[" << s.start_ << "," << s.length_ << "]";
	return os;
}

} // namespace swk::mr4
} // namespace swk

#endif /* SWK_MR4_FILE_SPLIT_HPP_INCLUDED */


