/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:49:47 by vfiszbin          #+#    #+#             */
/*   Updated: 2023/01/11 16:28:05 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>

namespace ft
{
	///-----------------///
	/// ITERATOR TRAITS ///
	///-----------------///

	//Traits classes defining properties of iterators.

	//Default definition that obtains these types from the iterator type itself
	template <class Iterator>
	class iterator_traits
	{
		public:
			typedef typename Iterator::difference_type difference_type;
			typedef typename Iterator::value_type value_type;
			typedef typename Iterator::pointer pointer;
			typedef typename Iterator::reference reference;
			typedef typename Iterator::iterator_category iterator_category;
	};

	class random_access_iterator_tag { }; //empty class to identify this type of iterator
	
	//Specialization for pointers
	template <class T>
	class iterator_traits<T*>
	{
		public:
			typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef T* pointer;
			typedef T& reference;
			typedef ft::random_access_iterator_tag iterator_category;
	};
	
	//Specialization for const pointers
	template <class T>
	class iterator_traits<const T*>
	{
		public:
			typedef std::ptrdiff_t difference_type;
			typedef T value_type;
			typedef const T* pointer;
			typedef const T& reference;
			typedef ft::random_access_iterator_tag iterator_category;
	};


	///-----------///
	/// ITERATORS ///
	///-----------///

	//Base class template that can be used to derive iterator classes from it
	template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
  	class iterator 
	{
		public:
			typedef T value_type;
			typedef Distance difference_type;
			typedef Pointer pointer;
			typedef Reference reference;
			typedef Category iterator_category;
  };

  
	
	/// RANDOM ACCESS ITERATOR ///

	//Random-access iterators are iterators that can be used to access elements at an arbitrary offset position relative to the element they point to,
	//offering the same functionality as pointers.
	template<typename T>
	class random_access_iterator : iterator<ft::random_access_iterator_tag, T>
	{
		public:
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type value_type;
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type difference_type;
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer pointer;
                typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference reference;
                // typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
				typedef	std::random_access_iterator_tag iterator_category;

			///------------------///
			/// MEMBER FUNCTIONS ///
			///------------------///
			
			//Default constructor
			random_access_iterator() : _ptr(0) {}

			//Constructor from pointer
			random_access_iterator(pointer p) : _ptr(p) {}

			//Copy constructor
			random_access_iterator(const random_access_iterator& r) : _ptr(r._ptr) {}
			
			//Assignment operator overload
			random_access_iterator& operator=(const random_access_iterator& r)
            {
				if (this == &r)
					return *this;

				_ptr = r._ptr;
				return *this;
            }

			//Destructor
			virtual ~random_access_iterator() {}

			///------------///
			/// OPERATIONS ///
			///------------///
			
			//Dereference, return rvalue (non assignable) pointed to by pointer
			reference operator*() const
			{
				return *_ptr;
			}

			//Return lvalue (assignable) to pointer 
			reference operator->() const
			{
				return _ptr;
			}

			//Prefix increment
			random_access_iterator& operator++()
            {
                    _ptr++;
                    return *this;
            }

			//Postfix increment
			//Takes int argument to differentiate pre and postfix
			//Increments pointer but return non-incremented copy of the instance
			random_access_iterator operator++(int)
			{
				random_access_iterator cpy(*this);
				_ptr++;
				return cpy;
			}

			//Prefix decrement
			random_access_iterator& operator--()
            {
                    _ptr--;
                    return *this;
            }

			//Postfix decrement
			//Takes int argument to differentiate pre and postfix
			//Decrements pointer but return non-decremented copy of the instance
			random_access_iterator operator--(int)
			{
				random_access_iterator cpy(*this);
				_ptr--;
				return cpy;
			}

			//Arithmetic + operator with an integer value
			random_access_iterator operator+(const difference_type n) const
			{
				return _ptr + n;
			}

			//Arithmetic - operator with an integer value
			random_access_iterator operator-(const difference_type n) const
			{
				return _ptr - n;
			}

			//Compound assignment operator +=
			random_access_iterator& operator+=(const difference_type n)
			{
				_ptr += n;
				return *this;
			}

			//Compound assignment operator -=
			random_access_iterator& operator-=(const difference_type n)
			{
				_ptr -= n;
				return *this;
			}

			//Offset dereference operator
			reference operator[](const difference_type n)
			{
				return *(_ptr + n);
			}

			//Convert to constant iterator
			operator random_access_iterator<const T> () const
                { return (random_access_iterator<const T>(_ptr)); }
			
		private:
			pointer _ptr; //the pointer around which the iterator (wrapper) is built
		
	};

	///----------------------///
	/// RELATIONAL OPERATORS ///
	///----------------------///

	//Equality operator
	template <typename L, typename R>
    bool operator==(const random_access_iterator<L> lhs, const random_access_iterator<R> rhs)
    {
        return &(*lhs) == &(*rhs); //&(*lhs) get the underlying pointer of iterator lhs
    }

	//Inequality operator
	template <typename L, typename R>
    bool operator!=(const random_access_iterator<L> lhs, const random_access_iterator<R> rhs)
    {
        return &(*lhs) != &(*rhs); //&(*lhs) get the underlying pointer of iterator lhs
    }

	//Arithmetic operator + with an integer but the other way around
	template <typename T>
    random_access_iterator<T> operator+(const typename random_access_iterator<T>::difference_type n, const random_access_iterator<T> rhs)
    {
        return rhs + n;
    }

	//Arithmetic operator - with an integer but the other way around
	template <typename T>
    random_access_iterator<T> operator-(const typename random_access_iterator<T>::difference_type n, const random_access_iterator<T> rhs)
    {
        return rhs - n;
    }

	//Arithmetic operator + with another iterator
	template <typename L, typename R>
    typename random_access_iterator<L>::difference_type operator+(const random_access_iterator<L> lhs, const random_access_iterator<R> rhs)
    {
        return &(*lhs) + &(*rhs); //&(*lhs) get the underlying pointer of iterator lhs
    }

	//Arithmetic operator - with another iterator
	template <typename L, typename R>
    typename random_access_iterator<L>::difference_type operator-(const random_access_iterator<L> lhs, const random_access_iterator<R> rhs)
    {
        return &(*lhs) - &(*rhs); //&(*lhs) get the underlying pointer of iterator lhs
    }

	//Relational operator <
	template <typename L, typename R>
    bool operator<(const random_access_iterator<L> lhs, const random_access_iterator<R> rhs)
    {
        return &(*lhs) < &(*rhs); //&(*lhs) get the underlying pointer of iterator lhs
    }

	//Relational operator >
	template <typename L, typename R>
    bool operator>(const random_access_iterator<L> lhs, const random_access_iterator<R> rhs)
    {
        return &(*lhs) > &(*rhs); //&(*lhs) get the underlying pointer of iterator lhs
    }

	//Relational operator <=
	template <typename L, typename R>
    bool operator<=(const random_access_iterator<L> lhs, const random_access_iterator<R> rhs)
    {
        return &(*lhs) <= &(*rhs); //&(*lhs) get the underlying pointer of iterator lhs
    }

	//Relational operator >=
	template <typename L, typename R>
    bool operator>=(const random_access_iterator<L> lhs, const random_access_iterator<R> rhs)
    {
        return &(*lhs) >= &(*rhs); //&(*lhs) get the underlying pointer of iterator lhs
    }
	

}

#endif