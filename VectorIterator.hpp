#ifndef INTERATOR_HPP

#define ITERATOR_HPP

#include <iterator>

namespace ft {

	template <typename T>
	struct VectorIterator : public std::iterator<std::random_access_iterator_tag, T>{

		pointer ptr;

		VectorIterator() : ptr(NULL) {}
		VectorIterator(pointer pntr) : ptr(pntr) {}
		VectorIterator(const VectorIterator& ref) : ptr(ref.ptr) {}
		VectorIterator& operator=(const VectorIterator& ref) {
			if (this != &ref)
				ptr = ref.ptr;
			return *this;
		}
		~VectorIterator() {};

		operator VectorIterator<const T>() const {
			return VectorIterator<const T>(ptr);
		}

		reference operator*() const { return *ptr; }
		reference operator[](const difference_type i) const { return ptr[i]; }
		pointer operator->() const { return ptr; }

		friend bool operator==(const VectorIterator& lhs, const VectorIterator& rhs) { return lhs.ptr == rhs.ptr; }
		friend bool operator!=(const VectorIterator& lhs, const VectorIterator& rhs) { return !(lhs.ptr == rhs.ptr); }
		friend bool operator<(const VectorIterator& lhs, const VectorIterator& rhs) {
			return lhs.ptr < rhs.ptr;
		}
		friend bool operator<=(const VectorIterator& lhs, const VectorIterator& rhs) {
			return !(rhs.ptr < lhs.ptr);
		}
		friend bool operator>(const VectorIterator& lhs, const VectorIterator& rhs) {
			return rhs.ptr < lhs.ptr;
		}
		friend bool operator>=(const VectorIterator& lhs, const VectorIterator& rhs) {
			return !(lhs.ptr < rhs.ptr);;
		}

		VectorIterator& operator++() {
			++ptr;
			return *this;
		}
		VectorIterator operator++(int) {
			VectorIterator tmp(*this);
			operator++();
			return tmp;
		}
		VectorIterator& operator--() {
			--ptr;
			return *this;
		}
		VectorIterator operator--(int) {
			VectorIterator tmp(*this);
			operator--();
			return tmp;
		}
		VectorIterator operator+(const difference_type i) const {
			return VectorIterator(ptr + i);
		}
		friend VectorIterator operator+(const difference_type i, const VectorIterator& rhs) {
			return VectorIterator(i + rhs.ptr);
		}
		VectorIterator operator-(const difference_type i) const {
			return VectorIterator(ptr - i);
		}
		difference_type operator-(const VectorIterator& rhs) const {
			return ptr - rhs.ptr;
		}
		VectorIterator& operator+=(const difference_type i) {
			ptr += i;
			return *this;
		}
		VectorIterator& operator-=(const difference_type i) {
			ptr -= i;
			return *this;
		}
	};
}

#endif
