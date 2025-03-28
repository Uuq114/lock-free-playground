#ifndef LOCK_FREE_PLAYGROUND_UBQUEUE_H
#define LOCK_FREE_PLAYGROUND_UBQUEUE_H

#include <atomic>
#include <cstdlib>

struct Pointer;
struct Node;

struct Pointer {
  Node *_pointer;
  unsigned int _counter;

  bool operator==(const Pointer &other) const {
    return _pointer == other._pointer && _counter == other._counter;
  }
};

struct Node {
  int _value;
  std::atomic<Pointer> _next;

  explicit Node(int val) : _value(val), _next(Pointer{nullptr, 0}) {}
};

class UBQueue {
 private:
  std::atomic<Pointer> _head;
  std::atomic<Pointer> _tail;
 public:
  UBQueue() {
    Node *dummy = new Node(-1);
    _head.store(Pointer{dummy, 0});
    _tail.store(Pointer{dummy, 0});
  };

  ~UBQueue() {
    int *tmp = new int;
    while (dequeue(tmp)) {}
    delete _head.load()._pointer;
  }

  void enqueue(int value) {
    Node *new_node = new Node(value);
    Pointer tail_copy = _tail.load();
    Pointer tail_next = tail_copy._pointer->_next.load();
    while (true) {
      if (tail_copy == _tail.load()) {
        if (tail_next._pointer == nullptr) {
          auto new_tail_next = Pointer{new_node, tail_next._counter + 1};
          if (tail_copy._pointer->_next.compare_exchange_weak(tail_next, new_tail_next)) {
            auto new_tail = Pointer{new_node, tail_copy._counter + 1};
            _tail.compare_exchange_weak(tail_copy, new_tail);
            break;
          }
        } else {
          auto new_tail = Pointer{new_node, tail_copy._counter + 1};
          _tail.compare_exchange_weak(tail_copy, new_tail);
        }
      }
    }
  }

  bool dequeue(int *ret) {
    while (true) {
      Pointer head_copy = _head.load();
      Pointer tail_copy = _tail.load();
      Pointer head_next_copy = head_copy._pointer->_next.load();
      if (head_copy == _head) {
        if (head_copy._pointer == tail_copy._pointer) {
          if (head_next_copy._pointer == nullptr) {
            return false;
          }
          auto new_tail = Pointer{head_next_copy._pointer, tail_copy._counter + 1};
          _tail.compare_exchange_weak(tail_copy, new_tail);
        } else {
          *ret = head_next_copy._pointer->_value;
          auto new_head = Pointer{head_next_copy._pointer, head_copy._counter + 1};
          if (_head.compare_exchange_weak(head_copy, new_head)) {
            break;
          }
        }
      }
    }
    return true;
  }
};

#endif //LOCK_FREE_PLAYGROUND_UBQUEUE_H
