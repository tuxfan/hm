/*----------------------------------------------------------------------------*
 * HashMark C interface.
 *----------------------------------------------------------------------------*/

#ifndef hash_mark_h
#define hash_mark_h

#include <stdint.h>
#include <stddef.h>

#define _include_hash_mark_h

#include <hm_flags.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*!
\page hashmark
Hash table interface.

\par Description:
HashMark is a set of C functions for creating and managing hash tables.  It is designed to be thread-safe and simple, and is built on top of the STL std::map class.  The actual underlying C++ data type is a \b std::map<size_t, \b std::map<std::string, \b void \b *>>.  Thread safety is achieved using \b std::mutex and \b std::guard_lock (these may or may not be very efficient).

\par Documentation:
Documentation is available for the individual subroutines, e.g., man hm_add

\par Main Interface:
The main interface allows creation and manipulation of hash tables.  It consists of the following functions: \n\n
\ref hm_add_table \n
\ref hm_add \n
\ref hm_find \n
\ref hm_table_exists \n
\ref hm_key_exists \n
\ref hm_remove \n
\ref hm_remove_table \n
\ref hm_clear \n
\ref hm_set_property \n
\ref hm_unset_property \n
\ref hm_error_string \n
 */

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
\page hm_table_exists
Check if hash entry exists.

\par Interface:
int32_t hm_table_exists(size_t id);

@param id The id of the hash to be checked. \n

@return This function returns \b 1 if the table exists, \b 0 otherwise.
 */
int32_t hm_table_exists(size_t id, const char * key);

/*!
\page hm_key_exists
Check if hash entry exists.

\par Interface:
int32_t hm_key_exists(size_t id, const char * key);

@param id The id of the hash to be checked. \n
@param key Hash string identifier. \n

@return This function returns \b 1 if the key exists, \b 0 otherwise.
 */
int32_t hm_key_exists(size_t id, const char * key);

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

/*!
\page hm_clear
Remove all tables and entries from HashMark.

\par Interface:
void hm_clear(int32_t free_memory)

@param free_memory Boolean flag: If \b free_memory is set to \b 1, the values associated with each key in the hash table will be free'd.  If \b free_memory is \b 0, no action will be taken.
 */
void hm_clear(int32_t free_memory);

/*!
\page hm_set_property
Set hash property.

\par Interface:
void hm_set_property(uint32_t property)

@param property The bitwise flag of the property to set.
 */
void hm_set_property(uint32_t property);

/*!
\page hm_unset_property
Unset hash property.

\par Interface:
void hm_unset_property(uint32_t property)

@param property The bitwise flag of the property to unset.
 */
void hm_unset_property(uint32_t property);

/*!
\page hm_error_string
Translate a HashMark error code into human-readable text.

\par Interface:
const char * hm_error_string(int32_t code)

@param code Error code to be translated.
 */
const char * hm_error_string(int32_t code);

#if defined(__cplusplus)
}
#endif

#endif // hash_mark_h
