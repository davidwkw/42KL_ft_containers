#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include <iostream>
# include <algorithm>
# include <iterator>
# include "VectorIterator.hpp"
# include "reverse_iterator.hpp"
# include "utils.hpp"

namespace ft {

	template < class T, class Alloc = std::allocator<T> >
	class vector {

		public:
			// typedefs
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef	value_type&	reference;
			typedef const value_type& const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef VectorIterator<value_type> iterator;
			typedef VectorIterator<const value_type> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		private:
			allocator_type			_allocator;
			static const size_type	_expansion_factor = 2;
			pointer					_arr;
			size_type				_size;
			size_type				_capacity;
			
		public:
			// Contructors
			// default
			explicit vector (const allocator_type& alloc = allocator_type())
			: _allocator(alloc), _arr(), _size(), _capacity() {}

			// fill
			explicit vector (size_type n, const value_type& val = value_type(),
								const allocator_type& alloc = allocator_type())
			: _allocator(alloc), _arr(_allocator.allocate(n)), _size(), _capacity(n){
				for (size_type i = 0; i < n; i++)
					push_back(val);
			}

			// range
			// default template arguments for a function template are a C++11 extension
			template < class InputIterator >
        	vector (InputIterator first, InputIterator last,
                	const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value, void>::type* = NULL) : _allocator(alloc), _arr(), _size(), _capacity() {
				this->reserve(std::distance(first, last));
				while (first != last)
				{
					this->push_back(*first);
					++first;
				}
			}

			// copy
			vector(const vector &ref) : _allocator(ref._allocator), _arr(_allocator.allocate(ref._capacity)), _size(), _capacity(ref._capacity) {
				for (size_type i = 0; i < ref._size; i++)
					this->push_back(ref[i]);
			}

			// destructor
			~vector() {
				this->clear();
				_allocator.deallocate(_arr, _capacity);
			}

			// assignment
			vector& operator=(const vector& ref) {
				if (this != &ref){
					this->clear();
					this->reserve(ref._capacity);
					for (size_type i = 0; i < ref._size; i++)
						this->push_back(ref._arr[i]);
				}
				return *this;
			};

			// Iterators
			iterator begin() { return iterator(_arr); }
			const_iterator begin() const { return const_iterator(_arr); }
			iterator end() { return iterator(_arr + _size); }
			const_iterator end() const { return const_iterator(_arr + _size); }
			reverse_iterator rbegin() { return reverse_iterator(this->end()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(this->end()); }
			reverse_iterator rend() { return reverse_iterator(this->begin()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(this->begin()); }

			// Capacity
			size_type size() const { return _size; };
			size_type max_size() const { return _allocator.max_size(); };

			void resize (size_type n, value_type val = value_type()) {
				if (n < _size)
				{
					for (size_type i = n; i < _size; i++)
						_allocator.destroy(&_arr[i]);
					_size = n;
				}
				else if (n > _size)
				{
					if (n > _capacity)
						this->reserve(n);
					for (size_type i = _size; i < n; i++)
						this->push_back(val);
				}
			}

			size_type capacity() const { return _capacity; };

			bool empty() const { return _size == 0; };

			void reserve (size_type n) {
				pointer temp;

				if (n > _capacity)
				{
					temp = _allocator.allocate(n, _arr);
					for (size_type i = 0; i < _size; i++)
					{
						_allocator.construct(&temp[i], _arr[i]);
						_allocator.destroy(&_arr[i]);
					}
					_allocator.deallocate(_arr, _capacity);
					_arr = temp;
					_capacity = n;
				}
			}

			// Element access:
			reference operator[](size_type pos) { return _arr[pos]; };

			const_reference operator[](size_type pos) const { return _arr[pos]; };

			reference at(size_type pos) {
				if (pos >= _size)
					throw std::out_of_range("Index out of range");
				return _arr[pos];
			};

			const_reference at(size_type pos) const {
				if (pos >= _size)
					throw std::out_of_range("Index out of range");
				return _arr[pos];
			};

			reference front() { return *_arr; }

			const_reference front() const { return *_arr; }

			reference back() { return _arr[_size - 1]; }

			const_reference back() const { return _arr[_size - 1]; }

			value_type* data(){ return _arr; }

			const value_type* data() const{ return _arr; }

			// modifiers

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, void>::type* = NULL) {
				this->clear();
				size_type n = std::distance(first, last);
				this->reserve(n);
				while (first != last)
				{
					this->push_back(*first);
					++first;
				}
			}

			void assign (size_type n, const value_type& val) {
				this->clear();
				if (n > _capacity)
					this->reserve(n);
				for (size_type i = 0; i < n; i++)
					this->push_back(val);
			}

			void push_back (const value_type& val){

				if (_size + 1 >= _capacity)
					this->reserve((_size + 1) * _expansion_factor);
				_allocator.construct(&_arr[_size], val);
				++_size;
			}

			void pop_back(){
				_allocator.destroy(&_arr[_size - 1]);
				--_size;
			}

			iterator insert (iterator position, const value_type& val){
				this->insert(position, 1, val);
				return position;
			}

    		void insert (iterator position, size_type n, const value_type& val){
				vector<T> temp(n, val);
				this->insert(position, temp.begin(), temp.end());
			}

			template <class InputIterator>
   			void insert (iterator position, InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, void>::type* = NULL){
				size_type	num_elements;
				size_type	elems_to_shift;
				size_type	index;

				num_elements = std::distance(first, last);
				index = position - iterator(_arr);
				elems_to_shift = this->end() - position;
				if ((_size + num_elements) > _capacity)
					this->reserve((_capacity + num_elements) * _expansion_factor);
				if (index == _size)
				{
					while (first != last)
					{
						this->push_back(*first);
						++first;
					}
				}
				else {
					while (elems_to_shift){
						_arr[index + num_elements + elems_to_shift - 1] = _arr[index + elems_to_shift - 1];
						--elems_to_shift;
					}
					while(first != last)
					{
						_arr[index] = *first;
						++first;
						++index;
						++_size;
					}
				}
			}

			iterator erase (iterator position) {
				return  this->erase(position, position + 1);
			}

			iterator erase (iterator first, iterator last) {
				iterator	ret;
				size_type	num_elems;

				ret = first;
				num_elems = std::distance(first, last);
				while (last != this->end())
				{
					*first = *last;
					++first;
					++last;
				}
				for (size_type i = 0; i < num_elems; ++i)
					this->pop_back();
				return (ret);
			}

			void swap (vector& x) {
				std::swap<pointer>(_arr, x._arr);
				std::swap<size_type>(_size, x._size);
				std::swap<size_type>(_capacity, x._capacity);
			}

			void clear()
			{
				this->erase(this->begin(), this->end());
			}

			// Allocator
			allocator_type get_allocator() const { return _allocator; }

		// Non-member function overloads
		// relational operators

		friend bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			if (lhs.size() == rhs.size())
				return equal(lhs.begin(), lhs.end(), rhs.begin());
			return false;
		}

		friend bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return !(lhs == rhs);
		}

		friend bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		friend bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return !(rhs < lhs);
		}

		friend bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return rhs < lhs;
		}

		friend bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
			return !(lhs < rhs);
		}
	};

	// swap
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}
}

#endif
