#ifndef VECTOR_ITERATOR_HPP

#define VECTOR_ITERATOR_HPP

#include <iterator>

namespace ft {

	template <typename T>
	struct VectorIterator{

		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::ptrdiff_t  difference_type;
		typedef std::random_access_iterator_tag  iterator_category;

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

		friend bool operator==(const VectorIterator& lhs, const VectorIterator& rhs){
			return lhs.ptr == rhs.ptr;
		}
		friend bool operator!=(const VectorIterator& lhs, const VectorIterator& rhs){ 
			return !(lhs == rhs);
		}
		friend bool operator<(const VectorIterator& lhs, const VectorIterator& rhs){
			return lhs.ptr < rhs.ptr;
		}
		friend bool operator<=(const VectorIterator& lhs, const VectorIterator& rhs){
			return !(lhs > rhs);
		}
		friend bool operator>(const VectorIterator& lhs, const VectorIterator& rhs){
			return rhs < lhs;
		}
		friend bool operator>=(const VectorIterator& lhs, const VectorIterator& rhs){
			return !(lhs < rhs);
		}

		VectorIterator& operator++() {
			++ptr;
			return *this;
		}
		VectorIterator operator++(int) {
			VectorIterator tmp(*this);
			++(*this);
			return tmp;
		}
		VectorIterator& operator--() {
			--ptr;
			return *this;
		}
		VectorIterator operator--(int) {
			VectorIterator tmp(*this);
			--(*this);
			return tmp;
		}
		VectorIterator operator+(difference_type i) const {
			return VectorIterator(ptr + i);
		}
		friend VectorIterator operator+(difference_type i, const VectorIterator& rhs) {
			return VectorIterator(i + rhs.ptr);
		}
		VectorIterator operator-(difference_type i) const {
			return VectorIterator(ptr - i);
		}

		difference_type operator-(const VectorIterator& rhs) const {
			return ptr - rhs.ptr;
		}

		VectorIterator& operator+=(difference_type i) {
			ptr += i;
			return *this;
		}
		VectorIterator& operator-=(difference_type i) {
			ptr -= i;
			return *this;
		}
	};

	template <class T>
	std::ptrdiff_t operator-(const VectorIterator<const T>& lhs,
							const VectorIterator<T>& rhs) {
		return std::distance(static_cast<VectorIterator<const T> >(rhs), lhs);
	}

	template <class T>
	std::ptrdiff_t operator-(const VectorIterator<T>& lhs,
							const VectorIterator<const T>& rhs) {
		return std::distance(rhs, static_cast<VectorIterator<const T> >(lhs));
	}
}

#endif
