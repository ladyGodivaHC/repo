#ifndef GENERICCONTAINER_H
#define GENERICCONTAINER_H

#include "searchfunctor.h"
#include "modifyfunctor.h"
#include <iostream>

/* Inclusion method, no inline definition */

template <class K>
class GenericContainer{

    friend class ContainerIterator;

private:

    class Node;

    class SmartNode{
    public:
        Node* pointer;
        SmartNode(Node* p=0);
        SmartNode(const SmartNode& p);
        ~SmartNode();
        SmartNode& operator= (const SmartNode& p);
        Node& operator*() const;
        Node* operator->() const;
        bool operator==(const SmartNode& p) const;
        bool operator!=(const SmartNode& p) const;
    };
    class Node{
    public:
        Node();
        Node(const K& obj, const SmartNode& p);
        K info;
        SmartNode next;
        int ref;
    };

    SmartNode first;

public:

    //as i'm defining a custom container i need a custom iterator to iterate the elements
    class ContainerIterator{
        friend class GenericContainer;
    private:
        GenericContainer::SmartNode p;
    public:
        bool operator==(ContainerIterator& it) const;
        bool operator!=(const ContainerIterator& it) const;
        ContainerIterator& operator++();
        ContainerIterator operator++(int i);
    };
    ContainerIterator begin() const;
    ContainerIterator end() const;
    K& operator[](ContainerIterator it) const;

    void add(const K& obj);
    void remove(const K& obj);

};

/* Methods definition */

//Defining SmartNode constructor
template<class K>
GenericContainer<K>::SmartNode::SmartNode(Node* p) : pointer(p){ if(pointer) pointer->ref++; }

//defining SmartNode copy constructor
template<class K>
GenericContainer<K>::SmartNode::SmartNode(const SmartNode& p) : pointer(p.pointer){ if(pointer) pointer->ref++; }

//defining SmartNode destroyer
template<class K>
GenericContainer<K>::SmartNode::~SmartNode(){
    if(pointer){
        pointer->ref--;
        if(pointer->ref == 0)
            delete pointer;
    }
}

//re-defining SmartNode's = operator
template<class K>
typename GenericContainer<K>::SmartNode& GenericContainer<K>::SmartNode::operator= (const SmartNode& p){
    if(this!=&p){
        Node* temp = pointer;
        pointer = p.pointer;
        if(pointer)
            pointer->ref++;
        if(temp){
            temp->ref--;
            if(temp->ref == 0)
                delete temp;
        }
    }
    return *this;
}

//re-defining SmartNode's operator*
template<class K>
typename GenericContainer<K>::Node& GenericContainer<K>::SmartNode::operator*() const{ return *pointer; }

//re-defining SmartNode's operator->
template<class K>
typename GenericContainer<K>::Node* GenericContainer<K>::SmartNode::operator->() const{ return pointer; }

//re-defining SmartNode's operator==
template<class K>
bool GenericContainer<K>::SmartNode::operator==(const SmartNode& p) const { return pointer == p.pointer; }

//re-defining SmartNode's operator!=
template<class K>
bool GenericContainer<K>::SmartNode::operator!=(const SmartNode& p) const { return pointer != p.pointer; }

//defining Node constructor
template<class K>
GenericContainer<K>::Node::Node() : ref(0) {}

//defining 2 parameter Node's constructor
template<class K>
GenericContainer<K>::Node::Node(const K& obj, const SmartNode& p) : info(obj), next(p), ref(0) {}

//defining ContainerIterator operator==
template<class K>
bool GenericContainer<K>::ContainerIterator::operator==(ContainerIterator& it) const{ return p==it.p;}

//defining ContainerIterator operator!=
template<class K>
bool GenericContainer<K>::ContainerIterator::operator!=(const ContainerIterator& it) const{ return p!=it.p;}

//defining ContainerIterator operator++()
template<class K>
typename GenericContainer<K>::ContainerIterator& GenericContainer<K>::ContainerIterator::operator++(){
    if(p!=0)
        p=p->next;
    return *this;
}

//defining ContainerIterator operator++(int)
template<class K>
typename GenericContainer<K>::ContainerIterator GenericContainer<K>::ContainerIterator::operator++(int i){
    ContainerIterator aux=*this;
    if(p!=0)
        p=p->next;
    return aux;
}

//defining ContainerIterator's begin() and end() methods
template<class K>
typename GenericContainer<K>::ContainerIterator GenericContainer<K>::begin() const{
    ContainerIterator aux;
    aux.p=first;
    return aux;
}

template<class K>
typename GenericContainer<K>::ContainerIterator GenericContainer<K>::end() const{
    ContainerIterator aux;
    aux.p=0;
    return aux;
}

//defining member access operator[]
template<class K>
K& GenericContainer<K>::operator[](ContainerIterator it) const{
    return (it.p)->info;
}

//defining add method to add a new element to the container
template<class K>
void GenericContainer<K>::add(const K& obj){
        first = new Node(obj, first);
}

//defining remove method to remove an element from the container
template<class K>
void GenericContainer<K>::remove(const K& obj){
    SmartNode p = first, prec, original = first;
    bool found = false;
    while(p!=0 && !found){
        //if i find the node i'm looking for
        if(p->info == obj){
            found = true;
            //if node is the first node i only move first to first->next. The old first node is automatically deleted
            if(prec == 0)
                first = original->next;
            else
                //otherwise i just "skip" a node, which is automatically deleted
                prec->next = p->next;
        }
        else{
            //if i didn't find the node, i update values and move to the next node
            prec = p;
            p = p->next;
        }
    }
}


#endif // GENERICCONTAINER_H
