#ifndef SWK_BUCKET_HPP_INCLUDED
#define SWK_BUCKET_HPP_INCLUDED

#include <swk/config.hpp>
#include <vector>
#include <map>

namespace swk {

/**
 * Bucket is the intermediate data package between mapper and reducer.
 *
 * @tparam K key type, should convertable from M::ok_type and to R::ik_type.
 * @tparam V value type, should convertable from M::ov_type and to R::iv_type.
 */
template <class K, class V>
class bucket
{
public:

	typedef K bk_type;
	typedef V bv_type;

	typedef std::vector<bv_type> bvs_type; // bucket value set
	typedef std::map<bk_type, bvs_type> type;

}; // class swk::bucket

} // namespace swk

#endif /* SWK_BUCKET_HPP_INCLUDED */

