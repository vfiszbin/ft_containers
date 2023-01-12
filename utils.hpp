/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:18:25 by vfiszbin          #+#    #+#             */
/*   Updated: 2023/01/12 10:45:38 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
	/// ENABLE_IF ///
	//If Cond is true, enable_if has a public member typedef type, equal to T; otherwise, there is no member typedef.
	//In the latter case, a specialization whose arguments depends on enable_if would be discarded from the overload set
	//instead of causing a compile error, this is the SFINAE (Substitution Failure Is Not An Error) principle.
	template<bool Cond, class T = void>
	struct enable_if {};
	
	template<class T>
	struct enable_if<true, T> { typedef T type; };

	/// IS_INTEGRAL ///
	
	template <class T, T v>
	struct integral_constant 
	{
		static const bool value = v;
		typedef T value_type;
	};

	//Default template of is_integral is "false"
	template <typename>
	struct is_integral : public ft::integral_constant<bool, false> {}; //is_integral inherits from integral_constant

	//If the given type is included in the list of known integral types, it is "true"
	template <>
	struct is_integral<bool> : public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<char> : public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<char16_t> : public ft::integral_constant<bool, true> {};
	
	template <>
	struct is_integral<char32_t> : public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<wchar_t>	: public ft::integral_constant<bool, true> {};
	
	template <>
	struct is_integral<signed char> : public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<short> : public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<int> : public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<long> : public ft::integral_constant<bool, true> {};

	template <>
	struct is_integral<long long> : public ft::integral_constant<bool, true> {};
	
	template <>
	struct is_integral<unsigned char> : public ft::integral_constant<bool, true> {};
	
	template <>
	struct is_integral<unsigned short> : public ft::integral_constant<bool, true> {};
	
	template <>
	struct is_integral<unsigned int> : public ft::integral_constant<bool, true> {};
	
	template <>
	struct is_integral<unsigned long> : public ft::integral_constant<bool, true> {};
	
	template <>
	struct is_integral<unsigned long long> : public ft::integral_constant<bool, true> {};
	
}

#endif