//
// Created by wing on 17/02/28.
//

#pragma once

// http://stackoverflow.com/questions/12042824/how-to-write-a-type-trait-is-container-or-is-vector
// Nevermore

#include <type_traits>

template<typename T, typename _ = void>
struct is_container_impl : std::false_type
{
};

template<typename... Ts>
struct is_container_helper
{
};

template<typename T>
struct is_container_impl<
	T,
	std::conditional_t<
		false,
		is_container_helper<
			typename T::value_type,
			typename T::size_type,
			typename T::allocator_type,
			typename T::iterator,
			typename T::const_iterator,
			decltype(std::declval<T>().size()),
			decltype(std::declval<T>().begin()),
			decltype(std::declval<T>().end()),
			decltype(std::declval<T>().cbegin()),
			decltype(std::declval<T>().cend())
		>,
		void
	>
> : public std::true_type {};

// type trait to utilize the implementation type traits as well as decay the type
// if it works, suggest the improvement to stackoverflow
template <typename T>
struct is_container
	: std::conditional_t<is_container_impl<std::decay_t<T>>::value,
		std::true_type, std::false_type> {};
