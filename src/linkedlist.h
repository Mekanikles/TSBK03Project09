#ifndef PROJECT_LINKEDLIST_H
#define PROJECT_LINKEDLIST_H

#include "stdlib.h"

template<typename T>
struct Node
{
    Node();
    
    Node<T>* next;
    Node<T>* prev;
    T item;
};

// Linked list class, uses Node class for nodes
template<typename T>
class LinkedList
{
public:    

    LinkedList();
    ~LinkedList();

    void addFirst(T item);
    Node<T>* getFirst();
    void remove(Node<T>* node);

protected:
private:    
 
    Node<T>* first;
    int size;
       
};

#include "linkedlist.hpp" 

#endif // PROJECT_LINKEDLIST_H
