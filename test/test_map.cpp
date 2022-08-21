
#include "test_map.hpp"

TEST_NS::map<int, std::string> init_map() {
    int array[] = {0, 42, 84, 126, 168};
    std::string str[] = {"one", "two", "three", "four", "five"};
    TEST_NS::map<int, std::string> mp;

    for (long unsigned int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        mp.insert(
            TEST_NS::make_pair(array[i], str[i]));  // single element insert
    }
    return mp;
}

void test_copy() {
    std::cout << "========================================" << std::endl;
    std::cout << "Map copy test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::map<int, std::string> mp = init_map();
    TEST_NS::map<int, std::string> mp2 = mp;  // copy constructor
    print_map(mp2);

    TEST_NS::map<int, std::string> mp3;
    mp3 = mp;  // assignment operator
    print_map(mp3);
}

void test_insert() {
    std::cout << "========================================" << std::endl;
    std::cout << "Map insert test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::map<int, std::string> mp = init_map();
    print_map(mp);

    mp.insert(TEST_NS::make_pair(42, "forty-two"));  // single element insert
    print_map(mp);

    mp.insert(mp.begin(), TEST_NS::make_pair(42, "forty-two"));  // hint insert
    print_map(mp);

    TEST_NS::map<int, std::string> mp2;
    mp2.insert(mp.begin(), mp.end());  // range insert
    print_map(mp2);
}

void test_erase() {
    std::cout << "========================================" << std::endl;
    std::cout << "Map erase test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::map<int, std::string> mp = init_map();

    mp.erase(mp.begin());  // single element erase.
    print_map(mp);

    mp.erase(42);  // erase by key
    print_map(mp);

    mp.erase(mp.begin(), mp.end());
    print_map(mp);
}

void test_iterator() {
    std::cout << "========================================" << std::endl;
    std::cout << "Map iterator test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::map<int, std::string> mp = init_map();
    TEST_NS::map<int, std::string>::iterator it = mp.begin();
    TEST_NS::map<int, std::string>::const_iterator cit = mp.begin();

    // should be able to perform operations between iterator and const_iterator
    std::cout << "(it == const_it): " << (cit != it ? "true" : "false")
              << std::endl;
}

void test_iterator_dereference() {
    std::cout << "========================================" << std::endl;
    std::cout << "Map iterator dereference test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::map<int, std::string> mp = init_map();
    TEST_NS::map<int, std::string>::iterator it;

    it = mp.begin();
    std::cout << "pair is: " << it->first << ", ";
    TEST_NS::pair<int, std::string> q = *it;
    std::cout << q.second << std::endl;
}

void test_iterator_relational_operators() {
    std::cout << "========================================" << std::endl;
    std::cout << "Map iterator relational operator test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::map<int, std::string> mp = init_map();
    TEST_NS::map<int, std::string>::iterator it, it2;
    it = mp.begin();
    it2 = mp.end();

    std::cout << "eq: " << (it == it) << std::endl;

    std::cout << std::endl;
    std::cout << "eq: " << (it == it2) << " | ne: " << (it != it2) << std::endl;

    std::cout << std::endl;
    std::cout << "eq: " << (it2 == it) << " | ne: " << (it2 != it) << std::endl;
}

void test_reverse_iterator() {
    std::cout << "========================================" << std::endl;
    std::cout << "Map reverse iterator test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::map<int, std::string> mp = init_map();
    TEST_NS::map<int, std::string>::iterator it = mp.begin();
    TEST_NS::map<int, std::string>::const_iterator cit = mp.end();

    // should be able to construct reverse iterators from iterators
    TEST_NS::map<int, std::string>::reverse_iterator rit(it);
    TEST_NS::map<int, std::string>::const_reverse_iterator crit(cit);

    // sholud have one offset between iterator and reverse iterator
    std::cout << "*--rit == *it: " << (*--rit == *it ? "OK" : "Fail")
              << std::endl;
    std::cout << "*crit == *--cit: " << (*crit == *--cit ? "OK" : "Fail")
              << std::endl;
}

void test_reverse_iterator_dereference() {
    std::cout << "========================================" << std::endl;
    std::cout << "Map reverse iterator dereference test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::map<int, std::string> mp = init_map();
    TEST_NS::map<int, std::string>::reverse_iterator it;

    it = mp.rbegin();
    std::cout << "pair is: " << it->first << ", ";
    TEST_NS::pair<int, std::string> q = *it;
    std::cout << q.second << std::endl;
}

void test_reverse_iterator_relational_operators() {
    std::cout << "========================================" << std::endl;
    std::cout << "Map reverse iterator relational operator test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::map<int, std::string> mp = init_map();
    TEST_NS::map<int, std::string>::reverse_iterator it, it2;
    it = mp.rbegin();
    it2 = mp.rend();

    std::cout << "eq: " << (it == it) << std::endl;

    std::cout << std::endl;
    std::cout << "eq: " << (it == it2) << " | ne: " << (it != it2) << std::endl;

    std::cout << std::endl;
    std::cout << "eq: " << (it2 == it) << " | ne: " << (it2 != it) << std::endl;
}

void test_empty() {
    std::cout << "========================================" << std::endl;
    std::cout << "Map resize test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::map<int, std::string> mp;

    std::cout << "map is empty: " << mp.empty() << std::endl;
    mp = init_map();
    std::cout << "map is empty: " << mp.empty() << std::endl;
}

void test_operator_bracket() {
    std::cout << "========================================" << std::endl;
    std::cout << "Map operator[] test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::map<int, std::string> mp = init_map();

    for (TEST_NS::map<int, std::string>::size_type i = 0; i < mp.size(); ++i)
        std::cout << "element " << i << " = " << (mp[i] = "toot") << std::endl;
    print_map(mp);
}

void test_swap() {
    std::cout << "========================================" << std::endl;
    std::cout << "Map swap test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::map<int, std::string> mp = init_map();
    TEST_NS::map<int, std::string> mp2 = init_map();
    mp.insert(mp2.begin(), mp2.end());

    print_map(mp);
    print_map(mp2);
    mp.swap(mp2);
    print_map(mp);
    print_map(mp2);
    TEST_NS::swap(mp, mp2);
    print_map(mp);
    print_map(mp2);
}

void test_clear() {
    std::cout << "========================================" << std::endl;
    std::cout << "Map clear test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::map<int, std::string> mp = init_map();
    mp.clear();
    print_map(mp);
}

void test_relational_operators() {
    std::cout << "========================================" << std::endl;
    std::cout << "Map relational operator test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::map<int, std::string> mp = init_map();
    TEST_NS::map<int, std::string> mp2 = init_map();

    std::cout << "eq: " << (mp == mp2) << std::endl;
    mp.insert(mp2.begin(), mp2.end());

    std::cout << std::endl;

    std::cout << "eq: " << (mp == mp2) << " | ne: " << (mp != mp2) << std::endl;
    std::cout << "lt: " << (mp < mp2) << " | le: " << (mp <= mp2) << std::endl;
    std::cout << "gt: " << (mp > mp2) << " | ge: " << (mp >= mp2) << std::endl;

    std::cout << std::endl;

    std::cout << "eq: " << (mp2 == mp) << " | ne: " << (mp2 != mp) << std::endl;
    std::cout << "lt: " << (mp2 < mp) << " | le: " << (mp2 <= mp) << std::endl;
    std::cout << "gt: " << (mp2 > mp) << " | ge: " << (mp2 >= mp) << std::endl;
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
    test_operator_bracket();
    test_swap();
    test_clear();
    test_relational_operators();

    return 0;
}
