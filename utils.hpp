# include <algorithm>

namespace ft {
	// enable_if
	template<bool Cond, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	// is_integral
	template <class T, T v>
	struct integral_constant {
		static constexpr T value = v;
		typedef T value_type;
		typedef integral_constant<T,v> type;
		constexpr operator T() { return v; }
	};

	typedef integral_constant<bool,false> false_type;
	typedef integral_constant<bool,true> true_type;

	template<typename> struct is_integral_base : false_type {};
	template<> struct is_integral_base<bool> : true_type {};
	template<> struct is_integral_base<char> : true_type {};
	template<> struct is_integral_base<signed char> : true_type {};
	template<> struct is_integral_base<unsigned char> : true_type {};
	template<> struct is_integral_base<int> : true_type {};
	template<> struct is_integral_base<unsigned int> : true_type {};
	template<> struct is_integral_base<short> : true_type {};
	template<> struct is_integral_base<unsigned short> : true_type {};
	template<> struct is_integral_base<long> : true_type {};
	template<> struct is_integral_base<unsigned long> : true_type {};
	template<> struct is_integral_base<long long> : true_type {};
	template<> struct is_integral_base<unsigned long long> : true_type {};

	template< class T >
	struct is_integral : is_integral_base<T> {};

	// equal

	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2) {
		while (first1!=last1) {
			if (!(*first1 == *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1,
              InputIterator2 first2, BinaryPredicate pred) {
		while (first1!=last1) {
			if (!pred(*first1, *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

	// lexographical compare
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2) {
		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1)
				return false;
			else if (*first1<*first2)
				return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2,
                                Compare comp) {
		while (first1!=last1)
		{
			if (first2==last2 || comp(*first2, *first1))
				return false;
			else if (*first1<*first2)
				return true;
			++first1; ++first2;
		}
		return (first2!=last2);
	}

	// std::pair

	template< class T1, class T2 >
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair() : first(), second() {}

		template<class U, class V>
		pair (const pair<U,V>& pr) : first(pr.first), second(pr.second);

		pair (const first_type& a, const second_type& b) : first(a), second(b);

		pair& operator=(const pair& pr) {
			if (this != &pr) {
				first = pr.first;
				second = pr.second;
			}
			return *this;
		}

		void swap (pair& pr) noexcept ( noexcept(swap(first,pr.first)) &&
                                noexcept(swap(second,pr.second)) ) {
			swap(first,pr.first);
			swap(second,pr.second);
		}
	};

	// std::make_pair
	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ( pair<T1,T2>(x,y) );
	}
}
