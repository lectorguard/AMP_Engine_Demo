// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once
#include "map"
#include "optional"


template<typename KEY,typename VALUE>
struct HashMap {
	using data_t = typename std::map <KEY,VALUE>;
	typedef typename std::remove_reference<decltype(*std::declval<VALUE>())>::type T;

	HashMap() { };
	virtual ~HashMap() {};

	HashMap(const HashMap&) = delete;
	HashMap(HashMap&&) = delete;

	std::optional<VALUE> tryFind(const KEY& key){
		auto found = data.find(key);
		if(found!=data.end()){
			return {found->second};
		}
		return std::nullopt;
	}

	std::optional<T*> tryFind_unique(const KEY& key) {
		auto found = data.find(key);
		if (found != data.end()) {
			return found->second.get();
		}
		return std::nullopt;
	}



	void add(const KEY& key,VALUE&& value){
		data.insert(std::pair<KEY,VALUE>(key,value));
	}

	void add_unique(const KEY& key, VALUE&& value) {
		data.insert(std::make_pair(key, std::move(value)));
	}

	void clear(){
		data.clear();
	}

	void erase(typename data_t::iterator iter) {
		data.erase(iter);
	}

	size_t count(){
		return data.size();
	}

	//
	// Iterators for Range-based for loops, e.g. for(auto & s : systems) { }
	//
	constexpr typename data_t::const_iterator cbegin() const noexcept {
		return data.cbegin();
	}

	constexpr typename data_t::const_iterator begin() const noexcept {
		return data.begin();
	}

	constexpr typename data_t::iterator begin() noexcept {
		return data.begin();
	}

	typename data_t::const_iterator cend() const noexcept {
		return data.cend();
	}

	typename data_t::const_iterator end() const noexcept {
		return data.end();
	}

	typename data_t::iterator end() noexcept {
		return data.end();
	}

private:
	std::map<KEY, VALUE> data;

};