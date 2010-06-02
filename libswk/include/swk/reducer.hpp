#ifndef SWK_REDUCER_HPP_INCLUDED
#define SWK_REDUCER_HPP_INCLUDED

#include <swk/dtool.hpp>
#include <swk/fs_local.hpp>
#include <swk/bucket.hpp>
#include <vector>

namespace swk {

template <class IK, class IV, class OK, class OV>
class reducer_context
{
public:

	typedef IK ik_type;
	typedef IV iv_type;
	typedef OK ok_type;
	typedef OV ov_type;
	typedef bucket<OK, OV> bucket_type;

	reducer_context(const typename bucket_type::type& rb)
		: rb_(rb)
	{
	}

	void push(const OK& ok, const OV& ov)
	{
		SWK_DOUT << ov << " <= " << ok;
	}

	typename bucket_type::type rb_;

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

} // namespace swk

#endif /* SWK_REDUCER_HPP_INCLUDED */


