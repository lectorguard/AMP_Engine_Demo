// Copyright 2020 Simon Keller. All Rights Reserved.

#pragma once
#include "time.h"
#define NANOS_IN_SECOND 1000000000LL
#define BILLION_AS_DOUBLE 1000000000.0


namespace TIME
{
	static int64_t currentTimeInNanos() {
	
		struct timespec res;
		clock_gettime(CLOCK_MONOTONIC, &res);
		return (int64_t)res.tv_sec * NANOS_IN_SECOND + res.tv_nsec;
	}

	static long currentTimeInSec() {
		struct timespec res;
		clock_gettime(CLOCK_MONOTONIC, &res);
		return res.tv_sec;
	}

	static double NanosToSeconds(int64_t nanos) {
		return nanos / BILLION_AS_DOUBLE;
	}
}
