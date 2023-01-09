#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <vector> //RETIRER !!!


namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			///---------------///
			/// MEMBER TYPES ///
			///---------------///
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef typename std::vector<value_type>::iterator iterator; //Mettre mon propre iterator !
			typedef typename std::vector<value_type>::const_iterator const_iterator; //Mettre mon propre iterator !
			typedef typename std::vector<value_type>::reverse_iterator reverse_iterator; //Mettre mon propre iterator !
			typedef typename std::vector<value_type>::const_reverse_iterator const_reverse_iterator; //Mettre mon propre iterator !
			typedef std::ptrdiff_t difference_type; //can represent the number of element between two pointers
			typedef std::size_t size_type;

			///------------------///
			/// MEMBER FUNCTIONS ///
			///------------------///

			//Default constructor (empty container constructor)
			explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _start(0),  _size(0), _capacity(0) {}

			//Fill constructor
			//Constructs a container with n elements. Each element is a copy of val.
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				_size = n;
				_capacity = n;
				_alloc = alloc;
				_start = _alloc.allocate(n); //allocates a block of storage with a size large enough to contain n elements of type value_type
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_start + i, val); //constructs (by calling the constructor of value_type with argument val) an element object on the location pointed by _start + i
			}

			//Range constructor
			//Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
			template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) //SFINAE !!!
			{
				if (first > last)
					throw std::length_error("vector");
				_alloc = alloc;
				_size = last - first;
				_capacity = _size;
				_start = _alloc.allocate(_size); //allocates a block of storage with a size large enough to contain _size elements of type value_type
				for (difference_type i = 0; i < _size; i++)
					_alloc.construct(_start + i, *(first + i)); //constructs (by calling the constructor of value_type with the corresponding range element as argument) an element object on the location pointed by _start + i
			}

			//Copy constructor
			//Constructs a container with a copy of each of the elements in x, in the same order.
			//The copy constructor creates a container that keeps and uses a copy of x's allocator.
			vector (const vector& x)
			{
				_alloc = x._alloc;
				*this = x;
			}

			//Assigment operator (=)
			//Assigns new contents to the container, replacing its current contents, and modifying its size accordingly.
			//The container preserves its current allocator, which is used to allocate storage in case of reallocation.
			vector& operator= (const vector& x)
			{
				if (x == *this)
					return (*this);

				//Destroy existing objects
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_start + i);

				//Modify size and reallocate more capacity if necessary
				this->_size = x._size;
				if (_size > _capacity)
				{
					if (_capacity != 0)
						_alloc.deallocate(_start, _capacity);
					_capacity = _size;
					_start = _alloc.allocate(_capacity);
				}

				//Constructs the elements by copying those from x
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(_start + i, x[i]);

				return *this;
			}
			
			//Destructor
			~vector()
			{
				//Destroy existing objects
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_start + i);

				//Deallocate memory block
				if (_capacity != 0)
					_alloc.deallocate(_start, _capacity);
			}

			/// ITERATORS ///

			//Returns an iterator pointing to the first element in the vector
			iterator begin()
			{
				return iterator(_start);
			}

			//Returns a const iterator pointing to the first element in the vector
			const_iterator begin() const
			{
				return const_iterator(_start);
			}

			//Returns an iterator referring to the past-the-end element in the vector container.
			//The past-the-end element is the theoretical element that would follow the last element in the vector.
			iterator end()
			{
				return iterator(_first + _size);
			}

			//Returns a const iterator referring to the past-the-end element in the vector container.
			//The past-the-end element is the theoretical element that would follow the last element in the vector.
			const_iterator end() const
			{
				return const_iterator(_first + _size);
			}

			//Returns a reverse iterator pointing to the last element in the vector (reverse beginning).
			//Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
			//rbegin points to the element right before the one that would be pointed to by member end.
			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			}

			//Returns a const reverse iterator pointing to the last element in the vector (reverse beginning).
			//Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
			//rbegin points to the element right before the one that would be pointed to by member end.
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			}

			//Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector (reverse end).
			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			}

			//Returns a const reverse iterator pointing to the theoretical element preceding the first element in the vector (reverse end).
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			}

			/// CAPACITY ///

			//Returns the number of elements in the vector.
			size_type size() const
			{
				return _size;
			}

			//Returns the maximum number of elements that the vector can hold
			size_type max_size() const
			{
				return _alloc.max_size();
			}

			//Resizes the container so that it contains n elements.
			void resize (size_type n, value_type val = value_type())
			{
				//If n is smaller than the current container size, the content is reduced to its first n elements
				if (n < _size)
				{
					//Destroy objects beyond n
					for (size_type i = n; i < _size; i++)
						_alloc.destroy(_start + i);
					
					_size = n;
				}
				//If n is greater than the current container size, the content is expanded by inserting at the end as many elements as needed to reach a size of n.
				//If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
				else if (n > _size)
				{
					//If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
					if (n > _capacity)
						reserve(n);

					for (size_type i = _size; i < n; i++)
						_alloc.construct(_start + i, val); //constructs (by calling the constructor of value_type with argument val) an element object on the location pointed by _start + i
					
					_size = n;
				}
			}

			//Returns the size of the storage space currently allocated for the vector
			size_type capacity() const
			{
				return _capacity;
			}

			//Returns whether the vector is empty (whether its size is 0).
			bool empty() const
			{
				return _size == 0;
			}

			//Requests that the vector capacity be at least enough to contain n elements.
			void reserve (size_type n)
			{
				if (n > max_size())
					throw (std::length_error("vector::reserve"));

				//If current capacity is sufficient, do nothing
				if (n <= _capacity)
					return;

				//PROTEGER LA PARTIE ALLOCATION ET CONSTRUCT ?!
				//Allocate a new block of memory and copy the old container into the new one
				pointer new_start = _alloc.allocate(n); //allocates a block of storage with a size large enough to contain n elements of type value_type
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(new_start + i, *(_start + i)); //constructs (by calling the constructor of value_type with argument val) an element object on the location pointed by _start + i

				//Destroy objects in the old container
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_start + i);
				//Deallocate the old memory block
				if (_capacity != 0)
					_alloc.deallocate(_start, _capacity);

				//Update the container pointer and capacity
				_start = new_start;
				_capacity = n;
			}


			private:
				//Private variables
				allocator_type _alloc; //allocator object to allocate/free memory dynamically
				pointer _start; //pointer to the beginning of the array
				size_type _size; //current number of elements in the array
				size_type _capacity; //full capacity of the allocated array
			


	};
}


#endif