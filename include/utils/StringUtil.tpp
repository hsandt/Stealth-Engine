//
// Created by wing on 17/03/12.
//

#pragma once

#include <iostream>

#include "utils/StringUtil.h"

namespace {
	/// Buffer for formatting string
	char buf[BUFFER_SIZE] = {};
}

template<typename... Args>
void streamf(std::ostream &os, const std::string &format, Args... args)
{
	// warning: format string is not a string literal (potentially insecure)
	// -> well, not much choice about it
	int n = snprintf(buf, sizeof(buf), format.c_str(), args...);
	os << buf;  // operator<< supports C-style string
	if (n >= BUFFER_SIZE) {
		os << " (" << n - BUFFER_SIZE + 1 << " characters missing)";
	}
}