#ifndef BNODE_HPP

#define BNODE_HPP
#include <iterator>
#include "utils.hpp"
#include "BaseNode.hpp"

namespace ft {
	template <class NodeType>
	struct BinaryNodeIterator : public std::iterator<std::bidirectional_iterator_tag, NodeType> {
		
		pointer ptr;

		BinaryNodeIterator() : ptr(NULL) {}

		explicit BinaryNodeIterator(pointer *node) : ptr(node) {}

		BinaryNodeIterator(const BinaryNodeIterator &ref): ptr(ref.ptr){}

		BinaryNodeIterator &operator=(const BinaryNodeIterator &ref){
			if (this != *ref)
				this->ptr = ref.ptr;
			return *this;
		}

		~BinaryNodeIterator(){}

		operator BinaryNodeIterator<const NodeType>() const {
			return BinaryNodeIterator<const NodeType>(_pointer);
		}

		reference operator*() const { return ptr->key; }
		pointer operator->() const { return &(ptr->key); }

		friend bool operator==(const BinaryNodeIterator& lhs, const BinaryNodeIterator& rhs) {
			return lhs.ptr == rhs.ptr;
		}

		friend bool operator!=(const BinaryNodeIterator& lhs, const BinaryNodeIterator& rhs) {
			return lhs.ptr != rhs.ptr;
		}
	
		BinaryNodeIterator& operator++() {
			ptr = value_type::successor(ptr);
			return *this;
		}

		BinaryNodeIterator operator++(int) {
			BinaryNodeIterator tmp(*this);
			operator++();
			return tmp;
		}

		BinaryNodeIterator& operator--() {
			ptr = value_type::predecessor(ptr);
			return *this;
		}

		BinaryNodeIterator operator--(int) {
			BinaryNodeIterator tmp(*this);
			operator--();
			return tmp;
		}
	};
}

#endif
