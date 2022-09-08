#ifndef BASE_NODE_HPP

#define BASE_NODE_HPP
#include "utils.hpp"

namespace ft {

	template <class NodeType >
	struct BaseNode {

		typedef NodeType *node_pointer;
		typedef const NodeType *const_node_pointer;

		node_pointer parent;
		node_pointer left;
		node_pointer right;

		BaseNode() : parent(NULL), left(NULL), right(NULL) {}

		BaseNode(const BaseNode &ref) : parent(ref._parent), left(ref.left), right(ref.right) {}
		
		BaseNode &operator=(const BaseNode &ref) {
			if (this != &ref)
			{
				this->parent = ref.parent;
				this->left = ref.left;
				this->right = ref.right;
			}
			return *this;
		}
		
		~BaseNode() {}

		static node_pointer min(node_pointer node){
			node_pointer temp = node;

			while (temp->left != NULL){
				temp = temp->left;
			}
			return temp;
		}

		static node_pointer max(node_pointer node){
			node_pointer temp = node;

			while (temp->right != NULL){
				temp = temp->right;
			}
			return temp;
		}

		static const_node_pointer min(const_node_pointer node){
			const_node_pointer temp = node;

			while (temp->left != NULL){
				temp = temp->left;
			}
			return temp;
		}

		static const_node_pointer max(const_node_pointer node){
			const_node_pointer temp = node;

			while (temp->right != NULL){
				temp = temp->right;
			}
			return temp;
		}

		static node_pointer predecessor(node_pointer node){
			node_pointer x = node;
			node_pointer y;
			
			// if (x->parent != NULL && x->parent->parent == x)
      		// 	x = x->right;
			if (x->left != NULL)
				return max(x->left);
			else {
				y = x->parent;
				// while (y != NULL && x == y->left){
				while (x == y->left){
					x = y;
					y = y->parent;
				}
				x = y;
				// return y;
			}
			return x;
		}

		static const_node_pointer predecessor(const_node_pointer node){
			const_node_pointer x = node;
			const_node_pointer y;

			// if (x->parent != NULL && x->parent->parent == x)
      		// 	x = x->right;
			if (x->left != NULL)
				return max(x->left);
			else {
				y = x->parent;
				// while (y != NULL && x == y->left){
				while (x == y->left){
					x = y;
					y = y->parent;
				}
				x = y;
				// return y;
			}
			return x;
		}

		static node_pointer successor(node_pointer node){
			node_pointer x = node;
			node_pointer y;

			if (x->right != NULL)
				return min(x->right);
			else {
				y = x->parent;
				//while (y != NULL && x == y->right){ // y != NULL is redundant if binary tree has header node. NULL->will trigger error.
				while (x == y->right){
					x = y;
					y = y->parent;
				}
				if (x->right != y)
         			x = y;
				// return y;
				return x;
			}
		}

		static const_node_pointer successor(const_node_pointer node){
			const_node_pointer x = node;
			const_node_pointer y;

			if (x->right != NULL)
				return min(x->right);
			else {
				y = x->parent;
				//while (y != NULL && x == y->right){ // y != NULL is redundant if binary tree has header node. NULL->will trigger error.
				while (x == y->right){
					x = y;
					y = y->parent;
				}
				if (x->right != y)
         			x = y;
				// return y;
				return x;
			}
		}
	};
}

#endif
