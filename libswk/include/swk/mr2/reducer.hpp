#ifndef SWK_MR2_REDUCER_HPP_INCLUDED
#define SWK_MR2_REDUCER_HPP_INCLUDED

#include <swk/dtool.hpp>
#include <swk/fs_local.hpp>
#include <vector>

namespace swk {
namespace mr2 {

template <class IK, class IV, class OK, class OV>
class reducer_context
{
public:

	void push(const OK& ok, const OV& ov)
	{
		SWK_DOUT << ov << " <= " << ok;
	}

}; // class swk::reducer_context

template <class IK, class IV, class OK, class OV>
class reducer
{
public:

	typedef reducer_context<IK, IV, OK, OV> context;

//	virtual void operator()(const IK& key,
//	                        const std::vector<IV>& values,
//	                        context& ctx) = 0;

}; // class swk::reducer

} // namespace mr2
} // namespace swk

#endif /* SWK_MR2_REDUCER_HPP_INCLUDED */


