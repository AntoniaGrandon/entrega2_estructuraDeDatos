#include <cstddef>

#ifndef NODE_HPP_
#define NODE_HPP_

class Node {
private:
    size_t data;
    Node* ptrNext;
public:
    Node();
    Node(size_t _data, Node* next = nullptr);
    void setData(size_t _data);
    void setNext(Node* _next);
    size_t getData();
    Node* getNext();
    void print();
    virtual ~Node();
};

#endif
