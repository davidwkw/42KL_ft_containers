#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft {

	template < class Iterator >
	class reverse_iterator {
		public:
			typedef Iterator										iterator_type;
			typedef iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef iterator_traits<Iterator>::value_type			value_type;
			typedef iterator_traits<Iterator>::difference_type		difference_type;
			typedef iterator_traits<Iterator>::pointer				pointer;
			typedef iterator_traits<Iterator>::reference			reference;

		private:
			iterator_type _base;
		public:
			reverse_iterator() : _base(NULL) {}
			explicit reverse_iterator (iterator_type it) : _base(it) {}

			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : _base(rev_it._base) {}

			iterator_type base() const { return iterator_type(_base); }
			reference operator*() const {
				iterator_type it = _base;
				return *(--it);
			}
			reverse_iterator operator+ (difference_type n) const {
				return reverse_iterator(_base() - n);
			}
			reverse_iterator& operator++() {
				--_base;
				return *this;
			}
			reverse_iterator operator++(int) {
				reverse_iterator temp = *this;
				++(*this);
				return temp;
			}
			reverse_iterator& operator+=(difference_type n) {
				_base -= n;
				return *this;
			}
			reverse_iterator operator-(difference_type n) const {
				return reverse_iterator(_base() + n);
			}
			reverse_iterator& operator--() {
				++_base;
				return *this;
			}
			reverse_iterator  operator--(int) {
				reverse_iterator temp = *this;
				--(*this);
				return temp;
			}
			reverse_iterator& operator-=(difference_type n) {
				_base += n;
				return *this;
			}
			pointer operator->() const {
 				return &(operator*());
			}
			reference operator[] (difference_type n) const {
				return base()[n - 1];
			}
	};

	template <class Iterator>
  	bool operator== (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs) {
					   return lhs.base() == rhs.base();
				   }
	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs) {
					   return lhs.base() != rhs.base();
				   }

	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs) {
					   return lhs.base() < rhs.base();
				   }

	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs) {
					   return lhs.base() <= rhs.base();
				   }

	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs) {
					   return lhs.base() > rhs.base();
				   }

	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs,
                   const reverse_iterator<Iterator>& rhs) {
					   return lhs.base() >= rhs.base();
				   }

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (
             typename reverse_iterator<Iterator>::difference_type n,
             const reverse_iterator<Iterator>& rev_it) {
				 return rev_it + n;
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (
    const reverse_iterator<Iterator>& lhs,
    const reverse_iterator<Iterator>& rhs) {
		return rhs.base() - lhs.base();
	}
}

#endif
