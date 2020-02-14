// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once

struct Attributes
{
	Attributes(bool isUsedAtRuntime = false):isUsedAtRuntime(isUsedAtRuntime) {};
	virtual ~Attributes() {};

	Attributes(Attributes&&) = delete;
	Attributes(const Attributes&) = delete;

	bool isUsedAtRuntime = false;
};
