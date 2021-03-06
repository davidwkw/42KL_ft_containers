#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <iterator>

namespace ft {
	template <class Iterator>
	class iterator_traits {
		public:
			typedef Iterator::difference_type difference_type;
			typedef Iterator::value_type value_type;
			typedef Iterator::pointer pointer;
			typedef Iterator::reference reference;
			typedef Iterator::iterator_category iterator_category;
	};

	template <class T>
	class iterator_traits<T*> {
		public:
			typedef ptrdiff_t difference_type;
			typedef T value_type;
			typedef T* pointer;
			typedef const T& reference;
			typedef std::random_access_iterator_tag iterator_category;
	};

	template <class T>
	class iterator_traits<const T*> {
		public:
			typedef ptrdiff_t difference_type;
			typedef T value_type;
			typedef const T* pointer;
			typedef const T& reference;
			typedef std::random_access_iterator_tag iterator_category;
	};
}

#endif
