#ifndef SWK_MAPPER_HPP_INCLUDED
#define SWK_MAPPER_HPP_INCLUDED

#include <swk/fs_local.hpp>

namespace swk {

template <class IK, class IV,
          class OK, class OV,
          class FS = fs_local>
class mapper_context
{
public:

	void push(const OK& ok, const OV& ov)
	{
	}

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

