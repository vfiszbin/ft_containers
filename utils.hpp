/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 09:18:25 by vfiszbin          #+#    #+#             */
/*   Updated: 2023/01/15 18:09:06 by vfiszbin         ###   ########.fr       */
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


	/// LEXICOGRAPHICAL_COMPARE ///

	//Default implementation
	//Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
	template <class InputIterator1, class InputIterator2>
  	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	//Custom implementation : the comparison operator used is the comp function instead of <
	//Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
	template <class InputIterator1, class InputIterator2, class Compare>
  	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1) )
				return false;
			else if ( comp(*first1, *first2) )
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	/// EQUAL ///

	//Equality implementation
	//Compares the elements in the range [first1,last1) with those in the range beginning at first2,
	//and returns true if all of the elements in both ranges match.
	template <class InputIterator1, class InputIterator2>
  	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1 != last1) 
		{
			if (!(*first1 == *first2)) 
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	//Predicate implementation : the elements are compared using the pred function instead of the == operator
	//Compares the elements in the range [first1,last1) with those in the range beginning at first2,
	//and returns true if all of the elements in both ranges match.
	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1) 
		{
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	/// PAIR ///

	template <class T1, class T2>
	struct pair
	{
		// MEMBER TYPES 

		// typedef typename std::remove_const<T1>::type first_type; //OK DE FAIRE CA ? !!!
		typedef T1 first_type;
		typedef T2 second_type;

		// MEMBER VARIABLES 
		//The individual values of the pair can be accessed through its public members first and second

		first_type first;
		second_type second;

		// MEMBER FUNCTIONS 

		//Default constructor
		pair() : first(), second() {}

		//Copy constructor
		template<class U, class V>
		pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}

		//Copy constructor
		pair(const pair & pr) : first(pr.first), second(pr.second) {}

		//Initialization constructor
		pair (const first_type& a, const second_type& b) : first(a), second(b) {}

		//Assignment operator overload
		pair& operator= (const pair& pr)
		{
			if (*this == pr)
				return (*this);
			first = pr.first;
			second = pr.second;
			return *this;
		}
	};

	// RELATIONAL OPERATORS 
	template <class T1, class T2>
  	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ 
		return lhs.first == rhs.first && lhs.second == rhs.second; 
	}

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ 
		return !(lhs == rhs); 
	}

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ 
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); 
	}

	template <class T1, class T2>
	bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ 
		return !(rhs < lhs); 
	}

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ 
		return rhs < lhs; 
	}

	template <class T1, class T2>
	bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ 
		return !(lhs < rhs); 
	}

	//Constructs a pair object with its first element set to x and its second element set to y.
	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		
		return pair<T1,T2>(x,y);
  	}

	//Choose template mechanism to choose between const and non-const version of a typedef
	template <bool flag, class IsTrue, class IsFalse>
	struct choose;

	template <class IsTrue, class IsFalse>
	struct choose<true, IsTrue, IsFalse> 
	{
		typedef IsTrue type;
	};

	template <class IsTrue, class IsFalse>
	struct choose<false, IsTrue, IsFalse> 
	{
		typedef IsFalse type;
	};
	
}

#endif