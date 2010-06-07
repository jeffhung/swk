#ifndef SWK_REDUCER_HPP_INCLUDED
#define SWK_REDUCER_HPP_INCLUDED

#include <swk/config.hpp>
#include <swk/dtool.hpp>
#include <swk/fs_local.hpp>
#include <swk/bucket.hpp>
#include <swk/file_output.hpp>
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
	typedef typename bucket_map<OK, OV>::type bucket_type;
	typedef record_writer<ok_type, ov_type> rw_type;

	reducer_context(const bucket_type& rb, file_output<>& rw)
		: rb_(rb)
		, rw_(rw)
	{
	}

	void push(const OK& ok, const OV& ov)
	{
		rw_.write(ok, ov);
	}

	bucket_type rb_;
//	std::auto_ptr<rw_type> rw_;
	file_output<> rw_;

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


