#ifndef BSTNODE_HPP

#define BSTNODE_HPP
#include "utils.hpp"
#include "BaseNode.hpp"

namespace ft {

	template < class T >
	struct BSTNode : public ft::BaseNode< BSTNode<T> > {

		typedef T value_type;

		value_type key;

		BSTNode(const value_type &val = value_type()) : key(val), parent(NULL), left(NULL), right(NULL) {}

		BSTNode(const BSTNode &ref) : _key(ref._key), parent(ref.parent), left(ref.left), right(ref.right) {}
		
		BSTNode &operator=(const BNode &ref) {
			if (this != &ref)
			{
				this->_key = ref._key;
				this->parent = ref.parent;
				this->left = ref.left;
				this->right = ref.right;
			}
			return *this;
		}

		~BSTNode() {}
	};
};

#endif
