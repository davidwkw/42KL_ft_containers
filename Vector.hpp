#ifndef VECTOR_HPP

# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include <iostream>
# include "Iterator.hpp"

namespace ft {

	template < class T, class Alloc = std::allocator<T> >
	class vector {
		public:
			// typedefs
			typedef typename T value_type;
			typedef typename Alloc allocator_type;
			typedef std::size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef	value_type&	reference;
			typedef const value_type& const_reference;
			typedef Alloc::pointer pointer;
			typedef Alloc::const_pointer const_pointer;
			typedef ft::Iterator<T> iterator;
			typedef ft::Iterator<const T> const_iterator;
			typedef std::reverse_iterator<iterator> reverse_iterator;
			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		private:
			static const size_type	_expansion_factor = 2;
			pointer					_arr;
			size_type				_size;
			size_type				_capacity;
			allocator_type			_allocator;
		public:
			// Contructors
			// default
			explicit vector (const allocator_type& alloc = allocator_type())
			: _arr(NULL), _size(0), _capacity(0), _allocator(alloc) {}

			// fill
			explicit vector (size_type n, const value_type& val = value_type(),
								const allocator_type& alloc = allocator_type())
			: _arr(alloc.allocate(n)), _size(0), _capacity(n), _allocator(alloc) {
				for (size_t i = 0; i < _size; i++)
					push_back(val);
			}

			// range
			template <class InputIterator>
        	vector (InputIterator first, InputIterator last,
                	const allocator_type& alloc = allocator_type()) : _size(0), _allocator(alloc) {
				reserve(std::distance(first, last));
				while (first != last)
				{
					push_back(*first);
					++first;
				}
			}

			// copy
			vector(const vector &ref) : _arr(alloc.allocate(ref._capacity)), _size(0), _capacity(ref._capacity), _allocator(ref._allocator) {
				for (size_t i = 0; i < _size; i++)
					push_back(ref._arr[i]);
			}

			// destructor
			~vector() {
				clear();
				_allocator.deallocate(_arr, _capacity);
			}

			// assignment
			vector& operator=(const vector& x) {
				if (this != &x)
				{
					clear();
					if (x._size > _capacity)
						reserve(_capacity);
					for (size_t i = 0; i < x._size; i++)
						push_back(ref._arr[i]);
					_size = x._size;
				}
				return *this;
			};

			iterator begin() { return iterator(_arr); }
			const_iterator begin() const { return const_iterator(_arr); }
			iterator end() { return iterator(_arr + _size); }
			const_iterator end() const { return const_iterator(_arr + _size); }
			reverse_iterator rbegin() { return reverse_iterator(iterator(_arr)); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(iterator(_arr)); }
			reverse_iterator rend() { return reverse_iterator(iterator(_arr + _size)); }
			const_reverse_iterator rend() const { return const_reverse_iterator(iterator(_arr + _size)); }

			// Capacity
			size_type size() const { return _size; };

			size_type max_size() const { return _allocator.max_size; };

			void resize (size_type n, value_type val = value_type()) {
				if (n < _size)
				{
					for (size_t i = n; i < _size; i++)
						_allocator.destroy(&_arr[i]);
				}
				else if (n > _size)
				{
					if (n > _capacity)
						reserve(n);
					for (size_t i = _size; i < n, i++)
						push_back(val);
				}
				_size = n;
			}

			size_type capacity() const { return _capacity; };

			bool empty() const { return _size == 0; };

			void reserve (size_type n) {
				pointer* temp;

				if (n > _capacity)
				{
					temp = _allocator.allocate(n, _arr);
					for (int i = 0; i < _size; i++)
					{
						_allocator.construct(&temp[i], _arr[i]);
						_allocator.destroy(&arr[i]);
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
					throw std::out_of_range("vector::_M_range_check");
				return _arr[pos];
			};

			const_reference at(size_type pos) const {
				if (pos >= _size)
					throw std::out_of_range("vector::_M_range_check");
				return _arr[pos];
			};

			reference front() { return *_arr };

			const_reference front() const { return *_arr };

			reference back() { return _arr[_size - 1]};

			const_reference back() const { return _arr[_size - 1]};

			// modifiers

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last) {
				clear();
				size_type n = std::distance<value_type>(first, last);
				if (n > _capacity)
					reserve(n);
				while (first != last)
				{
					push_back(*first);
					++first;
				}
			}

			void assign (size_type n, const value_type& val) {
				clear();
				if (n > _capacity)
					reserve(n);
				for (int i = 0; i < n; ++i)
					push_back(val);
			}

			void push_back (const value_type& val) {
				if (_size >= _capacity)
					reserve(_capacity * _expansion_factor);
				_allocator.construct(&_arr[_size], val);
				++_size;
			}

			void pop_back() {
				_allocator.destroy(&_arr[_size - 1]);
				--_size;
			}

			iterator insert (iterator position, const value_type& val) {
			}

    		void insert (iterator position, size_type n, const value_type& val);


			template <class InputIterator>
   			void insert (iterator position, InputIterator first, InputIterator last) {
				size_type	num_elements;
				size_type	shift_num;
				size_type	index;

				num_elements = std::distance(first, last);
				index = position - iterator(_arr);
				shift_num = _size - index;
				if (_size >= _capacity)
					reserve((_capacity + num_elements) * _expansion_factor);
				for (size_type i = index; i < shift_num; ++i)

			}

			void clear()
			{
				for (size_t i = 0; i < _size; i++)
					_allocator.destroy(&_array[i]);
				_size = 0;
			}

			// Allocator
			allocator_type get_allocator() const { return _allocator; }
	};
}

#endif
