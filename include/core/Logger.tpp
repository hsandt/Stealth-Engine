//
// Created by wing on 17/02/23.
//
#include "Logger.h"

#include <iostream>
#include <string>
#include <tuple>

#include "Stream.h"
#include "StringUtil.h"

using namespace std;

template<typename... Args>
inline void Logger::log(const Args&... args)
{
	streamArgs(standardOS, args...);
	standardOS << endl;
}

template<typename... Args>
inline void Logger::logwarn(const Args&... args)
{
	streamArgs(warningOS, args...);
	warningOS << endl;
}

template<typename... Args>
inline void Logger::logerr(const Args&... args)
{
	streamArgs(errorOS, args...);
	errorOS << endl;
}

template<typename... Args>
inline void Logger::logf(const std::string &format, Args... args)
{
	streamf(standardOS, format, args...);
	standardOS << endl;
}

template<typename... Args>
inline void Logger::logwarnf(const std::string &format, Args... args)
{
	streamf(warningOS, format, args...);
	warningOS << endl;
}

template<typename... Args>
inline void Logger::logerrf(const std::string &format, Args... args)
{
	streamf(errorOS, format, args...);
	errorOS << endl;
}
