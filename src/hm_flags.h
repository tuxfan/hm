/*----------------------------------------------------------------------------*
 * Various flags for HashMark configuration
 *----------------------------------------------------------------------------*/

#ifndef hm_flags_h
#define hm_flags_h

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*----------------------------------------------------------------------------*
 * Property flags
 *----------------------------------------------------------------------------*/

static const uint32_t hm_free_data = 0x01;
static const uint32_t hm_exit_on_error = 0x02;

/*----------------------------------------------------------------------------*
 * Error flags
 *----------------------------------------------------------------------------*/

static const int32_t hm_success = 0;
static const int32_t hm_invalid_hash_token = -1;
static const int32_t hm_invalid_hash_key = -2;
static const int32_t hm_hash_key_exists = -3;

#if defined(__cplusplus)
} // extern
#endif

#endif // hm_flags_h
