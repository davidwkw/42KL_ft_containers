#ifndef BST_NODE_HPP

#define BST_NODE_HPP
#include "utils.hpp"
#include "BaseNode.hpp"

namespace ft {

	template < class T >
	struct BSTNode : public BaseNode< BSTNode<T> > {

		typedef T value_type;
		typedef const T const_value_type; 
		typedef T *pointer;
		typedef const T *const_pointer;
		typedef	T &reference;
		typedef	const T &const_reference;

		value_type key;

		BSTNode(const value_type &val = value_type()) : BaseNode< BSTNode<T> >(), key(val){}

		BSTNode(const BSTNode &ref) : BaseNode< BSTNode<T> >(), key(ref.key){
			this->parent = ref.parent;
			this->left = ref.left;
			this->right = ref.right;
		}
		
		BSTNode &operator=(const BSTNode &ref) {
			if (this != &ref)
			{
				this->key = ref.key;
				this->parent = ref.parent;
				this->left = ref.left;
				this->right = ref.right;
			}
			return *this;
		}

		~BSTNode() {}
	};
}

#endif
