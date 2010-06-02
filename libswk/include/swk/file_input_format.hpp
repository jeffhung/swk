#ifndef SWK_FILE_INPUT_FORMAT_HPP_INCLUDED
#define SWK_FILE_INPUT_FORMAT_HPP_INCLUDED

#include <swk/config.hpp>
#include <swk/file_traits.hpp>
#include <swk/file_split.hpp>
#include <swk/fs_local.hpp>
#include <string>
#include <vector>
#include <algorithm>

namespace swk {

/**
 * A section of an input file.
 */
template <class FT = raw_file_traits, class FS = fs_local>
class file_input_format
{
public:

	void add_path(const std::string& path)
	{
		paths_.push_back(path);
	}

	/**
	 * Get list of splits from added paths.
	 */
	std::vector<file_split> list_splits() const
	{
		std::vector<file_split> splits;

		for (std::vector<std::string>::const_iterator path = paths_.begin();
		     path != paths_.end();
		     ++path) {
			size_t length = FS::file_length(*path);
			if ((length > 0) && FT::splittable()) {
				size_t split_size = SWK_BLOCK_SIZE;
				size_t start = 0;
				while ((length - start) > split_size) {
					splits.push_back(file_split(*path, start, split_size));
					start += split_size;
				}
				if (start < length) {
					splits.push_back(file_split(*path, start, (length - start)));
				}
			}
			else if (length > 0) {
				splits.push_back(file_split(*path, 0, length));
			}
			else {
				// Create empty hosts array for zero length files.
				splits.push_back(file_split(*path, 0, length));
			}
		}

		return splits;
	}

private:

	std::vector<std::string> paths_;

}; // class swk::file_input_format<>

} // namespace swk

#endif /* SWK_FILE_INPUT_FORMAT_HPP_INCLUDED */


