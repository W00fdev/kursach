#ifndef KURSACH_LIST_H
#define KURSACH_LIST_H

template <typename double_or_char>
struct _node {
    double_or_char value;
    _node* next = nullptr;

    _node(double_or_char _value, _node* _next = nullptr) : value(_value), next(_next) {}
};

#endif //KURSACH_LIST_H
