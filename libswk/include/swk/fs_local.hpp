#ifndef SWK_FS_LOCAL_HPP_INCLUDED
#define SWK_FS_LOCAL_HPP_INCLUDED

#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <sys/stat.h>

namespace swk {

class fs_local
{
public:

	static size_t file_length(const std::string& path)
	{
		struct stat sb;
		if (0 != stat(path.c_str(), &sb)) {
			throw std::runtime_error("Cannot get file status.");
		}
		return sb.st_size;
	}

}; // class swk::fs_local

} // namespace swk

#endif /* SWK_FS_LOCAL_HPP_INCLUDED */

