#include <vector>
#include "Node.h"

#pragma once


using namespace std;

template<class ItemType>
class SortedDoublyLinkedList {
    //DO NOT MODIFY THIS CLASS DECLARATION. FIND T-O-D-O-S to work on.
private:
    Node<ItemType> *head;
    Node<ItemType> *tail;
    int size;
public:

    SortedDoublyLinkedList();

    SortedDoublyLinkedList(Node<ItemType> *head, Node<ItemType> *tail, int size);

    SortedDoublyLinkedList(const SortedDoublyLinkedList<ItemType> &list);    // Copy constructor

    Node<ItemType> *getPointerTo(const ItemType &target) const;

    virtual ~ SortedDoublyLinkedList();    // Destructor should be virtual

    int getCurrentSize() const;

    bool isEmpty() const;

    bool add(const ItemType &newEntry);

    bool remove(const ItemType &anEntry);

    bool contains(const ItemType &anEntry) const;

    int getFrequencyOf(const ItemType &anEntry) const;

    vector<ItemType> toVector() const;

};

template<class ItemType>
SortedDoublyLinkedList<ItemType>::SortedDoublyLinkedList() : head(nullptr), tail(nullptr),
                                                             size(0) { }

template<class ItemType>
SortedDoublyLinkedList<ItemType>::SortedDoublyLinkedList(Node<ItemType> *head, Node<ItemType> *tail, int size) :
        head(head), tail(tail), size(size) { }

template<class ItemType>
SortedDoublyLinkedList<ItemType>::SortedDoublyLinkedList(const SortedDoublyLinkedList<ItemType> &list) {
    size = list.size;
    Node <ItemType> *chain1 = list.head;
    if(chain1 == nullptr){
        head = nullptr;
    }
    else{
        head = new Node<ItemType>();
        head->setItem(chain1->getItem());

        Node<ItemType> *chain2 = head;// for the last node in new chain
        chain1 = chain1->getNext();

        while (chain1 != nullptr){    // when traversing, keep a pointer to count
            ItemType nextVal = chain1->getItem(); //next value from the list
            Node<ItemType> *newNodePtr = new Node<ItemType>(nextVal); //makes a new node from the next value
            chain2->setNext(newNodePtr); //new node that'll link to the end
            chain2 = chain2->getNext(); //putting the pointer to the last node
            chain1 = chain1->getNext();
        }

        chain2->setNext(nullptr);
    }
}

template<class ItemType>
Node<ItemType> *SortedDoublyLinkedList<ItemType>::getPointerTo(const ItemType &target) const {
    bool isFound = false;
    Node<ItemType> *current = head;

    while ((current != nullptr) && !isFound) {
        if (target == current->getItem()){
            isFound = true;
        }
        else{
            current = current->getNext();
        }
    }
    return current;
}

template<class ItemType>
SortedDoublyLinkedList<ItemType>::~SortedDoublyLinkedList() { //Implement the destructor
    Node<ItemType> *deletedNode = head;

    while (head != nullptr) {
        head = head->getNext();
        deletedNode->setNext(nullptr);
        delete deletedNode;

        deletedNode = head;
    }
    size = 0;
}

template<class ItemType>
int SortedDoublyLinkedList<ItemType>::getCurrentSize() const {//Return the current size
    return size;
}

template<class ItemType>
bool SortedDoublyLinkedList<ItemType>::isEmpty() const {//Return True if the list is empty
    return (head == nullptr && tail == nullptr);
}

template<class ItemType>
bool SortedDoublyLinkedList<ItemType>::add(const ItemType &newEntry) { //sorted insertion
    Node<ItemType> *current;
    Node<ItemType> *newNode = new Node<ItemType>(newEntry);
    if(head == nullptr ){ // if empty
        newNode->setNext(head);
        newNode->setPrev(nullptr);
        head = tail =  newNode;
    }

    else if(head->getItem() >= newEntry){ //adding before head
        newNode->setNext(head);
        newNode->setPrev(nullptr);
        head = newNode;
    }

    else {
        current =head;

        while(current->getNext()!=nullptr && current->getNext()->getItem() < newNode->getItem()){
            current = current->getNext();
        }

        newNode->setNext(current->getNext());
        newNode->setPrev(current);
        current->setNext(newNode);
    }
    size++; //add to amount of items in list

    return true;
}

template<class ItemType>
bool SortedDoublyLinkedList<ItemType>::remove(const ItemType &anEntry) {
    Node<ItemType> *entryRemPtr = getPointerTo(anEntry);
    bool removable = !isEmpty() && (entryRemPtr != nullptr);
    if (removable) {
        entryRemPtr->setItem(head->getItem()); //the found node will get the data from the first node


        Node<ItemType> *delPtr = head;//getting rid of the first node
        head = head->getNext();

        delPtr->setNext(nullptr);
        delete delPtr;
        delPtr = nullptr;

        size--; //decrease amount of items in the list
    }
    return removable;
}

template<class ItemType>
bool SortedDoublyLinkedList<ItemType>::contains(const ItemType &anEntry) const {//Check if the List contains the Item(anEntry)- Return true if successful
    return (getPointerTo(anEntry) != nullptr);
}

template<class ItemType>
int SortedDoublyLinkedList<ItemType>::getFrequencyOf(const ItemType &anEntry) const {
    int frequency = 0;
    int count = 0;
    Node<ItemType> *current = head;

    while ((current != nullptr) && (count < size)) {
        if (anEntry == current->getItem()) {
            frequency++;
        }
        count++;
        current = current->getNext();
    }
    return frequency;
}

template<class ItemType>
vector<ItemType> SortedDoublyLinkedList<ItemType>::toVector() const {
    // DO NOT MODIFY THIS FUNCTION
    vector <ItemType> myVector;
    Node<ItemType> *cur;
    cur = this->head;
    while (cur != nullptr) {
        myVector.push_back(cur->getItem());
        cur = cur->getNext();
    }
    return myVector;
}

