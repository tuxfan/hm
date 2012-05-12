/*----------------------------------------------------------------------------*
 * HashMark C++ hash class.
 *----------------------------------------------------------------------------*/

#ifndef hash_hxx
#define hash_hxx

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cstdint>
#include <cstddef>
#include <cstdlib>

/*----------------------------------------------------------------------------*
 * Utilities
 *----------------------------------------------------------------------------*/

#define ASSERT(v, s)							\
	if(!(v)) {									\
		std::cerr << (s) << std::endl;	\
		std::exit(1);							\
	}

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
	typedef std::vector<hash_t> hash_vector_t;

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
		size_t tables = data_.size();
		data_.resize(tables+1);
		return tables;
	} // add_table

	/*-------------------------------------------------------------------------*
	 * Add an entry to a hash table.
	 *-------------------------------------------------------------------------*/

	void add(hash_token_t token, key_t key, value_t value) {
		// check for valid token
		ASSERT(token < data_.size(), "Invalid hash token!!!");

		// set value
		(data_[token])[key] = value;
	} // add

	/*-------------------------------------------------------------------------*
	 * Find an entry in a hash table.
	 *-------------------------------------------------------------------------*/

	value_t find(hash_token_t token, key_t key) {
		// check for valid token
		ASSERT(token < data_.size(), "Invalid hash token!!!");

		hash_t _map = data_[token];

		// check for valid key
		ASSERT(_map.find(key) != _map.end(), "Invalid hash key!!!");

		return _map[key];
	} // find

	/*-------------------------------------------------------------------------*
	 * Remove an entry from a hash table.
	 *-------------------------------------------------------------------------*/

	int32_t remove(hash_token_t token, key_t key, int32_t free_memory) {
		// check for valid token
		ASSERT(token < data_.size(), "Invalid hash token!!!");

		hash_t _map = data_[token];

		// check for valid key
		ASSERT(_map.find(key) != _map.end(), "Invalid hash key!!!");

		value_t _value = _map[key];

		// free data if requested
		if(free_memory == 1) {
			free(_value);
		} // if

		for(auto ita = _map.begin(); ita != _map.end(); ++ita) {
			if(_value == ita->second) {
				_map.erase(ita);
				break;
			} // if
		} // for
	} // remove

	/*-------------------------------------------------------------------------*
	 * Remove a hash table.
	 *-------------------------------------------------------------------------*/

	int32_t remove_table(hash_token_t token, int32_t free_memory) {
		// check for valid token
		ASSERT(token < data_.size(), "Invalid hash token!!!");

		hash_t _map = data_[token];

		if(free_memory == 1) {
			for(auto ita = _map.begin(); ita != _map.end(); ++ita) {
				free(ita->second);
			} // for
		} // if

		for(auto ita = data_.begin(); ita != data_.end(); ++ita) {
			if(_map == *ita) {
				data_.erase(ita);
				break;
			} // if
		} // for
	} // remove_table

private:

	/*-------------------------------------------------------------------------*
	 * Hidden for safety.
	 *-------------------------------------------------------------------------*/

	hm_hash() {}
	hm_hash(const hm_hash &) {}
	~hm_hash() {}
	hm_hash & operator = (const hm_hash &);

	/*-------------------------------------------------------------------------*
	 * Aggregate data members.
	 *-------------------------------------------------------------------------*/

	hash_vector_t data_;

}; // class hm_hash

#endif // hash_hxx
