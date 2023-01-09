
# include <vector> //ENLEVER !

#ifndef VECTOR_HPP
# define VECTOR_HPP

namespace ft
{
	template < class T, class Container = std::vector<T> > //mon vector par DEFAUT !!!
	class stack
	{
		public:
			/// Member types ///
			typedef T value_type;
			typedef Container container_type;
			typedef std::size_t size_type;


			/// Member functions ///

			//Constructor
			explicit stack (const container_type& ctnr = container_type()) : _ctnr(ctnr) {}
			//explicit keyword prevents implicit call to the constructor

			//Copy constructor
			stack(const stack& s): _ctnr(s._ctnr) {}

			//Assignment operator
			stack& operator=(const stack & s)
			{
				_ctnr = s._ctnr;
				return (*this);
			}

			//Destructor
			~stack() {}

			//Test whether container is empty
			bool empty() const
			{
				return _ctnr.empty();
			}

			//Return size
			size_type size() const
			{
				return _ctnr.size();
			}

			//Access next element
			value_type& top()
			{
				return (_ctnr.back());
			}

			//Access next element
			const value_type& top() const
			{
				return (_ctnr.back());
			}

			//Insert element
			void push (const value_type& val)
			{
				_ctnr.push_back(val);
			}

			//Remove top element
			void pop()
			{
				_ctnr.pop_back();
			}

			//Declare relational operators functions as friends of the stack class
			//It is necessary because these functions must access the private member _ctnr
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

		private:
			container_type _ctnr;

	};

	//Operator overload functions definitions
	//Performs the appropriate comparison operation between lhs and rhs
	template < class T, class Container >
	bool operator== (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs._ctnr == rhs._ctnr;
	}

	template < class T, class Container >
	bool operator!= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs._ctnr != rhs._ctnr;
	}

	template < class T, class Container >
	bool operator< (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs._ctnr < rhs._ctnr;
	}

	template < class T, class Container >
	bool operator<= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs._ctnr <= rhs._ctnr;
	}

	template < class T, class Container >
	bool operator> (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs._ctnr > rhs._ctnr;
	}

	template < class T, class Container >
	bool operator>= (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs)
	{
		return lhs._ctnr >= rhs._ctnr;
	}

}


#endif