#ifndef SWK_REDUCER_HPP_INCLUDED
#define SWK_REDUCER_HPP_INCLUDED

#include <swk/dtool.hpp>
#include <swk/fs_local.hpp>
#include <vector>

namespace swk {
namespace mr1 {

template <class IK, class IV,
          class OK, class OV,
          class FS = fs_local>
class reducer_context
{
public:

	void push(const OK& ok, const OV& ov)
	{
		SWK_DOUT << ov << " <= " << ok;
	}

}; // class swk::reducer_context

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

}; // class swk::reducer

} // namespace mr1
} // namespace swk

#endif /* SWK_REDUCER_HPP_INCLUDED */


