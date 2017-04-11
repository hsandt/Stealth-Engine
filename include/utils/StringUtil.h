//
// Created by wing on 17/03/12.
//

#pragma once

#include <iosfwd>

#define BUFFER_SIZE 100

/// Stream a formatted string with undefined number of parameters
template<typename... Args>
void streamf(std::ostream & os, const std::string& format, Args... args);

#include "StringUtil.tpp"
