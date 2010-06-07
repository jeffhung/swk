#ifndef SWK_MAPPER_HPP_INCLUDED
#define SWK_MAPPER_HPP_INCLUDED

#include <swk/config.hpp>
#include <swk/fs_local.hpp>
#include <swk/bucket.hpp>
#include <vector>
#include <map>
#include <utility>

namespace swk {

template <class IK, class IV, class OK, class OV>
class mapper_context
{
public:

	typedef IK ik_type;
	typedef IV iv_type;
	typedef OK ok_type;
	typedef OV ov_type;
	typedef bucket<OK, OV> bucket_type;

	void push(const OK& ok, const OV& ov)
	{
		std::pair<typename bucket_type::type::iterator, bool> r
			= mb_.insert(make_pair(ok, typename bucket_type::bvs_type()));
		r.first->second.push_back(ov);
	}

	typename bucket_type::type mb_;

}; // class swk::mapper_context

template <class IK, class IV, class OK, class OV>
class mapper
{
public:

	typedef IK ik_type;
	typedef IV iv_type;
	typedef OK ok_type;
	typedef OV ov_type;
	typedef mapper_context<IK, IV, OK, OV> context;

//	virtual void operator()(const ik_type& key,
//	                        const iv_type& value,
//	                        context& ctx) = 0;

}; // class swk::mapper

} // namespace swk

#endif /* SWK_MAPPER_HPP_INCLUDED */

