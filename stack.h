#ifndef KURSACH_STACK_H
#define KURSACH_STACK_H

#include "list.h"

template <typename double_or_char>
class _stack {
private:
    _node<double_or_char>* head = nullptr;
    size_t size = 0;
public:
    _stack(_node<double_or_char>* start) : head(start), size(1u) {}
    _stack() {}

    ~_stack() {
        _node<double_or_char>* searcher = head;

        while (searcher != nullptr) {
            _node<double_or_char>* to_delete = searcher;
            searcher = searcher->next;
            delete to_delete;
        }
    }

    void push(double_or_char new_value) {
        head = new _node<double_or_char>(new_value, head);
        size++;
    }

    double_or_char pop() {
        _node<double_or_char>* to_delete = head;
        double_or_char popping_value = to_delete->value;
        head = head->next;
        size--;
        delete to_delete;
        return popping_value;
    }
    
    double_or_char& top() {
        return head->value;
    }

    size_t get_size() const {
        return size;
    }

};

#endif //KURSACH_STACK_H
