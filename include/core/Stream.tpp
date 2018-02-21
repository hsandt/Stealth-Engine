//
// Created by wing on 17/03/12.
//

#include <ostream>
#include <type_traits>
#include <algorithm>
#include <string>

#include "utils/infix_iterator.h"
#include "utils/TraitsUtil.h"

#include "Stream.h"

using namespace std;

template<typename FirstArg, typename... Args>
inline void streamArgs(std::ostream &os, const FirstArg& arg, const Args&... args)
{
	// We isolate the handling of the first argument since we need infix separators
	// Do not explicitly set the template type to <FirstArg>, so that either an explicit non-template overload
	// or a template overload (via template type deduction) can be called (e.g. if we add non-template string overload)
	// Even template overloads are not called correctly if it is omitted
	// However, string<FirstArg> is required to produce template definitions for vector, etc. if only is_container is used
	stream(os, arg);

	// print the rest of the arguments using C comma sequences
	// see http://stackoverflow.com/questions/27375089/what-is-the-easiest-way-to-print-a-variadic-parameter-pack-using-stdostream
	// explicit template type is required to call the specific overload
	// same here, use stream<decltype(args)>(os, args) if only is_container is used
	(void)(int[]){(os << " ", stream(os, args), 0)...};
}

template<class T>
typename std::enable_if_t<std::is_fundamental<T>::value>
inline stream(std::ostream& os, const T& value)
{
	os << value;
}

template<class T>
typename std::enable_if_t<is_container<T>::value>
stream(std::ostream& os, const T& value)
{
	os << "(";
	// C++17: use auto class template deduction for lighter syntax
	infix_ostream_iterator<decltype(*value.cbegin())> _outIt(infix_ostream_iterator<decltype(*value.cbegin())>(os, ", "));
	std::copy(value.begin(), value.end(), _outIt);
	os << ")";
}
