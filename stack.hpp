/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 09:28:40 by vfiszbin          #+#    #+#             */
/*   Updated: 2023/01/17 15:40:53 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template < class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			/// Member types ///
			typedef T value_type;
			typedef Container container_type;
			typedef std::size_t size_type;


			/// Member functions ///

			//Constructor
			explicit stack (const container_type& ctnr = container_type()) : c(ctnr) {}
			//explicit keyword prevents implicit call to the constructor

			//Copy constructor
			stack(const stack& s): c(s.c) {}

			//Assignment operator
			stack& operator=(const stack & s)
			{
				c = s.c;
				return (*this);
			}

			//Destructor
			~stack() {}

			//Test whether container is empty
			bool empty() const
			{
				return c.empty();
			}

			//Return size
			size_type size() const
			{
				return c.size();
			}

			//Access next element
			value_type& top()
			{
				return (c.back());
			}

			//Access next element
			const value_type& top() const
			{
				return (c.back());
			}

			//Insert element
			void push (const value_type& val)
			{
				c.push_back(val);
			}

			//Remove top element
			void pop()
			{
				c.pop_back();
			}

			//Declare relational operators functions as friends of the stack class
			//It is necessary because these functions must access the protected member c
			template < class T_rops, class Container_rops >
			friend bool operator== (const ft::stack<T_rops, Container_rops>& lhs, const ft::stack<T_rops, Container_rops>& rhs);

			template < class T_rops, class Container_rops >
			friend bool operator!= (const ft::stack<T_rops, Container_rops>& lhs, const ft::stack<T_rops, Container_rops>& rhs);
			
			template < class T_rops, class Container_rops >
			friend bool operator< (const ft::stack<T_rops, Container_rops>& lhs, const ft::stack<T_rops, Container_rops>& rhs);

			template < class T_rops, class Container_rops >
			friend bool operator<= (const ft::stack<T_rops, Container_rops>& lhs, const ft::stack<T_rops, Container_rops>& rhs);

			template < class T_rops, class Container_rops >
			friend bool operator> (const ft::stack<T_rops, Container_rops>& lhs, const ft::stack<T_rops, Container_rops>& rhs);

			template < class T_rops, class Container_rops >
			friend bool operator>= (const ft::stack<T_rops, Container_rops>& lhs, const ft::stack<T_rops, Container_rops>& rhs);

		protected:
			container_type c;

	};

	//Operator overload functions definitions
	//Performs the appropriate comparison operation between lhs and rhs
	template < class T, class Container >
	bool operator== (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs.c == rhs.c;
	}

	template < class T, class Container >
	bool operator!= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs.c != rhs.c;
	}

	template < class T, class Container >
	bool operator< (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs.c < rhs.c;
	}

	template < class T, class Container >
	bool operator<= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs.c <= rhs.c;
	}

	template < class T, class Container >
	bool operator> (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs.c > rhs.c;
	}

	template < class T, class Container >
	bool operator>= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs.c >= rhs.c;
	}

}


#endif