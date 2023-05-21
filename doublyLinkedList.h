#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "Node.h"
#include <string> 
#include "Coin.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include "LinkedList.h"

class doublyLinkedList : public LinkedList{
public:
    doublyLinkedList();
    ~doublyLinkedList();

    // more functions to be added perhaps...
    void append(Node* node) override;
    void insertStock(Stock* stock) override;
    void remove(std::string id) override;
    void printList() override;
    Stock* getItemID(std::string id);
    int getCount();
    void resetStockCount();
    void saveStock(std::string stockFile);
private:
    // the beginning of the list
    Node* head;
    // the end of the list
    Node* tail;

    Node* middle;
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // DOUBLYLINKEDLIST_H
