#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <functional>
# include "utils.hpp"
# include "avl_tree.hpp"
# include "iterator.hpp"

namespace ft
{
	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::TreeNode<pair<const Key,T> > > >
	class map
	{	
		public:
			///--------------///
			/// MEMBER TYPES ///
			///--------------///

			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const key_type, mapped_type> value_type;
			typedef Compare key_compare;

			//Nested value_compare class
			//Returns a comparison object that can be used to compare two elements to get whether the key of the first one goes before the second.
			class value_compare
			{
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef ft::avl_tree_iterator<ft::TreeNode<value_type>, false> iterator;
			typedef ft::avl_tree_iterator<const ft::TreeNode<value_type>, true> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			typedef typename std::ptrdiff_t difference_type;
			typedef std::size_t size_type;

			///------------------///
			/// MEMBER FUNCTIONS ///
			///------------------///
			
			//Empty constructor
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(tree_type(value_compare(_comp), _alloc)), _comp(comp), _alloc(alloc) {}

			//Range constructor
			//Constructs a container with as many elements as the range [first,last),
			//with each element constructed from its corresponding element in that range.
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
				: _tree(tree_type(value_compare(_comp), _alloc)), _comp(comp), _alloc(alloc) 
			{
				insert(first, last); //insert range in maps's tree
			}

			//Copy constructor
			//Constructs a container with a copy of each of the elements in x.
			//The copy constructor creates a container that keeps and uses copies of x's allocator and comparison object.
			map (const map& x) : _tree(tree_type(value_compare(_comp), _alloc)), _comp(x._comp), _alloc(x._alloc)
			{
				const_iterator beg = x.begin();
				insert(x.begin(), x.end());
			}

			//Destructor
			~map()
			{
				clear();
			}

			//Assginment operator overload
			//Copies all the elements from x into the container, changing its size accordingly.
			//The container preserves its current allocator, which is used to allocate additional storage if needed.
			map& operator= (const map& x)
			{
				if (&x == this)
					return (*this);
				clear();
				insert(x.begin(), x.end());
				return *this;
			}

			//Returns an iterator referring to the first element in the map container.
			iterator begin()
			{
				if (_tree.root == NULL)
					return iterator(_tree.dummy_past_end);
				return iterator(_tree.min_value_node(_tree.root), _tree.dummy_past_end);
			}
			
			//Returns a const iterator referring to the first element in the map container.
			const_iterator begin() const
			{
				if (_tree.root == NULL)
					return const_iterator(_tree.dummy_past_end);
				return const_iterator(_tree.min_value_node(_tree.root), _tree.dummy_past_end);
			}

			//Returns an iterator referring to the past-the-end element in the map container.
			iterator end()
			{
				return iterator(_tree.dummy_past_end, _tree.dummy_past_end);
			}

			//Returns a const iterator referring to the past-the-end element in the map container.
			const_iterator end() const
			{
				return const_iterator(_tree.dummy_past_end, _tree.dummy_past_end);
			}

			//Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
			reverse_iterator rbegin()
			{
				return reverse_iterator(end());
			}
			
			//Returns a reverse const iterator pointing to the last element in the container (i.e., its reverse beginning).
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end());
			}

			//Returns a reverse iterator pointing to the theoretical element right before the first element in the map container (which is considered its reverse end).
			reverse_iterator rend()
			{
				return reverse_iterator(begin());
			}
			
			//Returns a const reverse iterator pointing to the theoretical element right before the first element in the map container (which is considered its reverse end).
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			}

			//Returns whether the map container is empty (i.e. whether its size is 0).
			bool empty() const
			{
				return _tree.tree_is_empty();
			}

			size_type size() const
			{
				return _tree.size(_tree.root);
			}

			//Returns the maximum number of elements that the map container can hold.
			size_type max_size() const
			{
				return _tree.max_size();
			}

			//If k matches the key of an element in the container, the function returns a reference to its mapped value.
			//If not, inserts a new element with that key and returns a reference to its mapped value
			mapped_type& operator[] (const key_type& k)
			{
				return (*((insert(ft::make_pair(k, mapped_type()))).first)).second;
			}

			//Returns a reference to the mapped value of the element identified with key k.
			//If k does not match the key of any element in the container, the function throws an out_of_range exception.
			mapped_type& at (const key_type& k)
			{
				iterator it_found = find(k);
				if (it_found == end())
					throw std::out_of_range("map::at");
				return it_found->second;
			}

			//Returns a reference to the mapped value of the element identified with key k.
			//If k does not match the key of any element in the container, the function throws an out_of_range exception.
			const mapped_type& at (const key_type& k) const
			{
				iterator it_found = find(k);
				if (*it_found == end())
					throw std::out_of_range("map::at");
				return it_found->second;
			}

			//Return a pair, with its member pair::first set to an iterator pointing to either the newly inserted element or to the element with an equivalent key in the map.
			//The pair::second element in the pair is set to true if a new element was inserted or false if an equivalent key already existed.
			pair<iterator,bool> insert (const value_type& val)
			{
				bool inserted;
				typename ft::TreeNode<value_type> * inserted_or_found;

				_tree.create_and_insert(val, &inserted, &inserted_or_found);
				return ft::make_pair<iterator, bool>(iterator(inserted_or_found, _tree.dummy_past_end), inserted);
			}

			//Insert val using position as an hint about where to insert it. Position might not be used.
			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				return insert(val).first;
			}

			//Copies of the elements in the range [first,last) are inserted in the container.
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last, typename ft::enable_if< ! ft::is_integral<InputIterator>::value >::type* = 0) //disable this overload if enable_if condition not statisfied
			{
				while (first != last)
					insert(*(first++));
			}
			
			//Removes the element pointed to by position from the map
			void erase (iterator position)
			{
				_tree.root = _tree.delete_node(_tree.root, *position);
				_tree.dummy_past_end->left = _tree.max_value_node(_tree.root); //update dummy past-the-end
			}

			//Removes the element of key k from the map
			//Returns the number of elements erased
			size_type erase (const key_type& k)
			{
				if (find(k) == end())
					return 0;
				_tree.root = _tree.delete_node(_tree.root, ft::make_pair(k, mapped_type()));
				_tree.dummy_past_end->left = _tree.max_value_node(_tree.root); //update dummy past-the-end
				return 1;
			}

			void erase (iterator first, iterator last)
			{
				while (first != last)
					erase(first++);
					
			}

			//Exchanges the content of the container by the content of x, which is another map of the same type
			void swap (map& x)
			{
				_tree.swap(x._tree);
				std::swap(_alloc, x._alloc);
				std::swap(_comp, x._comp);
			}

			//Removes all elements from the map container (which are destroyed), leaving the container with a size of 0.
			void clear()
			{
				_tree.clear(_tree.root);
				_tree.root = NULL;
			}

			//Returns a copy of the comparison object used by the container to compare keys.
			key_compare key_comp() const
			{ 
				return key_compare(); 
			}

			//Returns a comparison object that can be used to compare two elements to get whether the key of the first one goes before the second.
			value_compare value_comp() const
			{ 
				return value_compare(key_compare()); 
			}

			//Searches the container for an element with a key equivalent to k and returns an iterator to it if found, otherwise it returns an iterator to map::end.
			iterator find (const key_type& k)
			{
				typename ft::TreeNode<value_type> * node_found = _tree.iterative_search(ft::make_pair(k, mapped_type()));
				if (node_found == NULL)
					return iterator(end());
				return iterator(node_found, _tree.dummy_past_end);
			}

			//Searches the container for an element with a key equivalent to k and returns a const iterator to it if found, otherwise it returns a const iterator to map::end.
			const_iterator find (const key_type& k) const
			{
				typename ft::TreeNode<value_type> * node_found = _tree.iterative_search(ft::make_pair(k, mapped_type()));
				if (node_found == NULL)
					return const_iterator(end());
				return const_iterator(node_found, _tree.dummy_past_end);
			}

			//Searches the container for elements with a key equivalent to k and returns the number of matches.
			//Because all elements in a map container are unique, the function can only return 1 (if the element is found) or zero (otherwise).
			size_type count (const key_type& k) const
			{
				const_iterator it_found = find(k);
				if (it_found == end())
					return 0;
				return 1;
			}

			//Returns an iterator pointing to the first element in the container whose key is not considered to go before k
			iterator lower_bound (const key_type& k)
			{
				iterator begin = this->begin();
				iterator end = this->end();

				while (begin != end)
				{
					if (!_comp((*begin).first, k))
						return (begin);
					begin++;
				}
				return end; //if all keys are considered to go before k.
			}

			//Returns a const iterator pointing to the first element in the container whose key is not considered to go before k
			const_iterator lower_bound (const key_type& k) const
			{
				const_iterator begin = this->begin();
				const_iterator end = this->end();

				while (begin != end)
				{
					if (!_comp((*begin).first, k))
						return (begin);
					begin++;
				}
				return end; //if all keys are considered to go before k.
			}

			//Returns an iterator pointing to the first element in the container whose key is considered to go after k.
			iterator upper_bound (const key_type& k)
			{
				iterator begin = this->begin();
				iterator end = this->end();

				while (begin != end)
				{
					if (_comp(k, (*begin).first))
						return (begin);
					begin++;
				}
				return end; //if all keys are considered to go after k.
			}

			//Returns a const iterator pointing to the first element in the container whose key is considered to go after k.
			const_iterator upper_bound (const key_type& k) const
			{
				const_iterator begin = this->begin();
				const_iterator end = this->end();

				while (begin != end)
				{
					if (_comp(k, (*begin).first))
						return (begin);
					begin++;
				}
				return end; //if all keys are considered to go after k.
			}

			
			//Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.
			pair<iterator,iterator>             equal_range (const key_type& k)
			{
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}

			//Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.
			//If the map object is const-qualified, the function returns a pair of const_iterator
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}
			
			//Returns a copy of the allocator object associated with the map.
			allocator_type get_allocator() const
			{
				return allocator_type(_alloc);
			}
		private:
			typedef AVLTree<value_type, value_compare, allocator_type> tree_type;
			tree_type _tree;
			key_compare _comp;
			allocator_type _alloc;

	};

	///-------------------------------///
	/// NON-MEMBER FUNCTION OVERLOADS ///
	///-------------------------------///

	/// RELATIONAL OPERATORS ///

	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
		if (lhs.size() != rhs.size())
			return false;

		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
			return !(lhs == rhs); 
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
			return rhs < lhs;
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
			return !(lhs > rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> & lhs, const map<Key, T, Compare, Alloc> & rhs)
	{
			return !(lhs < rhs);
	}

	//The contents of container x are exchanged with those of y.
	template<class Key, class T, class Compare, class Alloc>
	void swap(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
} 

#endif