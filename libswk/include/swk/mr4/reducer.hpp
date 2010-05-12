#ifndef SWK_MR4_REDUCER_HPP_INCLUDED
#define SWK_MR4_REDUCER_HPP_INCLUDED

#include <swk/dtool.hpp>
#include <swk/fs_local.hpp>
#include <swk/mr4/bucket.hpp>
#include <vector>

namespace swk {
namespace mr4 {

template <class IK, class IV, class OK, class OV>
class reducer_context
{
public:

	typedef IK ik_type;
	typedef IV iv_type;
	typedef OK ok_type;
	typedef OV ov_type;
	typedef bucket<OK, OV> bucket_type;

	reducer_context(const bucket_type& rb)
		: rb_(rb)
	{
	}

	void push(const OK& ok, const OV& ov)
	{
		SWK_DOUT << ov << " <= " << ok;
	}

	bucket_type::type rb_;

}; // class swk::reducer_context

template <class IK, class IV, class OK, class OV>
class reducer
{
public:

	typedef IK ik_type;
	typedef IV iv_type;
	typedef OK ok_type;
	typedef OV ov_type;
	typedef reducer_context<IK, IV, OK, OV> context;

//	virtual void operator()(const IK& key,
//	                        const std::vector<IV>& values,
//	                        context& ctx) = 0;

}; // class swk::reducer

} // namespace mr4
} // namespace swk

#endif /* SWK_MR4_REDUCER_HPP_INCLUDED */


