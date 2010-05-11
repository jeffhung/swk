#ifndef SWK_MR3_MAPPER_CONTEXT_HPP_INCLUDED
#define SWK_MR3_MAPPER_CONTEXT_HPP_INCLUDED

#include <swk/fs_local.hpp>
#include <vector>
#include <map>
#include <utility>

namespace swk {
namespace mr3 {

class mapper_context
{
public:

	template <class OK, class OV>
	void push(const OK& ok, const OV& ov)
	{
	}
};

template <class IK, class IV, class OK, class OV>
class generic_mapper_context : public mapper_context
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

} // namespace swk::mr3
} // namespace swk

#endif /* SWK_MR3_MAPPER_CONTEXT_HPP_INCLUDED */

