/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_tree.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:02:00 by vfiszbin          #+#    #+#             */
/*   Updated: 2023/01/17 18:25:46 by vfiszbin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_SEARCH_TREE_HPP
# define BINARY_SEARCH_TREE_HPP

#include <iostream> //REMOVE !!!
#define SPACE 10 //REMOVE !!!
# include "utils.hpp"
# include <memory>
// #include <cstring> //!!!

namespace ft
{
	template <class T>
	class TreeNode 
	{
		public:
			typedef T value_type;
			
			T value;
			int height;
			TreeNode * left;
			TreeNode * right;
			TreeNode * parent;

			TreeNode() : value(), height(0), left(NULL), right(NULL), parent(NULL)  {}

			TreeNode(T v) : value(v), height(0), left(NULL), right(NULL), parent(NULL) {}
	};

	//AVL Tree is a balanced binary search tree. 
	//For each node, the height difference between left and right subtrees (balance factor) cannot be more than one
	//It ensures that lookup, insertion, and deletion all take O(log n)
	//T : type of the value contained by each node (ex: the type pair)
	template <class T, class Compare = std::less<T>, class Alloc = std::allocator<TreeNode<T> > >
	class AVLTree 
	{
		public:
			typedef TreeNode<T> node_type;
			typedef Alloc allocator_type;
			typedef std::size_t size_type;
			typedef Compare value_compare; //comparison on the first element (key) of the pair only. True if first key inferior.

			node_type* root;
			//a dummy node used when end() is called in map. Its left child is root so that the -- iterator operator can find the last node
			node_type* dummy_past_end; 
			
			AVLTree(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(value_compare())
			{
				root = NULL;
				dummy_past_end = _alloc.allocate(1);
				_alloc.construct(dummy_past_end, T());
				dummy_past_end->left = root;
			}

			AVLTree(const value_compare &comp, const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(comp)
			{
				root = NULL;
				dummy_past_end = _alloc.allocate(1);
				_alloc.construct(dummy_past_end, T());
				dummy_past_end->left = root;
			}

			~AVLTree()
			{
				clear(root);
				_alloc.destroy(dummy_past_end);
				_alloc.deallocate(dummy_past_end, 1);
			}

			bool tree_is_empty() const
			{
				if (root == NULL) 
					return true;
				else 
					return false;
			}
			
			// // Get Height  !!!
			// int height(node_type * r) const
			// {
			// 	if (r == NULL)
			// 		return -1; //base height is -1 for NULL nodes
					
			// 	else 
			// 	{
			// 		//recursively compute height in each subtree
			// 		int lheight = height(r->left);
			// 		int rheight = height(r->right);

			// 		//use the biggest height, +1 to account for current node
			// 		if (lheight > rheight)
			// 			return (lheight + 1);
			// 		else 
			// 			return (rheight + 1);
			// 	}
			// }

			//return height for node r
			int height(node_type * r) const
			{
				if (r == NULL)
					return -1; //base height is -1 for NULL nodes
				return r->height;
			}
							
			//update height for node r
			void update_height(node_type * r)
			{
				int lheight = height(r->left);
				int rheight = height(r->right);
				r->height = std::max(lheight, rheight) + 1;
			}

			//update the height of all the direct predecessors of r
			void update_predecessors_height(node_type * r)
			{
				while (r->parent)
				{
					update_height(r->parent->height);
					r = r->parent;
				}
			}

			// Get Balance factor of node N  
			int get_balance_factor(node_type * n) const
			{
				if (n == NULL)
					return -1; //base height is -1 for NULL nodes
				return height(n->left) - height(n->right);
			}

			node_type * right_rotate(node_type * y) 
			{
				node_type * x = y->left;
				node_type * T2 = x->right;

				// Perform rotation  
				if (x && y)
					x->parent = y->parent;
				
				x->right = y;
				if (y != NULL)
					y->parent = x;

				y->left = T2;
				if (T2 != NULL)
					T2->parent = y;

				update_height(y);
				update_height(x);
				return x;
			}

			node_type * left_rotate(node_type * x) 
			{
				node_type * y = x->right;
				node_type * T2 = y->left;

				// Perform rotation  
				if (x && y)
					y->parent = x->parent;

				y->left = x;
				if (x != NULL)
					x->parent = y;
				
				x->right = T2;
				if (T2 != NULL)
					T2->parent = x;

				update_height(x);
				update_height(y);
				return y;
			}

			//Allocate and construct a node with the given value, then insert it into the tree
			void create_and_insert(T value, bool * inserted, node_type ** inserted_or_found)
			{
				node_type* new_node = _alloc.allocate(1);
				_alloc.construct(new_node, value);
				root = this->insert(root, new_node, inserted, inserted_or_found);
				if (dummy_past_end->left == NULL || _comp(dummy_past_end->left->value, value))
					dummy_past_end->left = max_value_node(root); //update dummy past-the-end
				if (*inserted == false)
				{
					_alloc.destroy(new_node);
					_alloc.deallocate(new_node, 1);
				}
			}

			//Insert new_node into the AVL tree starting at root r
			//Return the new root
			node_type * insert(node_type * r, node_type * new_node, bool * inserted, node_type ** inserted_or_found) 
			{
				/// Usual binary search tree insertion steps ///
				
				//Base case : if no existing node at this spot, we can insert the new node here
				if (r == NULL) 
				{
					r = new_node;
					*inserted = true; //indicates the caller that the node was successfully inserted
					*inserted_or_found = r; //pointer to the node that was inserted
					return r;
				}
				//If key to insert is inferior to current node key, go left
				if (_comp(new_node->value, r->value)) 
				{
					r->left = insert(r->left, new_node, inserted, inserted_or_found);
					if (r->left != NULL)
						r->left->parent = r;
					update_height(r);
				}
				//If key to insert is superior to current node key, go right
				else if (_comp(r->value, new_node->value)) 
				{
					r->right = insert(r->right, new_node, inserted, inserted_or_found);
					if (r->right != NULL)
						r->right->parent = r;
					update_height(r);
				} 
				//If the key already exists, do nothing
				else 
				{
					*inserted = false; //indicates the caller that the node was not inserted
					*inserted_or_found = r; //pointer to the already existing node with same key
					return r;
				}

				/// The following steps are specific to AVL trees, we must rebalance if necessary ///
				/// There are only 4 possible imbalance cases ///

				//The first node to get to these steps is the one right after the recursive function first returned,
				//so we are assured to be as far in the tree as possible (right above the insertion spot).
				//We will then gradually climb the tree towards the root.
				
				int bf = get_balance_factor(r);
				//Left Left Case  
				if (bf > 1 && _comp(new_node->value, r->left->value))
					return right_rotate(r);

				//Right Right Case  
				if (bf < -1 && _comp(r->right->value, new_node->value))
					return left_rotate(r);

				//Left Right Case  
				if (bf > 1 && _comp(r->left->value, new_node->value)) 
				{
					r->left = left_rotate(r->left);
					return right_rotate(r);
				}

				//Right Left Case  
				if (bf < -1 && _comp(new_node->value, r->right->value)) 
				{
					r->right = right_rotate(r->right);
					return left_rotate(r);
				}

				/* return the (unchanged) node pointer */
				return r;

			}

			node_type * min_value_node(node_type * node) const
			{
				node_type * current = node;
				//loop down to find the leftmost leaf
				while (current && current->left != NULL) 
				{
					current = current->left;
				}
				return current;
			}

			node_type * max_value_node(node_type * node) const
			{
				node_type * current = node;
				//loop down to find the rightmost leaf
				while (current && current->right != NULL) 
				{
					current = current->right;
				}
				return current;
			}

			//Delete the node of key k from the tree starting at root r.
			//Return the new root
			node_type * delete_node(node_type * r, T k) 
			{
				/// Usual binary search tree deletion steps ///
				
				//Base case : no node with key k was found
				if (r == NULL) 
				{
					return NULL;
				}
				//If the key to be deleted is smaller than the current node's key, 
				//then it must be in the left subtree 
				else if (_comp(k, r->value)) 
				{
					r->left = delete_node(r->left, k);
					if (r->left != NULL)
						r->left->parent = r;
					update_height(r);
				}
				//If the key to be deleted is greater than the current node's key, 
				//then it must be in the right subtree 
				else if (_comp(r->value, k)) 
				{
					r->right = delete_node(r->right, k);
					if (r->right != NULL)
						r->right->parent = r;
					update_height(r);
				}
				//If the key is same as current node's key, then the current node is the one to delete
				else 
				{
					//node with only one child or no child 
					if (r->left == NULL) 
					{
						node_type * temp = r->right;
						_alloc.destroy(r);
						_alloc.deallocate(r, 1);
						return temp; //return the child to link it with the deleted node's parent
					}
					else if (r->right == NULL) 
					{
						node_type * temp = r->left;
						_alloc.destroy(r);
						_alloc.deallocate(r, 1);
						return temp; //return the child to link it with the deleted node's parent
					} 
					else 
					{
						//node with two children: find the inorder successor (smallest key in the right subtree) 
						node_type * temp = min_value_node(r->right);

						//unlink the inorder successor from the tree so that it can replace the deleted node
						r->right = replace_node(r->right, temp->value);
						
						//Replace the deleted node by the inorder successor
						temp->parent = r->parent;
						temp->left = r->left;
						temp->right = r->right;
						if (r->left)
							r->left->parent = temp;
						if (r->right)
							r->right->parent = temp;
						if (r->parent)
						{
							if (r->parent->left == r)
								r->parent->left = temp;
							else
								r->parent->right = temp;
						}
						//Delete the node to be deleted
						_alloc.destroy(r);
						_alloc.deallocate(r, 1);
						r = temp;
						update_height(r);
					}
				}

				/// The following steps are specific to AVL trees, we must rebalance if necessary ///

				int bf = get_balance_factor(r);
				//Left Left Imbalance/Case or Right rotation 
				if (bf == 2 && get_balance_factor(r->left) >= 0)
					return right_rotate(r);
				//Left Right Imbalance/Case or LR rotation 
				else if (bf == 2 && get_balance_factor(r->left) == -1) 
				{
					r->left = left_rotate(r->left);
					return right_rotate(r);
				}
				//Right Right Imbalance/Case or Left rotation	
				else if (bf == -2 && get_balance_factor(r->right) <= -0)
					return left_rotate(r);
				//Right Left Imbalance/Case or RL rotation 
				else if (bf == -2 && get_balance_factor(r->right) == 1) 
				{
					r->right = right_rotate(r->right);
					return left_rotate(r);
				}

				return r;
			}
			
			//Sames as delete_node, except the node with value k is not destroyed but simply unlinked from the rest of the tree
			node_type * replace_node(node_type * r, T k)
			{
				//Base case : no node with key k was found
				if (r == NULL) 
				{
					return NULL;
				}
				//If the key to be replaced is smaller than the current node's key, 
				//then it must be in the left subtree 
				else if (_comp(k, r->value)) 
				{
					r->left = replace_node(r->left, k);
					if (r->left != NULL)
						r->left->parent = r;
					update_height(r);
				}
				//If the key to be replaced is greater than the current node's key, 
				//then it must be in the right subtree 
				else if (_comp(r->value, k)) 
				{
					r->right = replace_node(r->right, k);
					if (r->right != NULL)
						r->right->parent = r;
					update_height(r);
				}
				//If the key is same as current node's key, then the current node is the one to replace
				else 
				{
					//node with only one child or no child 
					if (r->left == NULL) 
					{
						node_type * temp = r->right;
						return temp; //return the child to link it with the replaced node's parent
					} 
					else if (r->right == NULL) 
					{
						node_type * temp = r->left;
						return temp; //return the child to link it with the replaced node's parent
					}
				}

				/// The following steps are specific to AVL trees, we must rebalance if necessary ///

				int bf = get_balance_factor(r);
				//Left Left Imbalance/Case or Right rotation 
				if (bf == 2 && get_balance_factor(r->left) >= 0)
					return right_rotate(r);
				//Left Right Imbalance/Case or LR rotation 
				else if (bf == 2 && get_balance_factor(r->left) == -1) 
				{
					r->left = left_rotate(r->left);
					return right_rotate(r);
				}
				//Right Right Imbalance/Case or Left rotation	
				else if (bf == -2 && get_balance_factor(r->right) <= -0)
					return left_rotate(r);
				//Right Left Imbalance/Case or RL rotation 
				else if (bf == -2 && get_balance_factor(r->right) == 1) 
				{
					r->right = right_rotate(r->right);
					return left_rotate(r);
				}
				
				return r;
			}


			//ENELVER TOUS CES PRINT !!!
			void print2D(node_type * r, int space) {
				if (r == NULL) // Base case  1
				return;
				space += SPACE; // Increase distance between levels   2
				print2D(r -> right, space); // Process right child first 3 
				std::cout << std::endl;
				for (int i = SPACE; i < space; i++) // 5 
				std::cout << " "; // 5.1  
				if (r->parent)
					std::cout << r -> value.first << "," << r->value.second << "," << r->parent->value.first <<"\n"; // 6 t 
				else
					std::cout << r -> value.first << "," << r->value.second << "," << "\n"; // 6
				print2D(r -> left, space); // Process left child  7
			}
			void printPreorder(node_type * r) //(current node, Left, Right) 
			{
				if (r == NULL)
				return;
				/* first print data of node */
				if (r->parent)
					std::cout << r -> value.first << "," << r->value.second << "," << r->parent->value.first << " "; 
				else
					std::cout << r -> value.first << "," << r->value.second  << " ";
				/* then recur on left sutree */
				printPreorder(r -> left);
				/* now recur on right subtree */
				printPreorder(r -> right);
			}

			void printInorder(node_type * r) //  (Left, current node, Right)
			{
				if (r == NULL)
				return;
				/* first recur on left child */
				printInorder(r -> left);
				/* then print the data of node */
				if (r->parent)
					std::cout << r -> value.first << "," << r->value.second << "," << r->parent->value.first << " "; 
				else
					std::cout << r -> value.first << "," << r->value.second  << " ";
				/* now recur on right child */
				printInorder(r -> right);
			}
			void printPostorder(node_type * r) //(Left, Right, Root)
			{
				if (r == NULL)
				return;
				// first recur on left subtree 
				printPostorder(r -> left);
				// then recur on right subtree 
				printPostorder(r -> right);
				// now deal with the node 
				if (r->parent)
					std::cout << r -> value.first << "," << r->value.second << "," << r->parent->value.first << " ";
				else
				std::cout << r -> value.first << "," << r->value.second  << " ";
			}

			/* Print nodes at a given level */
			void printGivenLevel(node_type * r, int level) {
				if (r == NULL)
				return;
				else if (level == 0)
				std::cout << r -> value.first << "," << r->value.second  << " ";
				else // level > 0  
				{
				printGivenLevel(r -> left, level - 1);
				printGivenLevel(r -> right, level - 1);
				}
			}
			void printLevelOrderBFS(node_type * r) {
				int h = height(r);
				for (int i = 0; i <= h; i++)
				printGivenLevel(r, i);
			}

			node_type * iterative_search(T v) const
			{
				if (root == NULL) 
				{
					return root;
				} 
				else 
				{
					node_type * temp = root;
					while (temp != NULL) 
					{
						if (_comp(v, temp->value)) 
							temp = temp->left;
						else if (_comp(temp->value, v)) 
							temp = temp->right;
						else 
							return temp;
					}
				return NULL;
				}
			}

			//Destroy and deallocate the entire tree starting from root r
			void clear(node_type * r)
			{
				if (r == NULL)
					return;
				clear(r->left);
				clear(r->right);
				_alloc.destroy(r);
				_alloc.deallocate(r, 1);
			}

			//Calculates the number of nodes in the tree starting from root r
			size_type size(node_type * r) const
			{
				if (r == NULL)
					return 0;
				else
					return size(r->left) + 1 + size(r->right);
			}

			//Returns the maximum number of elements that the tree can hold
			size_type max_size() const
			{
				return _alloc.max_size();
			}

			//Swap the content of two AVL trees
			void swap(AVLTree &t)
			{
				std::swap(root, t.root);
				std::swap(dummy_past_end, t.dummy_past_end);
				std::swap(_alloc, t._alloc);
				std::swap(_comp, t._comp);
			}

		private:
			allocator_type _alloc;
			value_compare _comp;

	};


}

#endif