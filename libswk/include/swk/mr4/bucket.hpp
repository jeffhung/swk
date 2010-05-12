#ifndef SWK_MR4_BUCKET_HPP_INCLUDED
#define SWK_MR4_BUCKET_HPP_INCLUDED

#include <vector>

namespace swk {
namespace mr4 {

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

}; // class swk::mr4::bucket

} // namespace swk::mr4
} // namespace swk

#endif /* SWK_MR4_BUCKET_HPP_INCLUDED */

