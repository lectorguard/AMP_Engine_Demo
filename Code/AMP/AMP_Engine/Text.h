// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once

#include "functional"
#include "string"



struct TEXT
{
private:
	std::string txt;
	size_t hash = 0;
public:
	TEXT(std::string AssetPath):txt(AssetPath) {
		std::hash<std::string> hash_fn;
		hash = hash_fn(AssetPath);
	}
	TEXT() {};

	const char* getCharArray() {
		return txt.c_str();
	}

	std::string getString() {
		return txt;
	}

	size_t getHash() {
		return hash;
	}

	size_t getTextLength() {
		return txt.size();
	}

	bool operator==(TEXT &rhs) {
		return this->hash == rhs.hash;
	}

	bool operator>(TEXT& rhs) {
		return this->hash > rhs.hash;
	}

	char operator[](int element) {
		return this->txt[element];
	}

};
