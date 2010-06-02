#ifndef SWK_FILE_TRAITS_HPP_INCLUDED
#define SWK_FILE_TRAITS_HPP_INCLUDED

#include <string>
#include <vector>
#include <algorithm>

namespace swk {

/**
 * Traits of raw file where content are treated as a byte array.
 */
struct raw_file_traits
{
	static bool splittable()
	{
		return true;
	}
}; // class swk::raw_file_traits

} // namespace swk

#endif /* SWK_FILE_TRAITS_HPP_INCLUDED */



