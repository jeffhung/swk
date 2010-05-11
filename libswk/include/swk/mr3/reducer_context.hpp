#ifndef SWK_MR3_REDUCER_CONTEXT_HPP_INCLUDED
#define SWK_MR3_REDUCER_CONTEXT_HPP_INCLUDED

#include <swk/dtool.hpp>
#include <swk/fs_local.hpp>
#include <vector>

namespace swk {
namespace mr3 {

class reducer_context
{
public:

	template <class OK, class OV>
	void push(const OK& ok, const OV& ov)
	{
	}
};

template <class IK, class IV, class OK, class OV>
class generic_reducer_context : public reducer_context
{
public:

	void push(const OK& ok, const OV& ov)
	{
		SWK_DOUT << ov << " <= " << ok;
	}

}; // class swk::reducer_context

} // namespace mr3
} // namespace swk

#endif /* SWK_MR3_REDUCER_CONTEXT_HPP_INCLUDED */


