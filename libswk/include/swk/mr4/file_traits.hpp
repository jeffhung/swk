#ifndef SWK_MR4_FILE_TRAITS_HPP_INCLUDED
#define SWK_MR4_FILE_TRAITS_HPP_INCLUDED

#include <string>
#include <vector>
#include <algorithm>

namespace swk {
namespace mr4 {

/**
 * Traits of raw file where content are treated as a byte array.
 */
struct raw_file_traits
{
	static bool splittable()
	{
		return true;
	}
};

} // namespace swk::mr4
} // namespace swk

#endif /* SWK_MR4_FILE_TRAITS_HPP_INCLUDED */



