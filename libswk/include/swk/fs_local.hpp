#ifndef SWK_FS_LOCAL_HPP_INCLUDED
#define SWK_FS_LOCAL_HPP_INCLUDED

#include <fstream>

namespace swk {

class fs_local
{
public:

	typedef std::ifstream ichannel;
	typedef std::ofstream ochannel;

}; // class swk::fs_local

} // namespace swk

#endif /* SWK_FS_LOCAL_HPP_INCLUDED */

