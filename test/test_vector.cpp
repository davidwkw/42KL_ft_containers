
#include "test_vector.hpp"

TEST_NS::vector<int> init_vector() {
    int array[] = {0, 42, 84, 126, 168};
    TEST_NS::vector<int> vct;

    for (long unsigned int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        vct.insert(vct.end(), array[i]);  // single element insert
    }
    return vct;
}

void test_copy() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector copy test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::vector<int> vct = init_vector();
    TEST_NS::vector<int> vct2 = vct;  // copy constructor
    print_vector(vct2);

    TEST_NS::vector<int> vct3;
    vct3 = vct;  // assignment operator
    print_vector(vct3);
}

void test_insert() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector insert test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::vector<int> vct = init_vector();
    int array[] = {0, 42, 84, 126, 168};

    vct.insert(vct.begin(), 3, 42);  // fill insert in front
    print_vector(vct);
    vct.insert(vct.end(), 3, 42);  // fill insert at the back
    print_vector(vct);

    vct.insert(vct.begin(), array, array + 5);  // range insert in front
    print_vector(vct);
    vct.insert(vct.end(), array, array + 5);  // range insert at the back
    print_vector(vct);

    // inserting at the end (something large, like pair) is valid as well
    TEST_NS::pair<int, std::string> p = TEST_NS::make_pair(1, "Hello World!");

    TEST_NS::vector<TEST_NS::pair<int, std::string> > vct2;
    TEST_NS::vector<TEST_NS::pair<int, std::string> >::iterator it;

    vct2.insert(vct2.end(), p);
    it = vct2.begin();
    std::cout << it->first << " " << it->second << std::endl;
}

void test_erase() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector erase test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::vector<int> vct = init_vector();
    TEST_NS::vector<int>::iterator it, it2, it3;

    it = vct.erase(vct.begin());  // single element erase.
    print_vector(vct);
    std::cout << "Next element is: " << *it << std::endl;

    it2 = it3 = ++vct.begin();
    ++it3;
    it = vct.erase(it2, it3);  // range erase
    print_vector(vct);
    std::cout << "Next element is: " << *it << std::endl;
}

void test_iterator() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector iterator test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::vector<int> vct = init_vector();
    TEST_NS::vector<int>::iterator it = vct.begin();
    TEST_NS::vector<int>::const_iterator cit = vct.begin();

    // all these operations should be valid
    it = it + 3;
    it = 1 + it;
    it = it - 4;
    std::cout << *(it += 3) << std::endl;
    std::cout << *(it -= 3) << std::endl;

    // should be able to perform operations between iterator and const_iterator
    std::cout << "(it == const_it): " << (cit == it ? "true" : "false")
              << std::endl;
    std::cout << "(const_ite - it): " << (cit - it) << std::endl;
    std::cout << "(ite + 3 == it): " << (cit + 3 == it ? "true" : "false")
              << std::endl;
}

void test_iterator_dereference() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector iterator dereference test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::pair<int, std::string> p = TEST_NS::make_pair(1, "Hello World!");

    TEST_NS::vector<TEST_NS::pair<int, std::string> > vct;
    TEST_NS::vector<TEST_NS::pair<int, std::string> >::iterator it;

    vct.insert(vct.end(), p);
    std::cout << "size is: " << vct.size() << std::endl;
    it = vct.begin();
    std::cout << "pair is: " << it->first << ", ";
    TEST_NS::pair<int, std::string> q = *it;
    std::cout << q.second << std::endl;
}

void test_iterator_relational_operators() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector iterator relational operator test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::vector<int> vct = init_vector();
    TEST_NS::vector<int>::iterator it, it2;
    it = vct.begin();
    it2 = vct.end();

    std::cout << "eq: " << (it == it) << std::endl;

    std::cout << std::endl;

    std::cout << "eq: " << (it == it2) << " | ne: " << (it != it2) << std::endl;
    std::cout << "lt: " << (it < it2) << " | le: " << (it <= it2) << std::endl;
    std::cout << "gt: " << (it > it2) << " | ge: " << (it >= it2) << std::endl;

    std::cout << std::endl;

    std::cout << "eq: " << (it2 == it) << " | ne: " << (it2 != it) << std::endl;
    std::cout << "lt: " << (it2 < it) << " | le: " << (it2 <= it) << std::endl;
    std::cout << "gt: " << (it2 > it) << " | ge: " << (it2 >= it) << std::endl;
}

void test_iterator_operator_bracket() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector reverse iterator test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::vector<int> vct = init_vector();
    TEST_NS::vector<int>::iterator it = vct.begin();
    TEST_NS::vector<int>::iterator it2;
    TEST_NS::vector<int>::reverse_iterator rit;

    ++it;
    ++it;
    ++it;
    it2 = TEST_NS::vector<int>::iterator(it);
    rit = TEST_NS::vector<int>::reverse_iterator(it2);
    std::cout << "&rit[3 + 1] == &it[3]: " << (&rit[3 + 1] == &it[3])
              << std::endl;
}

void test_reverse_iterator() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector reverse iterator test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::vector<int> vct = init_vector();
    TEST_NS::vector<int>::iterator it = vct.begin();
    TEST_NS::vector<int>::const_iterator cit = vct.end();

    // should be able to construct reverse iterators from iterators
    TEST_NS::vector<int>::reverse_iterator rit(it);
    TEST_NS::vector<int>::const_reverse_iterator crit(cit);

    // sholud have one offset between iterator and reverse iterator
    std::cout << "*--rit == *it: " << (*--rit == *it ? "OK" : "Fail")
              << std::endl;
    std::cout << "*crit == *--cit: " << (*crit == *--cit ? "OK" : "Fail")
              << std::endl;
}

void test_reverse_iterator_dereference() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector reverse iterator dereference test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::pair<int, std::string> p = TEST_NS::make_pair(1, "Hello World!");

    TEST_NS::vector<TEST_NS::pair<int, std::string> > vct;
    TEST_NS::vector<TEST_NS::pair<int, std::string> >::reverse_iterator it;

    vct.insert(vct.end(), p);
    std::cout << "size is: " << vct.size() << std::endl;
    it = vct.rbegin();
    std::cout << "pair is: " << it->first << ", ";
    TEST_NS::pair<int, std::string> q = *it;
    std::cout << q.second << std::endl;
}

void test_reverse_iterator_relational_operators() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector reverse iterator relational operator test:"
              << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::vector<int> vct = init_vector();
    TEST_NS::vector<int>::reverse_iterator it, it2;
    it = vct.rbegin();
    it2 = vct.rend();

    std::cout << "eq: " << (it == it) << std::endl;

    std::cout << std::endl;

    std::cout << "eq: " << (it == it2) << " | ne: " << (it != it2) << std::endl;
    std::cout << "lt: " << (it < it2) << " | le: " << (it <= it2) << std::endl;
    std::cout << "gt: " << (it > it2) << " | ge: " << (it >= it2) << std::endl;

    std::cout << std::endl;

    std::cout << "eq: " << (it2 == it) << " | ne: " << (it2 != it) << std::endl;
    std::cout << "lt: " << (it2 < it) << " | le: " << (it2 <= it) << std::endl;
    std::cout << "gt: " << (it2 > it) << " | ge: " << (it2 >= it) << std::endl;
}

void test_resize() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector resize test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::vector<int> vct = init_vector();

    vct.resize(10, 42);
    print_vector(vct);
}

void test_empty() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector resize test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::vector<int> vct;

    std::cout << "vector is empty: " << vct.empty() << std::endl;
    vct = init_vector();
    std::cout << "vector is empty: " << vct.empty() << std::endl;
}

void test_reserve() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector reserve test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::vector<int> vct;

    vct.reserve(1000);
    std::cout << "vector capacity: " << vct.capacity() << std::endl;
}

void test_operator_bracket() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector operator[] test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::vector<int> vct = init_vector();

    for (TEST_NS::vector<int>::size_type i = 0; i < vct.size(); ++i)
        std::cout << "element " << i << " = " << vct[i] << std::endl;
}

void test_at() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector at test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::vector<int> vct = init_vector();

    // should have an error
    try {
        vct.at(vct.size());
    } catch (std::out_of_range &e) {
        std::cout << "Catch out_of_range exception!" << std::endl;
    } catch (std::exception &e) {
        std::cout << "Catch exception: " << e.what() << std::endl;
    }

    // should not have error
    std::cout << vct.at(0) << std::endl;
}

void test_front_back() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector front / back test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::vector<int> vct = init_vector();

    std::cout << "Front element: " << vct.front() << std::endl;
    std::cout << "Back element: " << vct.back() << std::endl;
}

void test_assign() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector assign test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::vector<int> vct = init_vector();
    TEST_NS::vector<int> vct2 = init_vector();

    vct.assign(100, 42);
    print_vector(vct);
    vct.assign(vct2.begin(), vct2.end());
    print_vector(vct);
}

void test_push_pop() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector push_back / pop_back test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::vector<int> vct = init_vector();

    vct.push_back(42);
    print_vector(vct);
    vct.pop_back();
    print_vector(vct);
}

void test_swap() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector swap test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::vector<int> vct = init_vector();
    TEST_NS::vector<int> vct2 = init_vector();
    vct.insert(vct.end(), vct2.begin(), vct2.end());

    print_vector(vct);
    print_vector(vct2);
    vct.swap(vct2);
    print_vector(vct);
    print_vector(vct2);
    TEST_NS::swap(vct, vct2);
    print_vector(vct);
    print_vector(vct2);
}

void test_clear() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector clear test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::vector<int> vct = init_vector();
    vct.clear();
    print_vector(vct);
}

void test_relational_operators() {
    std::cout << "========================================" << std::endl;
    std::cout << "Vector relational operator test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::vector<int> vct = init_vector();
    TEST_NS::vector<int> vct2 = init_vector();

    std::cout << "eq: " << (vct == vct2) << std::endl;
    vct.insert(vct.end(), vct2.begin(), vct2.end());

    std::cout << std::endl;

    std::cout << "eq: " << (vct == vct2) << " | ne: " << (vct != vct2)
              << std::endl;
    std::cout << "lt: " << (vct < vct2) << " | le: " << (vct <= vct2)
              << std::endl;
    std::cout << "gt: " << (vct > vct2) << " | ge: " << (vct >= vct2)
              << std::endl;

    std::cout << std::endl;

    std::cout << "eq: " << (vct2 == vct) << " | ne: " << (vct2 != vct)
              << std::endl;
    std::cout << "lt: " << (vct2 < vct) << " | le: " << (vct2 <= vct)
              << std::endl;
    std::cout << "gt: " << (vct2 > vct) << " | ge: " << (vct2 >= vct)
              << std::endl;
}

int main() {
    test_copy();
    test_insert();
    test_erase();
    test_iterator();
    test_iterator_dereference();
    test_iterator_relational_operators();
    test_iterator_operator_bracket();
    test_reverse_iterator();
    test_reverse_iterator_dereference();
    test_reverse_iterator_relational_operators();
    test_resize();
    test_empty();
    test_reserve();
    test_operator_bracket();
    test_at();
    test_front_back();
    test_assign();
    test_push_pop();
    test_swap();
    test_clear();
    test_relational_operators();

    return 0;
}
