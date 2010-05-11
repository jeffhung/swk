#ifndef SWK_MR2_MAPPER_HPP_INCLUDED
#define SWK_MR2_MAPPER_HPP_INCLUDED

#include <swk/fs_local.hpp>
#include <vector>
#include <map>
#include <utility>

namespace swk {
namespace mr2 {

template <class IK, class IV, class OK, class OV>
class mapper_context
{
public:

	typedef std::map<OK, std::vector<OV> > outputs_type;

	void push(const OK& ok, const OV& ov)
	{
		std::pair<typename outputs_type::iterator, bool> r
			= outputs_.insert(make_pair(ok, std::vector<OV>()));
		r.first->second.push_back(ov);
	}

	outputs_type outputs_;

}; // class swk::mapper_context

template <class IK, class IV, class OK, class OV>
class mapper
{
public:

	typedef mapper_context<IK, IV, OK, OV> context;

//	virtual void operator()(const IK& key,
//	                        const IV& value,
//	                        context& ctx) = 0;

}; // class swk::mapper

} // namespace swk::mr2
} // namespace swk

#endif /* SWK_MR2_MAPPER_HPP_INCLUDED */

