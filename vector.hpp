#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <vector> //RETIRER !!!
# include <stdexcept>


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
				return iterator(_start + _size);
			}

			//Returns a const iterator referring to the past-the-end element in the vector container.
			//The past-the-end element is the theoretical element that would follow the last element in the vector.
			const_iterator end() const
			{
				return const_iterator(_start + _size);
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
						reserve(n); //ALLOUER PLUS ?

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

			/// ELEMENT ACCESS ///

			//Returns a reference to the element at position n in the vector container.
			reference operator[] (size_type n)
			{
				return *(_start + n);
			}
			
			//Returns a const reference to the element at position n in the vector container.
			const_reference operator[] (size_type n) const
			{
				return *(_start + n);
			}

			//Returns a reference to the element at position n in the vector.
			//The function automatically checks whether n is within the bounds of valid elements in the vector, throwing an out_of_range exception if it is not
			reference at (size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("vector::at index out of range");

				return *(_start + n);
			}

			//Returns a const reference to the element at position n in the vector.
			//The function automatically checks whether n is within the bounds of valid elements in the vector, throwing an out_of_range exception if it is not	
			const_reference at (size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("vector::at index out of range");

				return *(_start + n);
			}

			//Returns a reference to the first element in the vector.
			//Unlike member vector::begin, which returns an iterator to this element
			reference front()
			{
				return *_start;
			}
			
			//Returns a const reference to the first element in the vector.
			//Unlike member vector::begin, which returns an iterator to this element
			const_reference front() const
			{
				return *_start;
			}

			//Returns a reference to the last element in the vector.
			//Unlike member vector::end, which returns an iterator just past this element
			reference back()
			{
				return *(_start + _size - 1);
			}
			
			//Returns a const reference to the last element in the vector.
			//Unlike member vector::end, which returns an iterator just past this element
			const_reference back() const
			{
				return *(_start + _size - 1);
			}

			/// MODIFIERS ///

			//Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
			//In the range version, the new contents are elements constructed from each of the elements in the range between first and last, in the same order.
			template <class InputIterator>  
			void assign (InputIterator first, InputIterator last) //SFINAE !
			{
				if (first > last)
					throw std::length_error("vector::assign");

				//Destroy all previous elements held in the container
				clear();

				//Reallocate storage space if necessary
				size_type nb_elements = static_cast<size_type>(last - first);
				if (nb_elements > _capacity)
				{
					//Deallocate existing storage space
					_alloc.deallocate(_start, _capacity);
					_start = _alloc(nb_elements);
					_capacity = nb_elements;
				}
				//Construct with new elements
				for (size_type i = 0; first != last; i++, first++) //iteration ok ?
					_alloc.construct(_start + i, *first);

				_size = nb_elements;
			}

			//Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
			//In the fill version, the new contents are n elements, each initialized to a copy of val.
			void assign (size_type n, const value_type& val)
			{
				//Destroy all previous elements held in the container
				clear();

				//Reallocate storage space if necessary
				if (n > _capacity)
				{
					//Deallocate existing storage space
					_alloc.deallocate(_start, _capacity);
					_start = _alloc(n);
					_capacity = n;
				}
				//Construct with new elements
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_start + i, val);

				_size = n;
			}

			//Adds a new element at the end of the vector, after its current last element.
			void push_back (const value_type& val)
			{
				//Reallocation if new vector size surpasses the current vector capacity
				if (_size == _capacity)
				{
					if (_capacity == 0)
						reserve(1);
					else
						reserve(_capacity * 2); //double the current capacity to prevent frequent reallocation
				}

				//Construct the new element
				_alloc.construct(_start + _size, val);
				_size++;
			}

			//Removes the last element in the vector, effectively reducing the container size by one.
			void pop_back()
			{
				//Destroy the last element
				_alloc.destroy(_start + _size - 1);
				_size--;
			}

			//The vector is extended by inserting new elements before the element at the specified position,
			//effectively increasing the container size by the number of elements inserted.
			//Single element
			iterator insert (iterator position, const value_type& val)
			{
				size_type insert_index =  static_cast<size_type>(position - _start);
				insert(position, 1, val);
				return iterator(_start + insert_index);
			}

			//The vector is extended by inserting new elements before the element at the specified position,
			//effectively increasing the container size by the number of elements inserted.
			//Fill
			void insert (iterator position, size_type n, const value_type& val)
			{
				if (n > max_size() - _size || position < begin() || position > end())
					throw std::length_error("vector::insert");

				size_type insert_index =  static_cast<size_type>(position - _start);

				//Reallocation if new vector size surpasses the current vector capacity
				if (_size + n > _capacity)
				{
					pointer new_start = _alloc.allocate(_size + n); //ALLOUER PLUS ?!
					
					//Reconstruct elements in new array up until the insert_index
					for (size_type i = 0; i < (insert_index - 1); i++)
					{
						_alloc.construct(new_start + i, *(_start + i));
						_alloc.destroy(_start + i);
					}

					//Move all elemets after insert_index + n to their old position + n
					size_type end_of_insert_index = insert_index + n; //where the insertion stops, which is the new beginning index for the displaced elements
					for (size_type i = end_of_insert_index; i < (end_of_insert_index + n); i++)
					{
							_alloc.construct(new_start + i, *(_start + i - n));
							_alloc.destroy(_start + i - n);
					}
					
					//Insert the n new elements copied from val starting at insert_index
					for (size_type i = insert_index; i < end_of_insert_index; i++)
						_alloc.construct(new_start + i, val);

					_alloc.deallocate(_start, _capacity);
					_start = new_start;
					_capacity = _size + n;
					_size += n;
				}
				//If no reallocation necessary, directly displace elements and insert n copies of val
				else
				{
					//Move all elemets after insert_index + n to their old position + n
					size_type end_of_insert_index = insert_index + n; //where the insertion stops, which is the new beginning index for the displaced elements
					for (size_type i = end_of_insert_index; i < (end_of_insert_index + n); i++)
					{
							_alloc.construct(_start + i, *(_start + i - n));
							_alloc.destroy(_start + i - n);
					}
					
					//Insert the n new elements copied from val starting at insert_index
					for (size_type i = insert_index; i < end_of_insert_index; i++)
						_alloc.construct(_start + i, val);

					_size += n;
				}
			}

			//The vector is extended by inserting new elements before the element at the specified position,
			//effectively increasing the container size by the number of elements inserted.
			//Range
			template <class InputIterator>    
			void insert (iterator position, InputIterator first, InputIterator last) //SFINAE !
			{
				if (first > last || position < begin() || position > end())
					throw std::length_error("vector::insert");

				size_type n = static_cast<size_type>(last - first);
				size_type insert_index =  static_cast<size_type>(position - _start);

				//Reallocation if new vector size surpasses the current vector capacity
				if (_size + n > _capacity)
				{
					pointer new_start = _alloc.allocate(_size + n); //ALLOUER PLUS ?!
					
					//Reconstruct elements in new array up until the insert_index
					for (size_type i = 0; i < (insert_index - 1); i++)
					{
						_alloc.construct(new_start + i, *(_start + i));
						_alloc.destroy(_start + i);
					}

					//Move all elemets after insert_index + n to their old position + n
					size_type end_of_insert_index = insert_index + n; //where the insertion stops, which is the new beginning index for the displaced elements
					for (size_type i = end_of_insert_index; i < (end_of_insert_index + n); i++)
					{
							_alloc.construct(new_start + i, *(_start + i - n));
							_alloc.destroy(_start + i - n);
					}
					
					//Insert the n new elements copied from the range starting at insert_index
					for (size_type i = insert_index, j = 0; i < end_of_insert_index; i++, j++)
						_alloc.construct(new_start + i, *(first + j));

					_alloc.deallocate(_start, _capacity);
					_start = new_start;
					_capacity = _size + n;
					_size += n;
				}
				//If no reallocation necessary, directly displace elements and insert n copies of val
				else
				{
					//Move all elemets after insert_index + n to their old position + n
					size_type end_of_insert_index = insert_index + n; //where the insertion stops, which is the new beginning index for the displaced elements
					for (size_type i = end_of_insert_index; i < (end_of_insert_index + n); i++)
					{
							_alloc.construct(_start + i, *(_start + i - n));
							_alloc.destroy(_start + i - n);
					}
					
					//Insert the n new elements copied from the range starting at insert_index
					for (size_type i = insert_index, j = 0; i < end_of_insert_index; i++, j++)
						_alloc.construct(_start + i, *(first + j));

					_size += n;
				}
			}

			//Removes from the vector a single element
			iterator erase (iterator position)
			{
				size_type erase_index =  static_cast<size_type>(position - _start);

				//Move all elements one index to the left
				for (size_type i = erase_index; i < _size - 1; i++) //s'arrete au bon indice ?!
				{
					_alloc.construct(_start + i, *(_start + i + 1));
					_alloc.destroy(_start + i + 1);
				}

				_size--;
				return iterator(_start + erase_index);
			}
			
			//Removes from the vector a range of elements [first,last)
			iterator erase (iterator first, iterator last)
			{
				
				size_type n =  static_cast<size_type>(last - first);
				size_type erase_index =  static_cast<size_type>(first - _start);

				//Move all elements n indices to the left
				for (size_type i = erase_index; i < _size - n - 1; i++) //s'arrete au bon indice ?!
				{
					_alloc.destroy(_start + i);
					_alloc.construct(_start + i, *(_start + n + i));
					_alloc.destroy(_start + n + i);
				}

				_size -= n;
				return iterator(_start + erase_index);
			}

			//Exchanges the content of the container by the content of x, which is another vector object of the same type.
			void swap (vector& x)
			{
				std::swap(_alloc, x._alloc);
				std::swap(_start, x._start);
				std::swap(_capacity, x._capacity);
				std::swap(_size, x._size);
			}

			//Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
			void clear()
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_start + i);

				_size = 0;
			}

			/// ALLOCATOR ///

			//Returns a copy of the allocator object associated with the vector.
			allocator_type get_allocator() const
			{
				return allocator_type(_alloc);
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