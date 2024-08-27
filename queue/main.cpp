#include <iostream>

#include "queue.h"

int main(int argc, char** argv) {
    
    Queue<int> queue;
    if (queue.empty()) {
        std::cout << "queue is empty!" << std::endl;
    }

    queue.enqueue(1);
    std::cout << "queue top is " << queue.front() << std::endl;
    queue.enqueue(2);
    std::cout << "queue top is " << queue.front() << std::endl;
    queue.enqueue(3);
    std::cout << "queue top is " << queue.front() << std::endl;
    queue.enqueue(4);
    std::cout << "queue top is " << queue.front() << std::endl;

    if (!queue.empty()) {
        std::cout << "queue is not empty!" << std::endl;
    }

    queue.dequeue();
    std::cout << "queue top is " << queue.front() << std::endl;
    queue.dequeue();
    std::cout << "queue top is " << queue.front() << std::endl;
    queue.dequeue();
    std::cout << "queue top is " << queue.front() << std::endl;
    queue.dequeue();

    if (queue.empty()) std::cout << "queue is empty!" << std::endl;

    std::cout << "Press Enter to continue...";
    std::cin.get();
    return 0;
}