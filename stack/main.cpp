#include <iostream>

#include "stack.h"

int main(int argc, char** argv) {
    Stack<int> stack;
    if (stack.empty()) {
        std::cout << "stack is empty!" << std::endl;
    }

    stack.push(4);
    std::cout << "stack top is " << stack.top() << std::endl;
    stack.push(3);
    std::cout << "stack top is " << stack.top() << std::endl;
    stack.push(2);
    std::cout << "stack top is " << stack.top() << std::endl;
    stack.push(1);
    std::cout << "stack top is " << stack.top() << std::endl;

    stack.pop();
    std::cout << "stack top is " << stack.top() << std::endl;
    stack.pop();
    std::cout << "stack top is " << stack.top() << std::endl;
    stack.pop();
    std::cout << "stack top is " << stack.top() << std::endl;
    stack.pop();

    if (stack.empty()) std::cout << "stack is empty!" << std::endl;

    std::cout << "Press Enter to continue...";
    std::cin.get();
    return 0;
}