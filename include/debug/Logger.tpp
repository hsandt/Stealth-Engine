//
// Created by wing on 17/02/23.
//

//#include "debug/Logger.h"

#include <iostream>
#include <string>
#include <tuple>

#include "utils/TraitsUtil.h"

using namespace std;

template<typename... Args>
inline void Logger::log(const Args&... args)
{
	log(standardOS, args...);
}

template<typename... Args>
inline void Logger::logwarn(const Args&... args)
{
	log(warningOS, args...);
}

template<typename... Args>
inline void Logger::logerr(const Args&... args)
{
	log(errorOS, args...);
}

template<typename... Args>
inline void Logger::log(ostream & os, const Args&... args)
{
	streamArgs(os, args...);
	os << endl;
}

template<typename FirstArg, typename... Args>
void Logger::streamArgs(std::ostream &os, const FirstArg& arg, const Args&... args)
{
	// We isolate the handling of the first argument since we need infix separators
	// Do not explicitly set the template type to <FirstArg>, so that either an explicit non-template overload
	// or a template overload (via template type deduction) can be called (e.g. if we add non-template string overload)
	// Even template overloads are not called correctly if it is omitted
	stream<FirstArg>(os, arg);

	// print the rest of the arguments using C comma sequences
	// see http://stackoverflow.com/questions/27375089/what-is-the-easiest-way-to-print-a-variadic-parameter-pack-using-stdostream
	// explicit template type is required to call the specific overload
	(void)(int[]){(os << " ", stream<decltype(args)>(os, args), 0)...};
}

template<class T>
inline void Logger::stream(std::ostream& os, const T& value)
{
	os << value;
}

template<class T>
void Logger::stream(std::ostream& os, const std::enable_if_t<is_container<T>::value, T>& value)
{
	os << "(";
	infix_ostream_iterator<decltype(*value.cbegin())> _outIt(infix_ostream_iterator<decltype(*value.cbegin())>(os, ", "));
	std::copy(value.begin(), value.end(), _outIt);
	os << ")";
}

template<typename... Args>
inline void Logger::logf(const std::string &format, Args... args)
{
	streamf(standardOS, format, args...);
}

template<typename... Args>
inline void Logger::logwarnf(const std::string &format, Args... args)
{
	streamf(warningOS, format, args...);
}

template<typename... Args>
inline void Logger::logerrf(const std::string &format, Args... args)
{
	streamf(errorOS, format, args...);
}

template<typename... Args>
void Logger::streamf(std::ostream &os, const std::string &format, Args... args)
{
	int n = snprintf(buf, sizeof(buf), format.c_str(), args...);
	os << buf << std::endl;  // operator<< supports C-style string
	if (n >= BUFFER_SIZE) {
		os << "(" << n - BUFFER_SIZE + 1 << " characters missing)";
	}
}

// Map streaming
//template<class T>
//void operator<<(std::ostream & flux, const std::map<int, std::string>& dict)
//{
//	infix_ostream_iterator<std::string> _outIt(infix_ostream_iterator<std::string>(_os, ", "));
//	std::transform(dict.begin(), dict.end(), _outIt, std::to_string(aPair.first) + ": " + aPair.second );
//}
