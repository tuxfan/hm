/*----------------------------------------------------------------------------*
 * HashMark C interface.
 *----------------------------------------------------------------------------*/

#ifndef hash_mark_h
#define hash_mark_h

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
\page hm_add_table
Add a new hash table.

\par Interface:
void hm_add_table(size_t * id)

@param id The hash id. This id can be used to access the hash in subsequent calls.
 */
void hm_add_table(size_t * id);

/*!
\page hm_add
Add a new hash entry.

\par Interface:
void hm_add(size_t id, const char * key, void * value)

@param id The id of the hash to which the key/value pair should be added. \n
@param key Hash string identifier. \n
@param value Value to add.
 */
void hm_add(size_t id, const char * key, void * value); 

/*!
\page hm_find
Find a hash entry.

\par Interface:
void * hm_find(size_t id, const char * key)

@param id The id of the hash to be searched. \n
@param key Hash string identifier. \n

@return The value associated with \b key.
 */
void * hm_find(size_t id, const char * key);

/*!
\page hm_remove
Remove an entry from a hash table.

\par Interface:
void hm_remove(size_t id, const char * key, int32_t free_memory)

@param id The id of the hash from which the key/value pair should be removed. \n
@param key Hash string identifier. \n
@param free_memory Boolean flag: If \b free_memory is set to \b 1, the value associated with \b key will be free'd.  If \b free_memory is \b 0, no action will be taken.
 */
void hm_remove(size_t id, const char * key, int32_t free_memory);

/*!
\page hm_remove_table
Remove a hash table.

\par Interface:
void hm_remove_table(size_t id, int32_t free_memory)

@param id The id of the hash to be removed. \n
@param free_memory Boolean flag: If \b free_memory is set to \b 1, the values associated with each key in the hash table will be free'd.  If \b free_memory is \b 0, no action will be taken.
 */
void hm_remove_table(size_t id, int32_t free_memory);

#if defined(__cplusplus)
}
#endif

#endif // hash_mark_h
