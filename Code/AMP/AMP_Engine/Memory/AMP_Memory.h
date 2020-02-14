// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once

#include <stdexcept>
#include <array>

/** Array-like fixed-size container that only allows adding elements.
 *
 */
template<typename T, size_t Size>
struct LinearArray {
	LinearArray() { };
	virtual ~LinearArray() {};

	LinearArray(const LinearArray&) = delete;
	LinearArray(LinearArray&&) = delete;

	// Actual number of explicitly added elements
	size_t count() const {
		return _count;
	}

	void clear(){
		for (int i = 0; i < count(); i++) {
			data[i].reset();
		}
		_count = 0;
	}

	// Maximum number of elements
	size_t capacity() const {
		return data.size();
	}

	// Range-checked move-insert at end
	void add(T&& value) {
		if (!(_count < capacity()))
			throw std::out_of_range("Access out of range.");

		data[_count] = std::move(value);
		_count++;
	}

	// Range-checked copy-insert at end
	void add(const T& value) {
		if (!(_count < capacity()))
			throw std::out_of_range("Access out of range.");

		data[_count] = value;
		_count++;
	}

	// Range-checked
	constexpr T& at(size_t pos) {
		if (!pos < count())
			throw std::out_of_range("Access out of range.");
		return data[pos];
	}

	// Not range-checked, no modification
	constexpr const T& operator[](size_t pos) const {
		return data[pos];
	};
	
private:
	std::array<T, Size> data;
	size_t _count = 0;
};

