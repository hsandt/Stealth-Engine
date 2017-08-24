//
// Created by wing on 17/03/12.
//

#pragma once

#include <iostream>
#include <string>

#include "utils/StringUtil.h"

extern char regexErrorNames[][20];

template<class T, typename... Args>
T exceptf(const std::string &format, Args... args)
{
	// warning: format string is not a string literal (potentially insecure)
	// -> well, not much choice about it
	int n = snprintf(buf, sizeof(buf), format.c_str(), args...);
	return T(buf);
//	return T{std::string(buf)};
}