#ifndef BNODE_HPP

#define BNODE_HPP
#include <limits>
#include <algorithm>
#include <functional>
#include "utils.hpp"
#include "BSTNode.hpp"
#include "BinaryNodeIterator.hpp"

namespace ft {

	template < class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class BSTree {
		public:
			typedef T value_type;
			typedef T& reference;
			typedef T* pointer;
			typedef typename BSTNode<value_type> node_type;
			typedef node_type* node_pointer;
			typedef node_type& node_refeerence;
			typedef typename ft::BinaryNodeIterator<node_type> iterator;
			typedef typename ft::BinaryNodeIterator<const node_type> const_iterator;
			typedef std::size_t size_type;
			typedef Compare key_compare;
			typedef Alloc allocator_type;
			typedef typename Alloc::template rebind< BSTNode<value_type> >::other node_allocator_type;
		
		private:

			node_type 		_header;
			size_type 		_node_count;
			allocator_type	_allocator;
			key_compare		_compare;
			node_allocator_type _node_allocator;

			node_pointer allocate_node(){
				return _node_allocator.allocate(1);
			}

			void deallocate_node(node_pointer ptr, size_type n){
				_node_allocator.deallocate(ptr, n);
			}

			void construct_node(node_pointer ptr, value_type val){
				_node_allocator.construct(ptr, val);
			}

			void destroy_node(node_pointer ptr){
				_node_allocator.destroy(ptr);
			}

			node_pointer _find(node_pointer node, const value_type& key){
				node_pointer temp = (node == &header ? node->parent : node);
				
				while (temp != NULL && (_compare(key, temp->key) == true || _compare(temp->key, key) == true))
				{
					if (_compare(key, temp->key) == true)
						temp = temp->left;
					else
						temp = temp->right;
				}
				return temp;
			}
			
			node_pointer _insert(node_pointer position, const value_type& val){
				node_pointer temp;

				temp = allocate_node();
				construct_node(temp, val);
				return this->_insert(position, temp);
			}

			node_pointer _insert(node_pointer position, node_pointer node){
				node_pointer y = NULL;
				node_pointer x = (position == &_header ? header->parent : position);
				
				while (x != NULL)
				{
					y = x;
					if (_compare(node->key, x->key) == true)
						x = x->left;
					else 
						x = x->right;
				}
				node->parent = y;
				if (y == NULL){
					_header->parent = node;
					_header->left = node;
					_header->right = node;
				}
				else if (_compare(node->key, y->key) == true){
					y->left = node;
					if (_compare(node->key, header.left->key) == true)							
						_header.left = node;
				}
				else{
					y->right = node;
					if (_compare(header.right->key, node->key) == true)
						_header.right = node;
				}
				++_node_count;
				return position;
			}

			void _transplant(node_pointer u, node_pointer v){
				if (u->parent == NULL)
					_header.parent = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				if (v != NULL)
					v->parent = u->parent;
			}

			void _erase(node_pointer node){
				node_pointer y;
				
				if (node->left == NULL){
					if (node == _header.left)
						_header.left = (node.right == NULL ? node->parent : node->right);
					else if (node == _header.right)
						_header.right = node->parent;
					this->transplant_node(node, node->right);
				}
				else if (node->right == NULL){
					if (node == _header.right)
						_header.right = node_type::max(node->left);
					this->transplant_node(node, node->left);
				}
				else {
					y = node_type::min(node);
					if (y->parent != node)
					{
						this->transplant_node(y, y->right);
						y->right = node->right;
						y->right->parent = y;
					}
					this->transplant_node(node, y);
					y->left = node->left;
					y->left->parent = y;
				}
				this->destroy_node(node);
				this->deallocate_node(node, 1);
				--_node_count;
			}

		public:
			explicit BSTree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _header(), _node_count(0), _allocator(alloc), _compare(comp), _node_allocator() {
				_header.parent = NULL;
				_header.left = &_header;
				_header.right = &_header;
			};

			template <class InputIterator>
			BSTree (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _header(), _node_count(0), _allocator(alloc), _compare(comp), _node_allocator() {
				while (first != last){
					this->insert(first);
					++first;
				}
			}

			BSTree(const BSTree &ref) : _header(), _node_count(0), _allocator(ref._allocator), _compare(ref._compare), _node_allocator(ref._node_allocator){
				*this = ref;
			};

			BSTree &operator=(const BSTree &ref){
				if (*this != ref){
					this->clear();	
					for (ref::iterator it = ref.begin(); it != ref.end(); it++)
						this->insert(*it);
				}
				return *this;
			};

			~BSTree(){
				this->clear();
			}

			// Getters
			node_pointer get_root() const{ return _header.parent; }
			node_pointer get_header() const{ return &_header; }
			size_type get_node_count() const{ return _node_count; }
			allocator_type get_allocator() const{ return _allocator; }
			node_allocator_type get_node_allocator() const{ return _node_allocator; }

			// Iterators
			iterator begin() { return iterator(_header.left); }
			const_iterator begin() const { return const_iterator(_header.left); }
			iterator end() { return iterator(&_header)};
			const_iterator end() const { return const_iterator(&_header); }
			reverse_iterator rbegin() { return ft::reverse_iterator(iterator(_header.left)); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(iterator(_header.left)); }
			reverse_iterator rend() { return reverse_iterator(iterator(&_header)); }
			const_reverse_iterator rend() const { return const_reverse_iterator(iterator(&_header)); }

			// Size
			size_type empty() const { return _node_count == 0; }
			size_type size() const { return _node_count; }
			size_type max_size() const { return std::numeric_limits<size_type>::max(); }

			// Element Access
			reference operator[] (const reference val) {
				return (this->find(val))->key;
			}

			// Operations
			iterator find(const value_type& key){
				node_pointer node;

				node = this->_find(_header.parent, key);
				return node ? iterator(node) : this->end();
			}

			const_iterator find (const value_type& k) const{
				node_pointer node;

				node = _find(_header.parent, key);
				return node ? const_iterator(node) : end();
			}

			size_type count(const value_type& key){
				size_type num = 0;
				node_pointer temp = _header.parent;

				while (this->_find(temp, key) != NULL){
					temp = temp->right;
					++num;
				}
				return num;
			}

			iterator lower_bound (const value_type& k){
				iterator it;

				for (it = this->begin(); it != this->end(); it++)
				{
					if (_compare(k, *it) == false)
						break;
				}
				return it;
			}
			
			const_iterator lower_bound (const value_type& k) const{
				const_iterator it;

				for (it = this->begin(); it != this->end(); it++)
				{
					if (_compare(k, *it) == false)
						break;
				}
				return it;
			}

			iterator upper_bound (const value_type& k){
				iterator it;

				for (it = this->begin(); it != this-this->>end(); it++)
				{
					if (_compare(*it, k) == true)
						break;
				}
				return it;
			}

			const_iterator upper_bound (const value_type& k) const{
				const_iterator it;

				for (it = this->begin(); it != this->end(); it++)
				{
					if (_compare(*it, k) == true)
						break;
				}
				return it;
			}

			pair<iterator,iterator> equal_range (const value_type& k){
				iterator lower = this->lower_bound(k)
				iterator upper = this->upper_bound(k);
				return ft::make_pair(lower, upper);
			}

			pair<const_iterator,const_iterator> equal_range (const value_type& k) const{
				const_iterator lower = this->lower_bound(k)
				const_iterator upper = this->upper_bound(k);
				return ft::make_pair(lower, upper);
			}

			// Modifiers
			// ft::pair<iterator,bool> insert (const value_type& val){
			// 	iterator it;
				
			// 	it = this->find(val);
			// 	if (it == this->end())
			// 		return ft::make_pair(this->insert(val), false);
			// 	else
			// 		return ft::make_pair(this->insert(val), true);
			// }

			iterator insert (iterator position, const value_type& val){
				return iterator(this->_insert(position.ptr, val));
			}

			template <class InputIterator>
  			void insert (InputIterator first, InputIterator last){
				while (first != last)
				{
					this->_insert(&_header, first->key);
					++first;
				}
			}

			void swap (map& x){
				std::swap<node_type>(_header, x._header);
				std::swap<size_type>(_node_count, x._node_count);
				std::swap<allocator_type>(_allocator, x._allocator);
				std::swap<key_compare>(_compare, x._compare);
				std::swap<node_allocator_type>(_node_allocator, x._node_allocator);
			}

			void erase (iterator position){
				this->_erase(position.ptr);
			}
	
			size_type erase (const value_type& k){
				size_type num_erased = 0;
				iterator it;

				it = this->find(k);
				while (it != this->end())
				{
					if (_compare(k, *it) == false && _compare(*it, k) == false){
						this->erase(it);
						++num_erased;
					}
					++it;
				}
				return num_erased;
			}

			void erase (iterator first, iterator last){
				while (first != last)
				{
					this->erase(it);
					++first;
				}
			}

			void clear(){
				for (iterator it = this->begin(); it != this->end(); it++)
					this->erase(it);
			}
	};
}

#endif
