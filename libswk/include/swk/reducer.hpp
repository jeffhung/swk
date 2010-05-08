#ifndef SWK_REDUCER_HPP_INCLUDED
#define SWK_REDUCER_HPP_INCLUDED

#include <swk/fs_local.hpp>
#include <vector>

namespace swk {

template <class IK, class IV,
          class OK, class OV,
          class FS = fs_local>
class reducer_context
{
public:

	void push(const OK& ok, const OV& ov)
	{
	}

}; // class swk::reducer::context

template <class IK, class IV,
          class OK, class OV,
          class FS = fs_local>
class reducer
{
public:

	typedef reducer_context<IK, IV, OK, OV, FS> context;

	virtual void reduce(const IK& key,
	                    const std::vector<IV>& values,
	                    context& ctx) = 0;

}; // namespace swk::reducer

} // namespace swk

#endif /* SWK_REDUCER_HPP_INCLUDED */


