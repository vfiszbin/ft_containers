/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:49:47 by vfiszbin          #+#    #+#             */
/*   Updated: 2023/01/15 18:22:08 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include "avl_tree.hpp"

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
	class bidirectional_iterator_tag{ }; //empty class to identify this type of iterator
	
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
			typedef	std::random_access_iterator_tag iterator_category; //besoin pour std::distance ! enlever ?

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
			pointer operator->() const
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
                { return random_access_iterator<const T>(_ptr); }
			
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


	/// REVERSE ITERATOR ///

	//Reverses the direction in which a bidirectional or random-access iterator iterates through a range.
	//A copy of the original iterator (the base iterator) is kept internally and used to reflect the operations performed on the reverse_iterator
	template<typename Iterator>
	class reverse_iterator
	{
		public:
			//Preserves Iterators's properties
			typedef typename iterator_traits<Iterator>::value_type value_type;
			typedef typename iterator_traits<Iterator>::difference_type difference_type;
			typedef typename iterator_traits<Iterator>::pointer pointer;
			typedef typename iterator_traits<Iterator>::reference reference;
			typedef	typename iterator_traits<Iterator>::iterator_category iterator_category;
			typedef Iterator iterator_type;

			///------------------///
			/// MEMBER FUNCTIONS ///
			///------------------///
			
			//Default constructor
			reverse_iterator() : _base_iterator() {} //base iterator initialised

			//Initialization constructor
			//Constructs a reverse iterator from some original iterator it.
			//The behavior of the constructed object replicates the original,
			//except that it iterates through its pointed elements in the reverse order.
			explicit reverse_iterator (iterator_type it) : _base_iterator(it) {}

			//Copy constructor
			//Constructs a reverse iterator from some other reverse iterator.
			//The constructed object keeps the same sense of iteration as rev_it.
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : _base_iterator(rev_it.base()) {}

			//Returns a copy of the base iterator.
			iterator_type base() const
			{
				return _base_iterator;
			}

			///------------///
			/// OPERATIONS ///
			///------------///
			
			//Dereference operator, returns a reference to the element pointed to by the iterator.
			reference operator*() const
			{
				iterator_type cpy = _base_iterator;
				//Decrements it, because the reversed version does not point to the same element in the range, but to the one preceding it.
				//This is so, in order to arrange for the past-the-end element of a range: An iterator pointing to a past-the-end element in a range, 
				//when reversed, is pointing to the last element (not past it) of the range (this would be the first element of the reversed range).
				//And if an iterator to the first element in a range is reversed, the reversed iterator points to the element before the first element 
				//(this would be the past-the-end element of the reversed range).
				return *(--cpy); 
			}

			//Returns a reverse iterator pointing to the element located n positions away from the element the iterator currently points to.
			reverse_iterator operator+ (difference_type n) const
			{
				return reverse_iterator(_base_iterator - n);
			}

			//Prefix increment
			reverse_iterator& operator++()
            {
                    _base_iterator--;
                    return *this;
            }

			//Postfix increment
			//Takes int argument to differentiate pre and postfix
			//Increments current instance but return non-incremented copy of the instance
			reverse_iterator  operator++(int)
			{
				reverse_iterator cpy = *this;
				++(*this);
				return cpy;
			}

			//Advances the reverse_iterator by n element positions.
			reverse_iterator& operator+= (difference_type n)
			{
				_base_iterator -= n;
				return *this;
			}

			//Returns a reverse iterator pointing to the element located n positions before the element the iterator currently points to.
			reverse_iterator operator- (difference_type n) const
			{
				return reverse_iterator(_base_iterator + n);
			}

			//Prefix decrement
			reverse_iterator& operator--()
            {
                    ++_base_iterator;
                    return *this;
            }

			//Postfix decrement
			//Takes int argument to differentiate pre and postfix
			//Decrements current instance but return non-decremented copy of the instance
			reverse_iterator  operator--(int)
			{
				reverse_iterator cpy = *this;
				--(*this);
				return cpy;
			}

			//Decreases the reverse_iterator by n element positions.
			reverse_iterator& operator-= (difference_type n)
			{
				_base_iterator += n;
				return *this;
			}

			//Returns a pointer to the element pointed to by the iterator
			pointer operator->() const
			{
				return &(operator*()); //calls operator* and return its address
			}

			//Accesses the element located n positions away from the element currently pointed to by the iterator.
			reference operator[] (difference_type n) const
			{
				return base()[-n-1];
			}
			
		private:
			iterator_type _base_iterator; //the base iterator which reflects the operations performed on the reverse_iterator: whenever the reverse_iterator is incremented, its base iterator is decreased, and vice versa.
		
	};
	
	///------------------------------///
	/// NON-MEMBER FUNCTION OVERLOADS///
	///------------------------------///

	/// RELATIONAL OPERATORS ///

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs,const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() == rhs.base();
	}
	//For comparison between const and non-const
	template <class L, class R>
	bool operator== (const reverse_iterator<L>& lhs, const reverse_iterator<R>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() != rhs.base();
	}
	//For comparison between const and non-const
	template <class L, class R>
	bool operator!= (const reverse_iterator<L>& lhs, const reverse_iterator<R>& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() > rhs.base();
	}
	//For comparison between const and non-const
	template <class L, class R>
	bool operator< (const reverse_iterator<L>& lhs, const reverse_iterator<R>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() >= rhs.base();
	}
	//For comparison between const and non-const
	template <class L, class R>
	bool operator<= (const reverse_iterator<L>& lhs, const reverse_iterator<R>& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() < rhs.base();
	}
	//For comparison between const and non-const
	template <class L, class R>
	bool operator> (const reverse_iterator<L>& lhs, const reverse_iterator<R>& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return lhs.base() <= rhs.base();
	}
	//For comparison between const and non-const
	template <class L, class R>
	bool operator>= (const reverse_iterator<L>& lhs, const reverse_iterator<R>& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	//operator+ the other way around
	//Returns a reverse iterator pointing to the element located n positions away from the element pointed to by rev_it.
	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return rev_it + n;
	}

	//Returns the distance between lhs and rhs.
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return rhs.base() - lhs.base();
	}
	//For comparison between const and non-const
	template <class L, class R>
	typename reverse_iterator<L>::difference_type operator- (const reverse_iterator<L>& lhs, const reverse_iterator<R>& rhs)
	{
		return rhs.base() - lhs.base();
	}


	/// AVL TREE ITERATOR ///
	
	template <typename T, bool is_const>
	class avl_tree_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef typename T::value_type value_type; //value inside the node
			typedef T* node_pointer; //pointer to the node
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type   difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
			
			//Choose template mechanism to choose between const and non-const version of a typedef
			// typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer pointer; //CHANGER ? !!!
			// typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;
			typedef typename choose<is_const, const value_type &, value_type &>::type reference;
			typedef typename choose<is_const, const value_type *, value_type *>::type pointer;

			///------------------///
			/// MEMBER FUNCTIONS ///
			///------------------///

			//Default constructor
			avl_tree_iterator(node_pointer p = 0, node_pointer dummy_past_end = 0) : _ptr(p), _dummy_past_end(dummy_past_end) {}

			//Copy constructor
			avl_tree_iterator(const avl_tree_iterator& r) : _ptr(r._ptr), _dummy_past_end(r._dummy_past_end) {}
			
			//Assignment operator overload
			avl_tree_iterator& operator=(const avl_tree_iterator& r)
            {
				if (this == &r)
					return *this;

				_ptr = r._ptr;
				_dummy_past_end = r._dummy_past_end;
				return *this;
            }
			
			//Destructor
			virtual ~avl_tree_iterator() {}
			
			//Dereference, return rvalue (non assignable) pointed to by pointer
			reference operator*() const
			{
				return _ptr->value;
			}

			//Return lvalue (assignable) to pointer 
			pointer operator->() const
			{
				return &(_ptr->value);
			}

			//Prefix increment
			//Find next in-order value in the tree
			avl_tree_iterator& operator++()
            {
				if (_ptr == _dummy_past_end->left)
					_ptr = _dummy_past_end;
                else if (_ptr->right)
					_ptr = minValueNode(_ptr->right);
				else
				{
					//Move up the tree until we reach a node whose parent's left child is not this node,
					//which means that we reached a node that had all of its left descendants visited but
					//none of its right descendants. It is therefore the in-order next node we were looking for.
					node_pointer p = _ptr->parent;
					while (p != NULL && _ptr == p->right)
					{
						_ptr = p;
						p = p->parent;
					}
					_ptr = p;
				}
                return *this;
            }

			//Postfix increment
			//Takes int argument to differentiate pre and postfix
			//Increments pointer but return non-incremented copy of the instance
			avl_tree_iterator operator++(int)
			{
				avl_tree_iterator cpy(*this);
				operator++();
				return cpy;
			}

			//Prefix decrement
			//Find previous in-order value in the tree
			avl_tree_iterator& operator--()
            {
                if (_ptr->left)
					_ptr = maxValueNode(_ptr->left);
				else
				{
					node_pointer p = _ptr->parent;
					while (p != NULL && _ptr == p->left)
					{
						_ptr = p;
						p = p->parent;
					}
					_ptr = p;
				}
                return *this;
            }

			//Postfix decrement
			//Takes int argument to differentiate pre and postfix
			//Decrements pointer but return non-decremented copy of the instance
			avl_tree_iterator operator--(int)
			{
				avl_tree_iterator cpy(*this);
				operator--();
				return cpy;
			}

			//Convert to constant iterator   UTILE ? !!!
			template<bool B>
			operator avl_tree_iterator<const T, B> () const
                { return avl_tree_iterator<const T, B>(_ptr, _dummy_past_end); }

		private:
			node_pointer _ptr;
			node_pointer _dummy_past_end;

			node_pointer minValueNode(node_pointer node) 
			{
				node_pointer current = node;
				//loop down to find the leftmost leaf
				while (current->left != NULL) 
				{
					current = current->left;
				}
				return current;
			}

			node_pointer maxValueNode(node_pointer node) 
			{
				node_pointer current = node;
				//loop down to find the rightmost leaf
				while (current->right != NULL) 
				{
					current = current->right;
				}
				return current;
			}
				
			
	};

	template<typename L, typename R, bool B_L, bool B_R>
	bool operator==(const avl_tree_iterator<L, B_L> & lhs, const avl_tree_iterator<R, B_R> & rhs)
	{
			return &(*lhs) == &(*rhs);
	}
	template<typename L, typename R, bool B_L, bool B_R>
	bool operator!=(const avl_tree_iterator<L, B_L> & lhs, const avl_tree_iterator<R, B_R> & rhs)
	{
			return &(*lhs) != &(*rhs);
	}
}

#endif