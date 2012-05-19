/*----------------------------------------------------------------------------*
 * HashMark C bindings implementation.
 *----------------------------------------------------------------------------*/

#include <hm_hash.hh>
#include <hash_mark.h>

hm_hash & hash = hm_hash::instance();

int32_t hm_result;

void hm_add_table(size_t * id) {
	*id = hash.add_table();
	hm_result = hash.result();
} // hm_add_table

void hm_add(size_t id, const char * key, void * value) {
	hash.add(id, key, value);
	hm_result = hash.result();
} // hm_add

void * hm_find(size_t id, const char * key) {
	void * _tmp = hash.find(id, key);
	hm_result = hash.result();
	return _tmp;
} // hm_find

int32_t hm_table_exists(size_t id) {
	int32_t _value = hash.table_exists(id);
	hm_result = hash.result();
	return _value;
} // hm_key_exists

int32_t hm_key_exists(size_t id, const char * key) {
	int32_t _value = hash.key_exists(id, key);
	hm_result = hash.result();
	return _value;
} // hm_key_exists

void hm_remove(size_t id, const char * key, int32_t free_memory) {
	hash.remove(id, key, free_memory);
	hm_result = hash.result();
} // hm_remove

void hm_remove_table(size_t id, int32_t free_memory) {
	hash.remove_table(id, free_memory);
	hm_result = hash.result();
} // hm_remove_table

void hm_clear(int32_t free_memory) {
	hash.clear(free_memory);
	hm_result = hash.result();
} // hm_clear

void hm_set_property(uint32_t property) {
	hash.set_property(property);
	hm_result = hash.result();
} // hm_set_property

void hm_unset_property(uint32_t property) {
	hash.unset_property(property);
	hm_result = hash.result();
} // hm_unset_property

const char * hm_error_string(int32_t code) {
	const char * _tmp = hash.error_string(code);
	hm_result = hash.result();
	return _tmp;
} // hm_error_string
