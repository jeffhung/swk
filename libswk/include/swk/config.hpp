#ifndef SWK_CONFIG_HPP_INCLUDED
#define SWK_CONFIG_HPP_INCLUDED

#define SWK_VERSION_MAJOR 0
#define SWK_VERSION_MINOR 1

#define SWK_USE_INPUT_FORMAT 1

//#define SWK_BLOCK_SIZE (64 * 1024 * 1024) // 64MB
#define SWK_BLOCK_SIZE 256

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct swk_info_t
{
	int version_major;
	int version_minor;
}; // struct swk_info

const swk_info_t& swk_info();

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

#endif /* SWK_CONFIG_HPP_INCLUDED */

