#include "stdlib.h"

#include "stdio.h"

template<typename T>
Node<T>::Node():
    next(NULL), prev(NULL), item(NULL)
{
}


template<typename T>
LinkedList<T>::LinkedList():
    first(NULL), size(0)
{   
   
}


template<typename T>
LinkedList<T>::~LinkedList()
{
    Node<T>* t;
    Node<T>* n = this->first;
    while (NULL != n)
    {   
        t = n->next;
        delete n;
        n = t;
    }
}

template<typename T>
void LinkedList<T>::addFirst(T item)
{
    fprintf(stderr, "trying to add to list\n");
    Node<T>* node = new Node<T>();
    node->item = item;
    
    if (NULL != first)
    {
        first->prev = node;
    }
    
    node->next = this->first;
    this->first = node;
}

template<typename T>
Node<T>* LinkedList<T>::getFirst()
{
    return this->first;
}

template<typename T>
void LinkedList<T>::remove(Node<T>* node)
{
    if (NULL != node->prev)
    {
        node->prev->next = node->next;
    }
    else
    {
        this->first = node->next;
    }
    
    if (NULL != node->next)
    {
        node->next->prev = node->prev;
    }
    
    delete node;
}




