//
// Created by wing on 17/03/12.
//

#pragma once

#include <iostream>

#include "utils/StringUtil.h"

// CAUTION: despite being an anonymous namespace,
// since the tpp is included, buf is not hidden.
// To really hide it, you'd need to move this to a cpp
// and add a getter function getBuf. However,
// since we are also using buf in ExceptionUtils,
// for now we keep it so, and can even remove namespace.
// Later, maybe move shared variables to a 3rd script with all of them.
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