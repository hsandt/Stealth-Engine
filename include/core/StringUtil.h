//
// Created by wing on 17/03/12.
//

#pragma once

#include <iosfwd>

#define BUFFER_SIZE 300

#define STR(value) #value

/// Stream a formatted string with undefined number of parameters
template<typename... Args>
void streamf(std::ostream & os, const std::string& format, Args... args);

#include "StringUtil.tpp"
