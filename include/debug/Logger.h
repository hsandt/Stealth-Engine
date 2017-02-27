//
//  Logger.h
//  From Cpp11_Training
//
//  Created by L Nguyen Huu on 18/02/29 H.
//  Copyright © 29 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

#include <iosfwd>
#include <type_traits>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <deque>
#include <map>

#include "utils/infix_iterator.h"
#include "utils/TraitsUtil.h"

// macro to log easily
#define LOG(...) if (Locator::getLogger() != nullptr) Locator::getLogger()->log(__VA_ARGS__);
#define LOGWARN(...) if (Locator::getLogger() != nullptr) Locator::getLogger()->logwarn(__VA_ARGS__);
#define LOGERR(...) if (Locator::getLogger() != nullptr) Locator::getLogger()->logerr(__VA_ARGS__);

#define LOGF(format, ...) if (Locator::getLogger() != nullptr) Locator::getLogger()->logf(format, __VA_ARGS__);
#define LOGWARNF(format, ...) if (Locator::getLogger() != nullptr) Locator::getLogger()->logwarnf(format, __VA_ARGS__);
#define LOGERRF(format, ...) if (Locator::getLogger() != nullptr) Locator::getLogger()->logerrf(format, __VA_ARGS__);

// macro to ease concatenation version
#define DUMP(variable) #variable ":", variable

#define BUFFER_SIZE 100

class Logger {
    
private:
	/// Output stream used to log the info (std::cout, file output stream...)
    std::ostream & standardOS;
    std::ostream & warningOS;
    std::ostream & errorOS;

    /// Buffer for formatting string
    char buf[BUFFER_SIZE] = {};
    
public:
	// Non-template methods should be inlined or defined
	// a .cpp (not .tpp), an actual source file that includes
	// this header but is not included by this header
    Logger(std::ostream & standardOS, std::ostream & warningOS, std::ostream & errorOS)
	    : standardOS(standardOS), warningOS(warningOS), errorOS(errorOS)
	{}

	/// Log an undetermined number of parameters to the standard output stream
    template<typename... Args>
    void log(const Args&... args);

	/// Log an undetermined number of parameters to the warning output stream
	template<typename... Args>
    void logwarn(const Args&... args);

	/// Log an undetermined number of parameters to the error output stream
	template<typename... Args>
    void logerr(const Args&... args);

private:
	/// Log an undetermined number of parameters to given output stream
	template<typename... Args>
	void log(std::ostream & os, const Args&... args);

	/// Stream an undetermined number of parameters with the appropriate string formatting
	template<typename FirstArg, typename... Args>
	void streamArgs(std::ostream & os, const FirstArg& arg, const Args&... args);

	/// Most generic overload for streaming
	template<class T>
	void stream(std::ostream& os, const T& value);
//	void stream(std::ostream& os, const std::enable_if_t<!is_container<T>::value, T>& value);

	/// Iterable container overload for streaming
	// http://eli.thegreenplace.net/2014/sfinae-and-enable_if/
	// add more container types as needed
	template<class T>
	void stream(std::ostream& os, const std::enable_if_t<is_container<T>::value, T>& value);

public:
	/// Log a formatted string with undefined number of parameters to the standard output stream
	template<typename... Args>
    void logf(const std::string &format, Args... args);

	/// Log a formatted string with undefined number of parameters to the warning output stream
	template<typename... Args>
    void logwarnf(const std::string &format, Args... args);

	/// Log a formatted string with undefined number of parameters to the error output stream
	template<typename... Args>
    void logerrf(const std::string &format, Args... args);

private:
    /// Stream a formatted string with undefined number of parameters
    template<typename... Args>
    void streamf(std::ostream & os, const std::string& format, Args... args);
};

/// Map streaming operator override
//template<class T, class U>
//void operator<<(std::ostream & flux, const std::map<T, U>& dict);

#include "debug/Logger.tpp"