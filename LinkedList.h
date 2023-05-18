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
    ~LinkedList();

    // more functions to be added perhaps...
    void append(Node* node);
    void insert(Node* node);
    void insertStock(Stock* stock);
    void remove(std::string id);
    void printList();
    void addItem();
    Stock* getItemID(std::string id);
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


