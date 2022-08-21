#ifndef MAP_HPP
#define MAP_HPP

# include <memory>
# include <stdexcept>
# include <iostream>
# include <algorithm>
# include "BinaryNodeIterator.hpp"
# include "BSTree.hpp"
# include "reverse_iterator.hpp"
# include "utils.hpp"

namespace ft {

	template < class Key,                                     // map::key_type
           class T,                                       // map::mapped_type
           class Compare = std::less<Key>,                     // map::key_compare
           class Alloc = std::allocator< ft::pair<const Key,T> >    // map::allocator_type
           >
	class map {
		public:
			typedef Key	key_type;
			typedef T mapped_type;
			typedef ft::pair<const Key, T> value_type;
			typedef Compare key_compare;
			typedef Alloc allocator_type;
			typedef	allocator_type::reference reference;
			typedef allocator_type::const_reference const_reference;
			typedef allocator_type::pointer pointer;
			typedef allocator_type::const_pointer const_pointer;
			typedef ft::BinaryNodeIterator< BSTNode<value_type> > iterator;
			typedef ft::BinaryNodeIterator< BSTNode<value_type> > const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef ft::iterator_traits<iterator>::difference_type difference_type;
			typedef std::size_t size_type;

		private:
			typename ft::BSTree< value_type, value_compare, Alloc > _base;

		public:
			class value_compare : public ft::binary_function<value_type, value_type, bool> {
				protected:
					friend class map<Key, T, Compare, Alloc>;
					Compare comp;

					value_compare(Compare comparator) : comp(comparator) {}

				public:
					bool operator()(const value_type& __x, const value_type& __y) const
					{ return comp(__x.first, __y.first); }
     		};

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _base(value_compare(comp, alloc)){}

			template <class InputIterator>
			map (InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) : _base(value_compare(comp, alloc)){
					_base.insert(first, last);
			}

			map (const map& ref) : _base(value_compare(map._base._compare, map._base._allocator)){
				*this = ref;
			}

			map &operator=(const map& ref){
				if (*this != ref){
					_base.clear();	
					for (ref::iterator it = ref.begin(); it != ref.end(); it++)
						_base.insert(it);
				}
				return *this;
			}

			~map(){
				_base.clear();
			}

			// Iterators
			iterator begin(){ return _base.begin(); }
			const_iterator begin() const{ return _base.begin(); }
			iterator end(){ return _base.end(); }
			const_iterator end() const{ return _base.end(); }
			reverse_iterator rbegin(){ return _base.rbegin(); }
			const_reverse_iterator rbegin() const{ return _base.rbegin(); }
			reverse_iterator rend(){ return _base.rend(); }
			const_reverse_iterator rend() const{ return _base.rend(); }

			// Capacity
			size_type size() const{ return _base.size(); }
			size_type max_size() const{ return _base.max_size();}
			bool empty() const{ return _base.empty(); }

			// Element access
			mapped_type& operator[] (const key_type& k){
				return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second
				
			}

			// Modifiers 
			ft::pair<iterator,bool> insert (const value_type& val){
				ft::pair<iterator,bool> ret;
				iterator it;
				
				it = _base.find(val);
				if (it == _base.end()){
					it = iterator(_base.insert(val));
					return ft::make_pair(it, true);
				}
				else
					return ft::make_pair(it, false);
			}

			iterator insert (iterator position, const value_type& val){
				return this->insert(val).first;
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last){
				_base.insert(first, last);
			}


			void erase (iterator position){
				_base.erase(position);
			}

			size_type erase (const key_type& k){
				return _base.erase(ft::make_pair(k, mapped_type()));
			}

			void erase (iterator first, iterator last){
				_base.erase(first, last);
			}

			void swap (map& x){
				_base.swap(x._base);
			}

			void clear(){
				_base.clear();
			}

			// Operations
			iterator find (const key_type& k){
				return _base.find(ft::make_pair(k, mapped_type()));
			}

			const_iterator find (const key_type& k) const{
				return _base.find(ft::make_pair(k, mapped_type()));
			}

			size_type count (const key_type& k) const{
				return this->find(k) == this->end() ? 0 : 1;
			}

			iterator lower_bound (const key_type& k){
				return _base.lower_bound(ft::make_pair(k, mapped_type()));
			}

			const_iterator lower_bound (const key_type& k) const{
				return _base.lower_bound(ft::make_pair(k, mapped_type()));
			}

			iterator upper_bound (const key_type& k){
				return _base.upper_bound(ft::make_pair(k, mapped_type()));
			}

			const_iterator upper_bound (const key_type& k) const{
				return _base.upper_bound(ft::make_pair(k, mapped_type()));
			}

			pair<const_iterator,const_iterator>	equal_range (const key_type& k) const{
				return _base.equal_range(ft::make_pair(k, mapped_type()));
			}

			pair<iterator,iterator>	equal_range (const key_type& k){
				return _base.equal_range(ft::make_pair(k, mapped_type()));
			}

			// Observers 
			key_compare key_comp() const{ return key_compare(); }

			value_compare value_comp() const{ return value_compare(key_comp()); }

			// Allocator
			allocator_type get_allocator() const{
				return _base.get_allocator();
			}
	};
}
#endif
