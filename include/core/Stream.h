//
// Created by wing on 17/03/12.
//

#pragma once

#include <iosfwd>
#include <type_traits>

#include "utils/TraitsUtil.h"

/// Stream an undetermined number of parameters with the appropriate string formatting
template<typename FirstArg, typename... Args>
void streamArgs(std::ostream & os, const FirstArg& arg, const Args&... args);

/// Most generic overload for streaming
template<class T>
typename std::enable_if_t<std::is_fundamental<T>::value>
stream(std::ostream& os, const T& value);

/// Iterable container overload for streaming
// http://eli.thegreenplace.net/2014/sfinae-and-enable_if/
template<class T>
typename std::enable_if_t<is_container<T>::value>
stream(std::ostream& os, const T& value);

// non-template functions should be either inlined or in a non-included sourced .cpp

inline void stream(std::ostream& os, const char* value)
{
	os << value;
}

inline void stream(std::ostream& os, const std::string& value)
{
	os << value;
}

#include "Stream.tpp"