
#include "test_set.hpp"

TEST_NS::set<int> init_set() {
    int array[] = {0, 42, 84, 126, 168};
    std::string str[] = {"one", "two", "three", "four", "five"};
    TEST_NS::set<int> st;

    for (long unsigned int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        st.insert(array[i]);  // single element insert
    }
    return st;
}

void test_copy() {
    std::cout << "========================================" << std::endl;
    std::cout << "Set copy test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::set<int> st = init_set();
    TEST_NS::set<int> st2 = st;  // copy constructor
    print_set(st2);

    TEST_NS::set<int> st3;
    st3 = st;  // assignment operator
    print_set(st3);
}

void test_insert() {
    std::cout << "========================================" << std::endl;
    std::cout << "Set insert test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::set<int> st = init_set();
    print_set(st);

    st.insert(42);  // single element insert
    print_set(st);

    st.insert(st.begin(), 42);  // hint insert
    print_set(st);

    TEST_NS::set<int> st2;
    st2.insert(st.begin(), st.end());  // range insert
    print_set(st2);
}

void test_erase() {
    std::cout << "========================================" << std::endl;
    std::cout << "Set erase test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::set<int> st = init_set();

    st.erase(st.begin());  // single element erase.
    print_set(st);

    st.erase(42);  // erase by key
    print_set(st);

    st.erase(st.begin(), st.end());
    print_set(st);
}

void test_iterator() {
    std::cout << "========================================" << std::endl;
    std::cout << "Set iterator test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::set<int> st = init_set();
    TEST_NS::set<int>::iterator it = st.begin();
    TEST_NS::set<int>::const_iterator cit = st.begin();

    // should be able to perform operations between iterator and const_iterator
    std::cout << "(it == const_it): " << (cit != it ? "true" : "false")
              << std::endl;
}

void test_iterator_dereference() {
    std::cout << "========================================" << std::endl;
    std::cout << "Set iterator dereference test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::set<int> st = init_set();
    TEST_NS::set<int>::iterator it;
    TEST_NS::set<TEST_NS::pair<int, int> > st2;
    TEST_NS::set<TEST_NS::pair<int, int> >::iterator it2;

    it = st.begin();
    std::cout << *it << std::endl;

    st2.insert(TEST_NS::make_pair(1, 2));
    it2 = st2.begin();
    std::cout << it2->first << ", " << it2->second << std::endl;
}

void test_iterator_relational_operators() {
    std::cout << "========================================" << std::endl;
    std::cout << "Set iterator relational operator test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::set<int> st = init_set();
    TEST_NS::set<int>::iterator it, it2;
    it = st.begin();
    it2 = st.end();

    std::cout << "eq: " << (it == it) << std::endl;

    std::cout << std::endl;
    std::cout << "eq: " << (it == it2) << " | ne: " << (it != it2) << std::endl;

    std::cout << std::endl;
    std::cout << "eq: " << (it2 == it) << " | ne: " << (it2 != it) << std::endl;
}

void test_reverse_iterator() {
    std::cout << "========================================" << std::endl;
    std::cout << "Set reverse iterator test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::set<int> st = init_set();
    TEST_NS::set<int>::iterator it = st.begin();
    TEST_NS::set<int>::const_iterator cit = st.end();

    // should be able to construct reverse iterators from iterators
    TEST_NS::set<int>::reverse_iterator rit(it);
    TEST_NS::set<int>::const_reverse_iterator crit(cit);

    // sholud have one offset between iterator and reverse iterator
    std::cout << "*--rit == *it: " << (*--rit == *it ? "OK" : "Fail")
              << std::endl;
    std::cout << "*crit == *--cit: " << (*crit == *--cit ? "OK" : "Fail")
              << std::endl;
}

void test_reverse_iterator_dereference() {
    std::cout << "========================================" << std::endl;
    std::cout << "Set reverse iterator dereference test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::set<int> st = init_set();
    TEST_NS::set<int>::reverse_iterator it;
    TEST_NS::set<TEST_NS::pair<int, int> > st2;
    TEST_NS::set<TEST_NS::pair<int, int> >::reverse_iterator it2;

    it = st.rbegin();
    std::cout << *it << std::endl;

    st2.insert(TEST_NS::make_pair(1, 2));
    it2 = st2.rbegin();
    std::cout << it2->first << ", " << it2->second << std::endl;
}

void test_reverse_iterator_relational_operators() {
    std::cout << "========================================" << std::endl;
    std::cout << "Set reverse iterator relational operator test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::set<int> st = init_set();
    TEST_NS::set<int>::reverse_iterator it, it2;
    it = st.rbegin();
    it2 = st.rend();

    std::cout << "eq: " << (it == it) << std::endl;

    std::cout << std::endl;
    std::cout << "eq: " << (it == it2) << " | ne: " << (it != it2) << std::endl;

    std::cout << std::endl;
    std::cout << "eq: " << (it2 == it) << " | ne: " << (it2 != it) << std::endl;
}

void test_empty() {
    std::cout << "========================================" << std::endl;
    std::cout << "Set resize test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::set<int> st;

    std::cout << "set is empty: " << st.empty() << std::endl;
    st = init_set();
    std::cout << "set is empty: " << st.empty() << std::endl;
}

void test_swap() {
    std::cout << "========================================" << std::endl;
    std::cout << "Set swap test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::set<int> st = init_set();
    TEST_NS::set<int> st2 = init_set();
    st.insert(st2.begin(), st2.end());

    print_set(st);
    print_set(st2);
    st.swap(st2);
    print_set(st);
    print_set(st2);
    TEST_NS::swap(st, st2);
    print_set(st);
    print_set(st2);
}

void test_clear() {
    std::cout << "========================================" << std::endl;
    std::cout << "Set clear test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::set<int> st = init_set();
    st.clear();
    print_set(st);
}

void test_relational_operators() {
    std::cout << "========================================" << std::endl;
    std::cout << "Set relational operator test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::set<int> st = init_set();
    TEST_NS::set<int> st2 = init_set();

    std::cout << "eq: " << (st == st2) << std::endl;
    st.insert(st2.begin(), st2.end());

    std::cout << std::endl;

    std::cout << "eq: " << (st == st2) << " | ne: " << (st != st2) << std::endl;
    std::cout << "lt: " << (st < st2) << " | le: " << (st <= st2) << std::endl;
    std::cout << "gt: " << (st > st2) << " | ge: " << (st >= st2) << std::endl;

    std::cout << std::endl;

    std::cout << "eq: " << (st2 == st) << " | ne: " << (st2 != st) << std::endl;
    std::cout << "lt: " << (st2 < st) << " | le: " << (st2 <= st) << std::endl;
    std::cout << "gt: " << (st2 > st) << " | ge: " << (st2 >= st) << std::endl;
}

int main() {
    test_copy();
    test_insert();
    test_erase();
    test_iterator();
    test_iterator_dereference();
    test_iterator_relational_operators();
    test_reverse_iterator();
    test_reverse_iterator_dereference();
    test_reverse_iterator_relational_operators();
    test_empty();
    test_swap();
    test_clear();
    test_relational_operators();

    return 0;
}
