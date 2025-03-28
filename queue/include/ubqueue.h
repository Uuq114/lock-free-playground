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
        Node dummy(-1);
        _head.store(Pointer{&dummy, 0});
        _tail.store(Pointer{&dummy, 0});
    };

    ~UBQueue() {
        while(dequeue()) {}
        delete _head.load()._pointer;
    }

    void enqueue(int value) {
        Node* node = new Node(value);
        Pointer tail_copy = _tail.load();
        Pointer next = tail_copy._pointer->_next.load();
        while (true) {
            if(tail_copy == _tail.load()) {
                if(next._pointer == nullptr) {
                    Pointer new_next =
                }
            }
        }
    }

    int dequeue() {

    }
};

#endif //LOCK_FREE_PLAYGROUND_UBQUEUE_H
