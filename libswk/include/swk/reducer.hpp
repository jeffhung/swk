#ifndef SWK_REDUCER_HPP_INCLUDED
#define SWK_REDUCER_HPP_INCLUDED

#include <swk/config.hpp>
#include <swk/dtool.hpp>
#include <swk/fs_local.hpp>
#include <swk/bucket.hpp>
#if SWK_USE_OUTPUT_FORMAT
# include <swk/file_output.hpp>
#endif // SWK_USE_OUTPUT_FORMAT
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
#if SWK_USE_OUTPUT_FORMAT
	typedef record_writer<ok_type, ov_type> rw_type;
#endif // SWK_USE_OUTPUT_FORMAT

#if SWK_USE_OUTPUT_FORMAT
	reducer_context(const bucket_type& rb, file_output<>& rw)
		: rb_(rb)
		, rw_(rw)
#else // !SWK_USE_OUTPUT_FORMAT
	reducer_context(const bucket_type& rb)
		: rb_(rb)
#endif // SWK_USE_OUTPUT_FORMAT
	{
	}

	void push(const OK& ok, const OV& ov)
	{
#if SWK_USE_OUTPUT_FORMAT
		rw_.write(ok, ov);
#else // !SWK_USE_OUTPUT_FORMAT
		SWK_DOUT << ov << " <= " << ok;
#endif // SWK_USE_OUTPUT_FORMAT
	}

	bucket_type rb_;
#if SWK_USE_OUTPUT_FORMAT
//	std::auto_ptr<rw_type> rw_;
	file_output<> rw_;
#endif // SWK_USE_OUTPUT_FORMAT

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


