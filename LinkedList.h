#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include <string> 
#include "Coin.h"
#include <iostream>
#include <iomanip>
#include <fstream>

class LinkedList
{
public:
    LinkedList();
    virtual ~LinkedList();

    // more functions to be added perhaps...
    virtual void append(Node* node);
    virtual void insertStock(Stock* stock);
    virtual void remove(std::string id);
    virtual void printList();
    virtual Stock* getItemID(std::string id);
    int getCount();
    void resetStockCount();
    void saveStock(std::string stockFile);

private:
    // the beginning of the list
    Node* head;
    // the end of the list
    Node* tail;
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


