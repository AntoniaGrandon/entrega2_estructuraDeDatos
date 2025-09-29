#ifndef LINKEDLIST_HPP_
#define LINKEDLIST_HPP_

#include "node.hpp"

class LinkedList {
private:
    Node* head;
    Node* tail;

public:
    LinkedList();
    ~LinkedList();
    void add_last(size_t data);
    Node* get_head();
};

#endif