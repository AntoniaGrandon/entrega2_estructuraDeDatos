#include "linkedList.hpp"

LinkedList::LinkedList() : head(nullptr), tail(nullptr) {
}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* node = current;
        current = current->getNext();
        delete node;
    }
}

void LinkedList::add_last(size_t data) {
    Node* node = new Node(data);

    if (head == nullptr) { 
        head = node;
        tail = node;
    } else { 
        tail->setNext(node);
        tail = node; 
    }
}

Node* LinkedList::get_head(){
    return head;
}

