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
			// typedef iterator
			// typedef const_iterator;
			// typedef std::reverse_iterator<iterator> reverse_iterator
			// typedef std::reverse_iterator<const_iterator> const_reverse_iterator
			// Contructors
		private:
			T*				_arr;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_allocator;
			static const size_type _expansion_factor = 2;
		public:
			explicit vector (const allocator_type& alloc = allocator_type())
			: _arr(alloc.allocate(0)), _size(0), _capacity(0), _allocator(alloc) {}

			explicit vector (size_type n, const value_type& val = value_type(),
								const allocator_type& alloc = allocator_type())
			: _arr(), _size(0), _capacity(), _allocator(alloc)
			{}

			template <class InputIterator>
        	vector (InputIterator first, InputIterator last,
                	const allocator_type& alloc = allocator_type());

			vector (const vector& x) {

			}
			~vector();
			vector(const vector &ref);
			reference operator=(const vector &ref) {};

			// iterator begin() { return std::begin(_arr); }

			// const_iterator begin() const { return std::begin(_arr); }

			// Capacity
			size_type size() const { return _size; };

			size_type max_size() const { return _max_size; };

			size_type capacity() const { return _capacity; };

			bool empty() const { return _size == 0; };

			void reserve (size_type n) {
				T* temp;

				if (n > _capacity)
					_allocator.allocate(n)
			}

			// void resize (size_type n, value_type val = value_type()) {
			// 	if (n < _size)
			// 	else if (n > size)
			// }

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

			// Allocator
			allocator_type get_allocator() const { return _allocator; }

	};

}

#endif
