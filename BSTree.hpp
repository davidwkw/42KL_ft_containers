#ifndef BSTREE_HPP

#define BSTREE_HPP
#include <limits>
#include <algorithm>
#include <functional>
#include "utils.hpp"
#include "BSTNode.hpp"
#include "BinaryNodeIterator.hpp"
#include "reverse_iterator.hpp"

namespace ft {

	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class BSTree {
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef Compare key_compare;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef BSTNode<value_type> node_type;
			typedef typename Alloc::template rebind< node_type >::other node_allocator_type;
			typedef typename node_allocator_type::reference node_reference;
			typedef typename node_allocator_type::const_reference const_node_reference;
			typedef typename node_allocator_type::pointer node_pointer;
			typedef typename node_allocator_type::const_pointer const_node_pointer;
			typedef BinaryNodeIterator<node_type> iterator;
			typedef BinaryNodeIterator<const node_type> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type difference_type;
			typedef std::size_t size_type;
		
		private:

			node_pointer 	_header;
			size_type 		_node_count;
			allocator_type	_allocator;
			key_compare		_compare;
			node_allocator_type _node_allocator;

			node_pointer allocate_node(){
				return _node_allocator.allocate(1);
			}

			void deallocate_node(node_pointer ptr){
				_node_allocator.deallocate(ptr, 1);
			}

			void construct_node(node_pointer ptr, value_type val){
				_node_allocator.construct(ptr, val);
			}

			void destroy_node(node_pointer ptr){
				_node_allocator.destroy(ptr);
			}

			node_pointer _find(node_pointer node, const value_type& key){ 
				node_pointer temp = (node == _header ? node->parent : node);
				
				while (temp != NULL && (_compare(key, temp->key) == true || _compare(temp->key, key) == true))
				{
					if (_compare(key, temp->key) == true)
						temp = temp->left;
					else
						temp = temp->right;
				}
				if (temp == NULL)
					temp = _header;
				return temp;
			}

			const_node_pointer _find(node_pointer node, const value_type& key) const{ 
				const_node_pointer temp = (node == _header ? node->parent : node);
				
				while (temp != NULL && (_compare(key, temp->key) == true || _compare(temp->key, key) == true))
				{
					if (_compare(key, temp->key) == true)
						temp = temp->left;
					else
						temp = temp->right;
				}
				if (temp == NULL)
					temp = _header;
				return temp;
			}
			
			node_pointer _insert(node_pointer position, const value_type& val){
				node_pointer temp;

				temp = allocate_node();
				construct_node(temp, val);
				return this->_insert(temp, position);
			}

			node_pointer _insert(node_pointer node, node_pointer position){
				node_pointer x = (position == _header ? _header->parent : position);
				node_pointer y = _header;
				
				// Finding where the parent is..
				while (x != NULL)
				{
					y = x;
					if (_compare(node->key, x->key) == true)
						x = x->left;
					else 
						x = x->right;
				}
				node->parent = y;
				// Finding where to place child..
				if (y == _header){
					_header->parent = node;
					_header->left = node;
					_header->right = node;
				}
				else if (_compare(node->key, y->key) == true){
					y->left = node;
					if (_compare(node->key, _header->left->key) == true)							
						_header->left = node;
				}
				else{
					y->right = node;
					if (_compare(_header->right->key, node->key) == true)
						_header->right = node;
				}
				++_node_count;
				return node;
			}

			void _transplant(node_pointer u, node_pointer v){
				if (u->parent == _header)
					_header->parent = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				if (v != NULL)
					v->parent = u->parent;
			}

			void _erase(node_pointer node){
				node = (node == _header ? _header->parent : node);
				node_pointer y;
				
				if (node->left == NULL){
					if (node == _header->left){
						_header->left = node_type::successor(node);
						if (_header->left == _header)
							_header->right = _header;
					}
					this->_transplant(node, node->right);
				}
				else if (node->right == NULL){
					if (node == _header->right)
						_header->right = node_type::predecessor(node);
					this->_transplant(node, node->left);
				}
				else {
					y = node_type::min(node->right);
					if (y->parent != node)
					{
						this->_transplant(y, y->right);
						y->right = node->right;
						y->right->parent = y;
					}
					this->_transplant(node, y);
					y->left = node->left;
					y->left->parent = y;
				}
				this->destroy_node(node);
				this->deallocate_node(node);
				--_node_count;
			}

			node_pointer _lower_bound (const value_type& k){
				node_pointer x = _header->parent;
				node_pointer y = _header;

				while (x != NULL){
					if(_compare(k, x->key) == true){
						y = x;
						x = x->left;
					}
					else if (_compare(x->key, k) == false)
						return x;
					else
						x = x->right;	
				}
				return y;
			}

			const_node_pointer _lower_bound (const value_type& k) const{
				const_node_pointer x = _header->parent;
				const_node_pointer y = _header;

				while (x != NULL){
					if(_compare(k, x->key) == true){
						y = x;
						x = x->left;
					}
					else if (_compare(x->key, k) == false)
						return x;
					else
						x = x->right;	
				}
				return y;
			}

			node_pointer _upper_bound (const value_type& k){
				node_pointer x = _header->parent;
				node_pointer y = _header;

				while (x != NULL){
					if (_compare(k, x->key) == true){
						y = x;
                		x = x->left;
					}
					else
						x = x->right;
				}
				return y;				
			}

			const_node_pointer _upper_bound (const value_type& k) const{
				const_node_pointer x = _header->parent;
				const_node_pointer y = _header;

				while (x != NULL){
					if (_compare(k, x->key) == true){
						y = x;
                		x = x->left;
					}
					else
						x = x->right;
				}
				return y;				
			}

		public:
			explicit BSTree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _header(), _node_count(0), _allocator(alloc), _compare(comp), _node_allocator() {
				_header = allocate_node();
				construct_node(_header, value_type());
				_header->parent = NULL;
				_header->left = _header;
				_header->right = _header;
			};

			template <class InputIterator>
			BSTree (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _header(), _node_count(0), _allocator(alloc), _compare(comp), _node_allocator() {
				_header = allocate_node();
				construct_node(_header, value_type());
				_header->parent = NULL;
				_header->left = _header;
				_header->right = _header;
				this->insert(first, last);
			}

			BSTree(const BSTree &ref) : _header(), _node_count(ref._node_count), _allocator(ref._allocator), _compare(ref._compare), _node_allocator(ref._node_allocator){
				_header = allocate_node();
				construct_node(_header, value_type());
				_header->parent = NULL;
				_header->left = _header;
				_header->right = _header;
				*this = ref;
			}

			BSTree &operator=(const BSTree &ref){
				if (*this != ref){
					this->clear();	
					this->insert(ref.begin(), ref.end());
				}
				return *this;
			}

			~BSTree(){
				this->clear();
				destroy_node(_header);
				deallocate_node(_header);
			}

			// Getters
			node_pointer get_root() const{ return _header->parent; }
			size_type get_node_count() const{ return _node_count; }
			allocator_type get_allocator() const{ return _allocator; }
			key_compare		get_compare() const{ return _compare; }
			node_allocator_type get_node_allocator() const{ return _node_allocator; }

			// Iterators
			iterator begin() { return iterator(_header->left); }
			const_iterator begin() const { return const_iterator(static_cast<const_node_pointer>(_header->left)); }
			iterator end() { return iterator(_header); }
			const_iterator end() const { return const_iterator(static_cast<const_node_pointer>(_header)); }
			reverse_iterator rbegin() { return reverse_iterator(this->end()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }
			reverse_iterator rend() { return reverse_iterator(this->begin()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

			// Size
			size_type empty() const { return _node_count == 0; }
			size_type size() const { return _node_count; }
			size_type max_size() const { return std::numeric_limits<size_type>::max(); }

			// Element Access
			reference operator[] (reference val) {
				return (this->find(val))->key;
			}

			// Operations
			iterator find(iterator position, const value_type& key){
				node_pointer node;

				node = this->_find(position.ptr, key);
				return iterator(node);
			}

			const_iterator find (iterator position, const value_type& key) const{
				const_node_pointer node;

				node = this->_find(position.ptr, key);
				return const_iterator(node);
			}

			iterator find(const value_type& key){
				node_pointer node;

				node = this->_find(_header->parent, key);
				return iterator(node);
			}

			const_iterator find (const value_type& key) const{
				const_node_pointer node;

				node = this->_find(_header->parent, key);
				return const_iterator(node);
			}

			size_type count(const value_type& key) const{
				size_type num = 0;
				node_pointer temp = _header->parent;

				while (this->_find(key, temp) != _header){
					temp = temp->right;
					++num;
				}
				return num;
			}

			iterator lower_bound (const value_type& k){
				return iterator(this->_lower_bound(k));
			}
			
			const_iterator lower_bound (const value_type& k) const{
				return const_iterator(this->_lower_bound(k));
			}

			iterator upper_bound (const value_type& k){
				return iterator(this->_upper_bound(k));
			}

			const_iterator upper_bound (const value_type& k) const{
				return const_iterator(this->_upper_bound(k));
			}

			// Modifiers
			iterator insert (iterator position, const value_type& val){
				return iterator(this->_insert(position.ptr, val));
			}

			template <class InputIterator>
  			void insert (InputIterator first, InputIterator last){
				while (first != last)
				{
					this->_insert(_header, *first);
					++first;
				}
			}

			void swap (BSTree& x){
				std::swap<node_pointer>(_header, x._header);
				std::swap<size_type>(_node_count, x._node_count);
				std::swap<allocator_type>(_allocator, x._allocator);
				std::swap<key_compare>(_compare, x._compare);
				std::swap<node_allocator_type>(_node_allocator, x._node_allocator);
			}
	
			size_type erase (const value_type& k){
				size_type num_erased = 0;
				iterator it;

				it = this->find(k);
				while (it != this->end() && (_compare(k, *it) == false && _compare(*it, k) == false)){
					this->erase(it++);
					++num_erased;
				}
				return num_erased;
			}

			void erase (iterator position){
				this->_erase(position.ptr);
			}

			void erase (iterator first, iterator last){
				while (first != last)
					this->erase(first++);
			}

			void clear(){
				this->erase(this->begin(), this->end());
			}

			friend bool operator== ( const BSTree& lhs, const BSTree& rhs ){
				return lhs._node_count == rhs._node_count && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
			}
			
			friend bool operator!= ( const BSTree& lhs, const BSTree& rhs ){
				return !(lhs == rhs);
			}
			
			friend bool operator<  ( const BSTree& lhs, const BSTree& rhs ){
				return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
			}
			
			friend bool operator<= ( const BSTree& lhs, const BSTree& rhs ){
				return !(rhs < lhs);
			}
			
			friend bool operator>  ( const BSTree& lhs, const BSTree& rhs ){
				return rhs < lhs;
			}
			
			friend bool operator>= ( const BSTree& lhs, const BSTree& rhs ){
				return !(lhs < rhs);
			}
	};
}

#endif
