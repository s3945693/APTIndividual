#include "DLL.h"
#include "Node.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;

#include "DLL.h"
#include "Node.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;

DLL::DLL() {
    // linked list constructor 
    head = nullptr;
    tail = nullptr;
}

DLL::~DLL() {
    // linked list deconstructor 
    Node *temp = this->head;
    while (temp != nullptr){
        Node *temp2 = (*temp).next;
        delete temp;
        temp = temp2;
    }
}

void DLL::append(Node* node){
    // add node to end of linked list
    if (this->head == nullptr){
        this->head = node;
        this->tail= node;
        count += 1;
    }
    else{
        (*tail).next = node;
        (*node).prev = this->tail;
        this->tail = node;
        count += 1;
    }
}

void DLL::insertStock(Stock* stock){
    // insert stock alphabetically by name
    Node* node = new Node(stock);
    if (this->head == nullptr){
        this->head = node;
        this->tail= node;
        count += 1;
    }
    
    else{
        if (this->head->name() > (*node).name()){
            (*node).next = this->head;
            (*head).prev = node;
            this->head = node;
            count += 1;
        }
        else{
            Node *temp = this->head;
            //int i =0;
            bool boolDone = false;
            while (temp != nullptr){
                
                if (temp == this->tail){
                    (*temp).next = node;
                    (*node).prev = temp;
                    this->tail = node;
                    count += 1;
                    boolDone = true;
                    temp = nullptr;
                    
                }
                else if (temp->next->name() > (*node).name()){
                    (*node).next = (*temp).next;
                    (*node).prev = temp;
                    node->next->prev = node;
                    (*temp).next = node;
                    count += 1;
                    boolDone = true;
                    temp = nullptr;
                }
                if (!boolDone){ temp = (*temp).next;}
                
            }
        }
    }
}

void DLL::remove(std::string id){
    // remove node based off id
    if (this->head == nullptr){
        return;
    }
    else{
        if ((*head).data->id == id){
            Node *temp = this->head;
            this->head = (*head).next;
            delete temp;
            this->head->prev = nullptr;
            count -= 1;
        }
        else if ((*tail).data->id == id){
            Node *temp = this->tail->prev;
            delete this->tail;
            this->tail = temp;
            
            (*temp).next = nullptr;
            count -= 1;
        }
        else{
            Node *temp = this->head;
            bool boolDone = false;
            while (temp != nullptr){
                //tail check if id is invalid
                if (tail == temp){
                    temp = nullptr;
                    boolDone = true;
                }
                else if ((*temp).data->id == id){
                    (*temp).prev->next = (*temp).next;
                    (*temp).next->prev = (*temp).prev;
                    count -= 1;
                    temp = nullptr;
                    boolDone = true;
                    
                }

                if (!boolDone){ temp = (*temp).next;}
            }
        }
    }
}

void DLL::printList(){
    // print stock
    std::cout << "Items Menu" << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << "ID   |Name                                    | Available | Price  " << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;
    Node *temp = this->head;
    while (temp != nullptr){
        // ID column, left-aligned, width 5
        std::cout << std::left << std::setw(5) << (*temp).data->id;

        // Name column, left-aligned, width 40
        std::cout << "|" << std::left << std::setw(40) << (*temp).data->name;

        // Available column, left-aligned, width 11
        std::cout << "|" << std::left << std::setw(11) << (*temp).data->on_hand;

        if((*temp).data->price.cents == 0) {
            std::cout << "|$ " << std::left << (*temp).data->price.dollars << "." << (*temp).data->price.cents << "0" << std::endl;
        } else {
            std::cout << "|$ " << std::left << (*temp).data->price.dollars << "." << (*temp).data->price.cents << std::endl;
        }

        // Move to the next node
        temp = (*temp).next;
    }
}


Stock* DLL::getItemID(string ID){
    // Get stock object based of id
    Node *temp = this->head;
    Stock *toReturn = nullptr;
    bool boolDone = false;
    while (temp != nullptr){
        if ((*temp).data->id == ID){
            toReturn = temp->data;
            temp = nullptr;
            boolDone = true;
        }
        if (!boolDone){ temp = (*temp).next;}
    }
    return toReturn;
}

int DLL::getCount(){
    return count;
}

void DLL::resetStockCount() {
    // reset stock count
    Node *temp = this->head;
    while(temp != nullptr) {
        temp->data->on_hand = DEFAULT_STOCK_LEVEL;
        temp = temp->next;
    }
}

void DLL::saveStock(string _stockFile) {
    // save stock back to stock file that was loaded
    std::ofstream stockFile(_stockFile);
    Node* temp = this->head;
    while(temp != nullptr) {
        Stock* item = temp->data;
        stockFile << item->id << "|" << item->name << "|" << item->description << "|" << item->price.dollars << "." << std::fixed << std::setprecision(2) << item->price.cents << "|" << item->on_hand << endl;
        temp = temp->next;
    }
    stockFile.close();
}