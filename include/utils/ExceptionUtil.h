//
// Created by wing on 17/03/12.
//

#pragma once

#include <iostream>
#include <string>

#define EXC_BUFFER_SIZE 100

extern char regexErrorNames[][20];

/// Return an exception of type T with a formatted message
template<typename T, typename... Args>
T exceptf(const std::string &format, Args... args);

#include "ExceptionUtil.tpp"
