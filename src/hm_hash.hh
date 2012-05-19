/*----------------------------------------------------------------------------*
 * HashMark C++ hash class.
 *----------------------------------------------------------------------------*/

#ifndef hash_hxx
#define hash_hxx

#include <iostream>
#include <map>
#include <vector>
#include <mutex>
#include <string>
#include <cstdint>
#include <cstddef>
#include <cstdlib>

#define _include_hash_mark_h

#include <hm_flags.h>

/*----------------------------------------------------------------------------*
 * Utilities
 *----------------------------------------------------------------------------*/

#if defined(ENABLE_ASSERTIONS)
	#define ASSERT_AND_CODE(v, c)									\
		if(!(v)) {														\
			if(property_set(hm_exit_on_error)) {				\
				std::cerr << error_string((c)) << std::endl;	\
				std::exit(1);											\
			}																\
			else {														\
				result_ = c;											\
				return c;												\
			}																\
		} /* if */

	#define ASSERT_AND_NULL(v, c)									\
		if(!(v)) {														\
			if(property_set(hm_exit_on_error)) {				\
				std::cerr << error_string((c)) << std::endl;	\
				std::exit(1);											\
			}																\
			else {														\
				result_ = c;											\
				return NULL;											\
			}																\
		} /* if */
#else
	#define ASSERT_AND_CODE(v, c)
	#define ASSERT_AND_NULL(v, c)
#endif

/*----------------------------------------------------------------------------*
 * Simple hash class.
 *----------------------------------------------------------------------------*/

class hm_hash
{
public:

	/*-------------------------------------------------------------------------*
	 * Public types
	 *-------------------------------------------------------------------------*/

	typedef size_t hash_token_t;
	typedef std::string key_t;
	typedef void * value_t;
	typedef std::map<key_t, value_t> hash_t;
	typedef std::map<hash_token_t, hash_t> hash_map_t;

	/*-------------------------------------------------------------------------*
	 * Meyer's singlton instance.
	 *-------------------------------------------------------------------------*/

	static hm_hash & instance() {
		static hm_hash h;
		return h;
	} // instance

	/*-------------------------------------------------------------------------*
	 * Add a hash table.
	 *-------------------------------------------------------------------------*/

	hash_token_t add_table() {
		// acquire lock
		std::lock_guard<std::mutex> lock(m_);

		result_ = hm_success;

		// generate new token
		hash_token_t _token = token_++;

		// initialize table
		data_[_token]["Rush Rules!!!"] = NULL;

		return _token;
	} // add_table

	/*-------------------------------------------------------------------------*
	 * Add an entry to a hash table.
	 *-------------------------------------------------------------------------*/

	int32_t add(hash_token_t token, key_t key, value_t value) {
		// acquire lock
		std::lock_guard<std::mutex> lock(m_);

		result_ = hm_success;

		// check for valid token
		ASSERT_AND_CODE(data_.find(token) != data_.end(),
			hm_invalid_hash_token);
		ASSERT_AND_CODE(data_[token].find(key) == data_[token].end(),
			hm_hash_key_exists);

		// set value
		(data_[token])[key] = value;
	} // add

	/*-------------------------------------------------------------------------*
	 * Find an entry in a hash table.
	 *-------------------------------------------------------------------------*/

	value_t find(hash_token_t token, key_t key) {
		// acquire lock
		std::lock_guard<std::mutex> lock(m_);

		result_ = hm_success;

		// check for valid token
		ASSERT_AND_NULL(data_.find(token) != data_.end(),
			hm_invalid_hash_token);

		hash_t & _map = data_[token];

		// check for valid key
		ASSERT_AND_NULL(_map.find(key) != _map.end(), hm_invalid_hash_key);

		return _map[key];
	} // find

	/*-------------------------------------------------------------------------*
	 * Check to see if a hash table exists.
	 *-------------------------------------------------------------------------*/

	int32_t table_exists(hash_token_t token) {
		return data_.find(token) == data_.end() ? 0 : 1;
	} // table_exists

	/*-------------------------------------------------------------------------*
	 * Check if an entry exists in a hash table.
	 *-------------------------------------------------------------------------*/

	int32_t key_exists(hash_token_t token, key_t key) {
		// check for valid token
		ASSERT_AND_CODE(data_.find(token) != data_.end(),
			hm_invalid_hash_token);

		hash_t & _map = data_[token];

		return _map.find(key) == _map.end() ? 0 : 1;
	} // key_exists

	/*-------------------------------------------------------------------------*
	 * Remove an entry from a hash table.
	 *-------------------------------------------------------------------------*/

	int32_t remove(hash_token_t token, key_t key, int32_t free_memory) {
		// acquire lock
		std::lock_guard<std::mutex> lock(m_);

		result_ = hm_success;

		// check for valid token
		ASSERT_AND_CODE(data_.find(token) != data_.end(),
			hm_invalid_hash_token);

		hash_t & _map = data_[token];

		// check for valid key
		ASSERT_AND_CODE(_map.find(key) != _map.end(), hm_invalid_hash_key);

		value_t _value = _map[key];

		// free data if requested
		if(free_memory == 1) {
			free(_value);
		} // if

		_map.erase(key);
	} // remove

	/*-------------------------------------------------------------------------*
	 * Remove a hash table.
	 *-------------------------------------------------------------------------*/

	int32_t remove_table(hash_token_t token, int32_t free_memory) {
		// acquire lock
		std::lock_guard<std::mutex> lock(m_);

		result_ = hm_success;

		// check for valid token
		ASSERT_AND_CODE(data_.find(token) != data_.end(),
			hm_invalid_hash_token);

		hash_t & _map = data_[token];

		if(free_memory == 1) {
			for(auto ita = _map.begin(); ita != _map.end(); ++ita) {
				free(ita->second);
			} // for
		} // if

		data_.erase(token);
	} // remove_table

	/*-------------------------------------------------------------------------*
	 * Remove everything from hash.
	 *-------------------------------------------------------------------------*/

	int32_t clear(int32_t free_memory) {
		// acquire lock
		std::lock_guard<std::mutex> lock(m_);

		if(property_set(hm_free_data)) {
			for(auto t = data_.begin(); t != data_.end(); ++t) {
				hash_t _h = t->second;

				for(auto st = _h.begin(); st != _h.end(); ++st) {
					free(st->second);
				} // for

			} // for
		} // if

		data_.clear();
	} // clear

	/*-------------------------------------------------------------------------*
	 * Set hash properties.
	 *-------------------------------------------------------------------------*/

	uint32_t set_property(uint32_t property) {
		// acquire lock
		std::lock_guard<std::mutex> lock(m_);

		result_ = hm_success;

		properties_ |= property;
		return properties_;
	} // hm_set_property

	/*-------------------------------------------------------------------------*
	 * Unset hash properties.
	 *-------------------------------------------------------------------------*/

	uint32_t unset_property(uint32_t property) {
		// acquire lock
		std::lock_guard<std::mutex> lock(m_);

		result_ = hm_success;

		properties_ & ~property;
		return properties_;
	} // hm_set_property

	const char * error_string(int32_t code) {
		result_ = hm_success;
		return error_strings_[code == 0 ? code : -code];
	} // hm_error_string

	uint32_t result() {
		return result_;
	} // result

private:

	/*-------------------------------------------------------------------------*
	 * Private methods
	 *-------------------------------------------------------------------------*/

	bool property_set(uint32_t property) {
		return properties_ & property;
	} // property_set

	/*-------------------------------------------------------------------------*
	 * Hidden for safety.
	 *-------------------------------------------------------------------------*/

	hm_hash() : token_(0), properties_(0) {}
	hm_hash(const hm_hash &) {}
	hm_hash & operator = (const hm_hash &);

	~hm_hash() {
		clear(property_set(hm_free_data));
	} // ~hm_hash

	/*-------------------------------------------------------------------------*
	 * Aggregate data members.
	 *-------------------------------------------------------------------------*/

	size_t token_;
	hash_map_t data_;
	uint32_t properties_;
	int32_t result_;
	std::mutex m_;

	const char * error_strings_[4] = {
		"HashMark: Success",
		"HashMark Error: Invalid Hash Token!!!",
		"HashMark Error: Invalid Hash Key!!!",
		"HashMark Error: Hash Key Exists!!!"
	};

}; // class hm_hash

#endif // hash_hxx
