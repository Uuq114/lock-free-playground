#include "ubqueue.h"

#include <iostream>
#include <vector>

int main() {
  UBQueue queue;
  std::vector<int> input{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  for (auto i : input) {
    queue.enqueue(i);
    std::cout << "enqueue: " << i << std::endl;
  }
  std::cout << "=================" << std::endl;
  int tmp;
  for (size_t i = 0; i < input.size(); i++) {
    queue.dequeue(&tmp);
    std::cout << "dequeue: " << tmp << std::endl;
  }

  return 0;
}