#ifndef BINARY_NODE_ITERATOR_HPP

#define BINARY_NODE_ITERATOR_HPP
#include "utils.hpp"
#include "BaseNode.hpp"
#include "BSTNode.hpp"
#include <iostream>

namespace ft {

	template <class NodeType>
	struct BinaryNodeIterator{
		
		typedef NodeType node_type;
		typedef node_type *node_pointer;
		typedef typename node_type::value_type value_type;
		typedef typename ft::conditional<is_const<node_type>::value, typename node_type::const_pointer, typename node_type::pointer>::type pointer;
		typedef typename ft::conditional<is_const<node_type>::value, typename node_type::const_reference, typename node_type::reference>::type reference;
		typedef std::ptrdiff_t  difference_type;
		typedef std::bidirectional_iterator_tag  iterator_category;

		node_pointer ptr;

		BinaryNodeIterator() : ptr(){}

		BinaryNodeIterator(node_pointer node) : ptr(node){}

		BinaryNodeIterator(const BinaryNodeIterator &ref){
			*this = ref;
		}

		BinaryNodeIterator &operator=(const BinaryNodeIterator &ref){
			if (this != &ref)
				this->ptr = ref.ptr;
			return *this;
		}

		~BinaryNodeIterator(){}

		operator BinaryNodeIterator<const NodeType>() const{
			return BinaryNodeIterator<const NodeType>(ptr);
		}

		reference operator*() const{ return ptr->key; }
		pointer operator->() const{ return &(ptr->key); }

		friend bool operator==(const BinaryNodeIterator& lhs, const BinaryNodeIterator& rhs) {
			return lhs.ptr == rhs.ptr;
		}

		friend bool operator!=(const BinaryNodeIterator& lhs, const BinaryNodeIterator& rhs) {
			return lhs.ptr != rhs.ptr;
		}
	
		BinaryNodeIterator& operator++(){
			ptr = node_type::successor(ptr);
			return *this;
		}

		BinaryNodeIterator operator++(int){
			BinaryNodeIterator tmp(*this);
			operator++();
			return tmp;
		}

		BinaryNodeIterator& operator--(){
			ptr = node_type::predecessor(ptr);
			return *this;
		}

		BinaryNodeIterator operator--(int){
			BinaryNodeIterator tmp(*this);
			operator--();
			return tmp;
		}
	};

	template<typename T>
	bool operator==(const BinaryNodeIterator<T>& x,
			const BinaryNodeIterator<const T>& y){ 
		return x.ptr == y.ptr; 
	}

	template<typename T>
	bool operator!=(const BinaryNodeIterator<T>& x,
			const BinaryNodeIterator<const T>& y){
		return x.ptr != y.ptr;
	}

	// template <class T>
	// struct BinaryNodeIterator{
		
	// 	typedef BSTNode<T> node_type;
	// 	typedef typename node_type::node_pointer node_pointer;
	// 	typedef T value_type;
	// 	typedef T *pointer;
	// 	typedef T &reference;
	// 	typedef std::ptrdiff_t  difference_type;
	// 	typedef std::bidirectional_iterator_tag  iterator_category;

	// 	node_pointer ptr;

	// 	BinaryNodeIterator() : ptr(){}

	// 	BinaryNodeIterator(node_pointer node) : ptr(node){}

	// 	BinaryNodeIterator(const BinaryNodeIterator &ref){
	// 		*this = ref;
	// 	}

	// 	BinaryNodeIterator &operator=(const BinaryNodeIterator &ref){
	// 		if (this != &ref)
	// 			this->ptr = ref.ptr;
	// 		return *this;
	// 	}

	// 	~BinaryNodeIterator(){}

	// 	reference operator*() const{ return ptr->key; }
	// 	pointer operator->() const{ return &(ptr->key); }

	// 	bool operator==(const BinaryNodeIterator& rhs) {
	// 		return this->ptr == rhs.ptr;
	// 	}

	// 	bool operator!=(const BinaryNodeIterator& rhs) {
	// 		return this->ptr != rhs.ptr;
	// 	}
	
	// 	BinaryNodeIterator& operator++(){
	// 		ptr = node_type::successor(ptr);
	// 		return *this;
	// 	}

	// 	BinaryNodeIterator operator++(int){
	// 		BinaryNodeIterator tmp(*this);
	// 		operator++();
	// 		return tmp;
	// 	}

	// 	BinaryNodeIterator& operator--(){
	// 		ptr = node_type::predecessor(ptr);
	// 		return *this;
	// 	}

	// 	BinaryNodeIterator operator--(int){
	// 		BinaryNodeIterator tmp(*this);
	// 		operator--();
	// 		return tmp;
	// 	}
	// };

	// template <class T>
	// struct ConstBinaryNodeIterator{
		
	// 	typedef BSTNode<T> node_type;
	// 	typedef typename node_type::const_node_pointer node_pointer;
	// 	typedef T value_type;
	// 	typedef const T *pointer;
	// 	typedef const T &reference;
	// 	typedef std::ptrdiff_t  difference_type;
	// 	typedef std::bidirectional_iterator_tag  iterator_category;

	// 	typedef BinaryNodeIterator<T> iterator;

	// 	node_pointer ptr;

	// 	ConstBinaryNodeIterator() : ptr(){}

	// 	explicit ConstBinaryNodeIterator(node_pointer node) : ptr(node){}

	// 	ConstBinaryNodeIterator(const iterator& it) : ptr(it.ptr) {}

	// 	ConstBinaryNodeIterator(const ConstBinaryNodeIterator &ref){
	// 		*this = ref;
	// 	}

	// 	ConstBinaryNodeIterator &operator=(const ConstBinaryNodeIterator &ref){
	// 		if (this != &ref)
	// 			this->ptr = ref.ptr;
	// 		return *this;
	// 	}

	// 	~ConstBinaryNodeIterator(){}

	// 	reference operator*() const{ return ptr->key; }
	// 	pointer operator->() const{ return &(ptr->key); }

	// 	bool operator==(const ConstBinaryNodeIterator& rhs) {
	// 		return this->ptr == rhs.ptr;
	// 	}

	// 	bool operator!=(const ConstBinaryNodeIterator& rhs) {
	// 		return this->ptr != rhs.ptr;
	// 	}
	
	// 	ConstBinaryNodeIterator& operator++(){
	// 		ptr = node_type::successor(ptr);
	// 		return *this;
	// 	}

	// 	ConstBinaryNodeIterator operator++(int){
	// 		ConstBinaryNodeIterator tmp(*this);
	// 		operator++();
	// 		return tmp;
	// 	}

	// 	ConstBinaryNodeIterator& operator--(){
	// 		ptr = node_type::predecessor(ptr);
	// 		return *this;
	// 	}

	// 	ConstBinaryNodeIterator operator--(int){
	// 		ConstBinaryNodeIterator tmp(*this);
	// 		operator--();
	// 		return tmp;
	// 	}
	// };

	// template<typename T>
	// bool operator==(const BinaryNodeIterator<T>& x,
	// 		const ConstBinaryNodeIterator<T>& y){ 
	// 	return x.ptr == y.ptr; 
	// }

	// template<typename T>
	// bool operator!=(const BinaryNodeIterator<T>& x,
	// 		const ConstBinaryNodeIterator<T>& y){
	// 	return x.ptr != y.ptr;
	// }

}

#endif
