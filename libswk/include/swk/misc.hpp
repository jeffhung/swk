#ifndef SWK_MISC_HPP_INCLUDED
#define SWK_MISC_HPP_INCLUDED

#include <swk/config.hpp>
#include <swk/fs_local.hpp>

namespace swk {

/**
 * Saves the absolute position of the get pointer of an input channel, and
 * restore when destruct.
 */
class ifstream_position_saver
{
public:

	ifstream_position_saver(std::ifstream& ic)
		: ic_(ic)
		, pos_(ic.tellg())
	{
	}

	~ifstream_position_saver()
	{
		ic_.seekg(pos_);
	}

private:

	std::ifstream& ic_;
	std::ifstream::streampos pos_;

}; // class swk::ifstream_position_saver

} // namespace swk

#endif /* SWK_MISC_HPP_INCLUDED */

