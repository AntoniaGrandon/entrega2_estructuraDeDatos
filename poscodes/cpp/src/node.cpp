#include "node.hpp"
#include <iostream>

Node::Node(): data(0), ptrNext(nullptr) {
}

Node::Node(size_t val, Node* next): data(val), ptrNext(next) {
}

void Node::setData(size_t _data){
    data = _data;
}

void Node::setNext(Node* next){
    ptrNext = next;
}

size_t Node::getData(){
    return data;
}

Node* Node::getNext(){
    return ptrNext;
}

void Node::print(){
    std::cout << data ;
}

Node::~Node() {
}
