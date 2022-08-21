
#include "test_stack.hpp"

TEST_NS::stack<int> init_stack() {
    int array[] = {0, 42, 84, 126, 168};
    TEST_NS::stack<int> stk;

    for (long unsigned int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
        stk.push(array[i]);  // single element insert
    }
    return stk;
}

void test_copy() {
    std::cout << "========================================" << std::endl;
    std::cout << "Stack copy test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::stack<int> stk = init_stack();
    TEST_NS::stack<int> stk2 = stk;  // copy constructor
    print_stack(stk2);

    TEST_NS::stack<int> stk3;
    stk3 = stk;  // assignment operator
    print_stack(stk3);
}

void test_push() {
    std::cout << "========================================" << std::endl;
    std::cout << "Stack push test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::stack<int> stk = init_stack();

    stk.push(42);
    print_stack(stk);
}

void test_pop() {
    std::cout << "========================================" << std::endl;
    std::cout << "Stack pop test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::stack<int> stk = init_stack();

    stk.pop();
    print_stack(stk);
}

void test_top() {
    std::cout << "========================================" << std::endl;
    std::cout << "Stack top test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::stack<int> stk = init_stack();

    std::cout << stk.top() << std::endl;
    print_stack(stk);
}

void test_empty() {
    std::cout << "========================================" << std::endl;
    std::cout << "Stack resize test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::stack<int> stk;

    std::cout << "stack is empty: " << stk.empty() << std::endl;
    stk = init_stack();
    std::cout << "stack is empty: " << stk.empty() << std::endl;
}

void test_relational_operators() {
    std::cout << "========================================" << std::endl;
    std::cout << "Stack relational operator test:" << std::endl;
    std::cout << "========================================" << std::endl;
    TEST_NS::stack<int> stk = init_stack();
    TEST_NS::stack<int> stk2 = init_stack();

    std::cout << "eq: " << (stk == stk2) << std::endl;
    stk.push(1);

    std::cout << std::endl;

    std::cout << "eq: " << (stk == stk2) << " | ne: " << (stk != stk2)
              << std::endl;
    std::cout << "lt: " << (stk < stk2) << " | le: " << (stk <= stk2)
              << std::endl;
    std::cout << "gt: " << (stk > stk2) << " | ge: " << (stk >= stk2)
              << std::endl;

    std::cout << std::endl;

    std::cout << "eq: " << (stk2 == stk) << " | ne: " << (stk2 != stk)
              << std::endl;
    std::cout << "lt: " << (stk2 < stk) << " | le: " << (stk2 <= stk)
              << std::endl;
    std::cout << "gt: " << (stk2 > stk) << " | ge: " << (stk2 >= stk)
              << std::endl;
}

int main() {
    test_copy();
    test_push();
    test_pop();
    test_top();
    test_empty();
    test_relational_operators();

    return 0;
}
