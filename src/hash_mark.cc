/*----------------------------------------------------------------------------*
 * HashMark C bindings implementation.
 *----------------------------------------------------------------------------*/

#include <hm_hash.hh>
#include <hash_mark.h>

hm_hash & hash = hm_hash::instance();

void hm_add_table(size_t * id) {
	*id = hash.add_table();
} // hm_add_table

void hm_add(size_t id, const char * key, void * value) {
	hash.add(id, key, value);
} // hm_add

void * hm_find(size_t id, const char * key) {
	return hash.find(id, key);
} // hm_find

void hm_remove(size_t id, const char * key, int32_t free_memory) {
	hash.remove(id, key, free_memory);
} // hm_remove

void hm_remove_table(size_t id, int32_t free_memory) {
	hash.remove_table(id, free_memory);
} // hm_remove_table
