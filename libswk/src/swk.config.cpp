#include <swk/config.hpp>

static const swk_info_t g_swk_info = {
	SWK_VERSION_MAJOR,
	SWK_VERSION_MINOR
};

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

const swk_info_t& swk_info()
{
	return g_swk_info;
}

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

