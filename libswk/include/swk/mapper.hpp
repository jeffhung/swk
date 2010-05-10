#ifndef SWK_MAPPER_HPP_INCLUDED
#define SWK_MAPPER_HPP_INCLUDED

#include <swk/fs_local.hpp>
#include <vector>
#include <map>
#include <utility>

namespace swk {

template <class IK, class IV,
          class OK, class OV,
          class FS = fs_local>
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

template <class IK, class IV,
          class OK, class OV,
          class FS = fs_local>
class mapper
{
public:

	typedef mapper_context<IK, IV, OK, OV, FS> context;

	virtual void map(const IK& key, const IV& value, context& ctx) = 0;

}; // namespace swk::mapper

} // namespace swk

#endif /* SWK_MAPPER_HPP_INCLUDED */

