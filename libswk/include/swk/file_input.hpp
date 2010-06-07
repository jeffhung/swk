#ifndef SWK_FILE_INPUT_HPP_INCLUDED
#define SWK_FILE_INPUT_HPP_INCLUDED

#include <swk/config.hpp>
#include <swk/file_traits.hpp>
#include <swk/file_split.hpp>
#include <swk/fs_local.hpp>
#include <swk/dtool.hpp>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <utility>

namespace swk {

/**
 * A section of an input file.
 */
template <class FS = fs_local, class FT = text_file_traits<FS> >
class file_input
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
			std::ifstream ic(path->c_str(), std::ios::binary); // must open in binary mode
			if ((length > 0) && FT::splittable) {
				size_t start = 0;
				do {
//					SWK_DVAR(start);
					size_t split_size = std::min<size_t>((length - start), SWK_BLOCK_SIZE);
					if (!splits.empty() &&
					    (splits.at(splits.size() - 1).path() == *path)) {
						size_t boundary = FT::find_boundary(ic, start);
						if (boundary > start) {
//							SWK_DVAR(boundary);
							size_t size_move_to_previous_split = boundary - start;
//							SWK_DVAR(size_move_to_previous_split);
							file_split& last = splits.at(splits.size() - 1);
							last.extend(size_move_to_previous_split);
//							SWK_DVAR(last.length());
							start = boundary;
							split_size -= size_move_to_previous_split;
						}
					}
//					SWK_DVAR(start);
//					SWK_DVAR(split_size);
					if (split_size > 0) {
						splits.push_back(file_split(*path, start, split_size));
					}
					start += split_size;
				} while (start < length);
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

}; // class swk::file_input<>

} // namespace swk

#endif /* SWK_FILE_INPUT_HPP_INCLUDED */


