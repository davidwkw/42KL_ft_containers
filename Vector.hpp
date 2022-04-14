#ifndef VECTOR_HPP

# define VECTOR_HPP

# include <memory>
# include <stdexcept>
# include <iterator>

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
			typedef typename Alloc::pointer pointer;
			typedef typename Alloc::const_pointer const_pointer;
			typedef typename std::iterator<std::random_access_iterator_tag, T> iterator;
			typedef typename std::iterator<std::random_access_iterator_tag, T> const_iterator;
			typedef std::reverse_iterator<iterator> reverse_iterator;
			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		private:
			pointer					_arr;
			size_type				_size;
			size_type				_capacity;
			allocator_type			_allocator;
			static const size_type	_expansion_factor = 2;
		public:
			// Contructors
			explicit vector (const allocator_type& alloc = allocator_type())
			: _arr(alloc.allocate(0)), _size(0), _capacity(0), _allocator(alloc) {}

			explicit vector (size_type n, const value_type& val = value_type(),
								const allocator_type& alloc = allocator_type())
			: _arr(n), _size(0), _capacity(n), _allocator(alloc) {}

			template <class InputIterator>
        	vector (InputIterator first, InputIterator last,
                	const allocator_type& alloc = allocator_type());

			~vector() {
				clear();
				_allocator.deallocate(_array, _capacity);
				_capacity = 0;
				_arr = NULL;
			}


			vector(const vector &ref) {

			}
			vector& operator= (const vector& x) {
				if (this != &x)
				{
					clear();
					if (x._size > _capacity)
						reserve(_capacity);
					for (size_t i = 0; i < x._size; i++)
						_allocator.create(&_arr[i], x[i]);
					_size = x._size;
				}
				return *this;
			};

			// iterator begin() { return std::begin(_arr); }

			// const_iterator begin() const { return std::begin(_arr); }

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
						_allocator.construct(&_arr[i], val);
				}
				_size = n;
			}

			size_type capacity() const { return _capacity; };

			bool empty() const { return _size == 0; };

			void reserve (size_type n) {
				pointer* temp;

				if (n > _capacity)
				{
					try
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
					catch(const std::bad_alloc& ba)
					{
						throw;
					}
				}
			}

			// Element access:
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

			reference operator[](size_type pos) { return _arr[pos]; };

			const_reference operator[](size_type pos) const { return _arr[pos]; };

			reference front() { return _arr[0] };

			const_reference front() const { return _arr[0] };

			reference back() { return _arr[size - 1]};

			const_reference back() const { return _arr[size - 1]};

			// modifiers
			// template <class InputIterator>
  			// void assign (InputIterator first, InputIterator last) {
			// 	for ()
			// }
			void assign (size_type n, const value_type& val) {
				for (int i = 0; i < n; i++)
					_arr[i] = val;
			}

			void push_back (const value_type& val) {
				++_size;
				if (_size >= _capacity)
					reserve(_capacity * _expansion_factor);
				_allocator.construct(&_arr[_size], val);
			}

			void pop_back() {
				_allocator.destroy(&_arr[_size - 1]);
				--_size;
			}

			// iterator insert (iterator position, const value_type& val) {
			// 	++_size;
			// 	if (_size >= _capacity)
			// 		reserve(_capacity * _expansion_factor);
			// 	for (size_t i = (position - ))
			// }

			// void insert (iterator position, size_type n, const value_type& val) {

			// }

			// template <class InputIterator>
			// void insert (iterator position, InputIterator first, InputIterator last) {

			// }

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
