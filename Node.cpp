#include "Node.h"

Node::Node(){
    data = new Stock;
    next = nullptr;
    prev = nullptr;
};

Node::Node(Stock* stock){
    data = stock;
    next = nullptr;
    prev = nullptr;
};

Node::~Node(){
    delete data;
};

std::string Node::name(){
    return this->data->name;
}