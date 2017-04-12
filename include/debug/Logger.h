//
//  Logger.h
//  From Cpp11_Training
//
//  Created by L Nguyen Huu on 18/02/29 H.
//  Copyright © 29 Heisei L Nguyen Huu. All rights reserved.
//

#pragma once

#include <iosfwd>

#include "core/EngineCore.h"

#define LOGGER_VALID (EngineCore::getInstance() != nullptr && EngineCore::getInstance()->getLogger() != nullptr)

// Use CMake standard macro for Release and MinSizeRel
#ifndef NDEBUG

	// Shortcut macros to log messages
	// Only call them from inside GameClass subclass objects
	#define LOG(...) if LOGGER_VALID EngineCore::getInstance()->getLogger()->log(__VA_ARGS__)
	#define LOGWARN(...) if LOGGER_VALID EngineCore::getInstance()->getLogger()->logwarn(__VA_ARGS__)

	// Format versions
	#define LOGF(format, ...) if LOGGER_VALID EngineCore::getInstance()->getLogger()->logf(format, ##__VA_ARGS__)
	#define LOGWARNF(format, ...) if LOGGER_VALID EngineCore::getInstance()->getLogger()->logwarnf(format, ##__VA_ARGS__)

#else

	#define LOG(...)
	#define LOGWARN(...)
	#define LOGERR(...)

	#define LOGF(format, ...)
	#define LOGWARNF(format, ...)
	#define LOGERRF(format, ...)

	#define DUMP(variable) ""

#endif

// Log errors even in Release. Maybe don't log them in RelMinSize build
#define LOGERR(...) if LOGGER_VALID EngineCore::getInstance()->getLogger()->logerr(__VA_ARGS__)
#define LOGERRF(format, ...) if LOGGER_VALID EngineCore::getInstance()->getLogger()->logerrf(format, ##__VA_ARGS__)

// Macro to ease concatenation version (required in Release build for LOGERR(F)
#define DUMP(variable) #variable ":", variable


class Logger {
    
private:
	/// Output stream used to log the info (std::cout, file output stream...)
    std::ostream & standardOS;
    std::ostream & warningOS;
    std::ostream & errorOS;
    
public:
	// Non-template methods should be inlined or defined
	// a .cpp (not .tpp), an actual source file that includes
	// this header but is not included by this header
    Logger(std::ostream & standardOS, std::ostream & warningOS, std::ostream & errorOS)
	    : standardOS(standardOS), warningOS(warningOS), errorOS(errorOS)
	{}

	virtual ~Logger()
	{
		log("[LOG] Logger destroyed");
	}

	/// Log an undetermined number of parameters to the standard output stream
    template<typename... Args>
    void log(const Args&... args);

	/// Log an undetermined number of parameters to the warning output stream
	template<typename... Args>
    void logwarn(const Args&... args);

	/// Log an undetermined number of parameters to the error output stream
	template<typename... Args>
    void logerr(const Args&... args);

	/// Log a formatted string with undefined number of parameters to the standard output stream
	template<typename... Args>
    void logf(const std::string &format, Args... args);

	/// Log a formatted string with undefined number of parameters to the warning output stream
	template<typename... Args>
    void logwarnf(const std::string &format, Args... args);

	/// Log a formatted string with undefined number of parameters to the error output stream
	template<typename... Args>
    void logerrf(const std::string &format, Args... args);

};

#include "debug/Logger.tpp"