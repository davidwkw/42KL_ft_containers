#ifndef INTERATOR_HPP

#define ITERATOR_HPP

#include <iterator>

namespace ft {

	template <typename T>
	class Iterator {
		public:
		    typedef T value_type;
			typedef ptrdiff_t difference_type;
			typedef T* pointer;
			typedef T& reference;
			typedef std::random_access_iterator_tag  iterator_category;

		private:
			pointer _pointer;
		public:
			Iterator() : _pointer(NULL) {}
			Iterator(T* ptr) : _pointer(ptr) {}
			Iterator(const Iterator& ref) : _pointer(ref._pointer) {}
			Iterator& operator=(const Iterator& ref) {
				if (this != &ref)
					_pointer = ref._pointer;
				return *this;
			}
			~Iterator() {};

			operator Iterator<const T>() const {
				return Iterator<const T>(_pointer);
    		}

			reference operator*() const { return *_pointer; }
			reference operator[](const difference_type i) const { return _pointer[i]; }
			pointer operator->() const { return _pointer; }

			friend bool operator==(const Iterator& lhs, const Iterator& rhs) { return lhs._pointer==rhs._pointer; }
			friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { return lhs._pointer!=rhs._pointer; }
			friend bool operator<(const Iterator& lhs, const Iterator& rhs) {
				return lhs._pointer < rhs._pointer;
			}
			friend bool operator>(const Iterator& lhs, const Iterator& rhs) {
				return lhs._pointer > rhs._pointer;
			}
			friend bool operator<=(const Iterator& lhs, const Iterator& rhs) {
				return lhs._pointer <= rhs._pointer;
			}
			friend bool operator>=(const Iterator& lhs, const Iterator& rhs) {
				return lhs._pointer >= rhs._pointer;
			}

			Iterator& operator++() {
				++_pointer;
				return *this;
			}
			Iterator operator++(int) {
				Iterator tmp(*this);
				operator++();
				return tmp;
			}
			Iterator& operator--() {
				--_pointer;
				return *this;
			}
			Iterator operator--(int) {
				Iterator tmp(*this);
				operator--();
				return tmp;
			}
			Iterator operator+(const difference_type i) const {
				return Iterator(_pointer + i);
			}
			friend Iterator operator+(const difference_type i, const Iterator& rhs) {
				return Iterator(i + rhs._pointer);
			}
			Iterator operator-(const difference_type i) const {
				return Iterator(_pointer - i);
			}
			difference_type operator-(const Iterator& rhs) const {
				return _pointer - rhs._pointer;
			}
			Iterator& operator+=(const difference_type i) {
				_pointer += i;
				return *this;
			}
			Iterator& operator-=(const difference_type i) {
				_pointer -= i;
				return *this;
			}
	};
}

#endif
