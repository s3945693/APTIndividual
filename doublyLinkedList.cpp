#include "doublyLinkedList.h"
#include "Node.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;

doublyLinkedList::doublyLinkedList() {
    // linked list constructor 
    head = nullptr;
    middle = nullptr;
    tail = nullptr;
}

doublyLinkedList::~doublyLinkedList() {
    // linked list deconstructor 
    Node *temp = this->head;
    while (temp != nullptr){
        Node *temp2 = (*temp).next;
        delete temp;
        temp = temp2;
    }
}

void doublyLinkedList::append(Node* node){
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

void doublyLinkedList::insertStock(Stock* stock)  {
    // insert stock alphabetically by name
    Node* node = new Node(stock);
    //insertion at head if head is null
    if (this->head == nullptr){
        this->head = node;
        this->middle = node;
        this->tail= node;
        count += 1;
    }
    
    else{
        //insertion at head 
        if (this->head->name() > (*node).name()){
            (*node).next = this->head;
            (*head).prev = node;
            this->head = node;
            //ensuring middle is consistent
            if (count % 2 == 1){this->middle = this->middle->prev;}
            count += 1;
        }
        //insertion at tail
        else if (this->tail->name() < (*node).name()){
            (*tail).next = node;
            (*node).prev = this->tail;
            this->tail = node;
            //ensuring middle is consistent
            if (count % 2 == 0){this->middle = this->middle->next;}
            count += 1;
        }
        else{
            Node* temp = this->head;
            bool boolDone = false;
            bool changeToTail = false;
            while (temp != nullptr){
                //if name value is lower than middle, insert from head
                if (middle->name() > node->name()){
                    if (temp->name() > node->name()){
                        (*node).next = temp;
                        (*node).prev = temp->prev;
                        (*temp).prev->next = node;
                        (*temp).prev = node;
                        count += 1;
                        //ensuring middle is consistent
                        if (count % 2 == 1){this->middle = this->middle->prev;}
                        temp = nullptr;
                        boolDone = true;
                    }
                    if (!boolDone){ temp = (*temp).next;}
                }
                else{
                    if(!changeToTail){
                        temp = this->tail;
                        changeToTail = true;
                    }
                    //since middle is lower than node, insert from tail
                    if(temp->name() < node->name()){
                        temp->next->prev = node;
                        node->next = temp->next;
                        temp->next = node;
                        node->prev = temp;
                        count += 1;
                        //ensuring middle is consistent
                        if (count % 2 == 0){this->middle = this->middle->next;}
                        temp = nullptr;
                        boolDone = true;
                    }
                    if (!boolDone){ temp = (*temp).prev;}
                }
                
                
            }
        }
    }
    //this next line is to ensure the middle is what i expect it to be
    //cout << "Middle: " << middle->name() << endl;
}

void doublyLinkedList::remove(std::string id){
    // remove node based off id
    if (this->head == nullptr){
        return;
    }
    else{
        if (count == 1){
            delete this->head;
            this->head = nullptr;
            this->tail = nullptr;
            this->middle = nullptr;
            count -= 1;
        }
        //removal at head
        else if ((*head).data->id == id){
            Node *temp = this->head;
            this->head = (*head).next;
            delete temp;
            this->head->prev = nullptr;
            count -= 1;
            //ensuring middle is consistent
            if (count % 2 == 0){this->middle = this->middle->next;}
        }
        else if ((*tail).data->id == id){
            Node *temp = this->tail->prev;
            //middle consisten up high so no seg fault by accessing a null value (if tail was middle)
            count -= 1;
            if (count % 2 == 1){this->middle = this->middle->prev;}
            delete this->tail;
            this->tail = temp;
            (*temp).next = nullptr;
            
        }
        else{
            Node *temp = this->head;
            bool boolDone = false;
            while (temp != nullptr){
                if ((*temp).data->id == id){

                    count -= 1;
                    if (middle->name() > temp->name()){
                        if (count % 2 == 0){this->middle = this->middle->next;}
                    }
                    else{
                        if (count % 2 == 1){this->middle = this->middle->prev;}
                    }
                    (*temp).prev->next = (*temp).next;
                    (*temp).next->prev = (*temp).prev;
                    delete temp;
                    temp = nullptr;
                    boolDone = true;
                }
                if (!boolDone){ temp = (*temp).next;}
            }
        }
    }
}

void doublyLinkedList::printList(){
    // print stock
    std::cout << "Items Menu" << std::endl;
    std::cout << "----------" << std::endl;
    std::cout << "ID   |Name                                    | Available | Price  " << std::endl;
    std::cout << "-------------------------------------------------------------------" << std::endl;
    Node *temp = this->head;
    cout<< "Stupid" << endl;
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


Stock* doublyLinkedList::getItemID(string ID){
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

int doublyLinkedList::getCount(){
    return count;
}

void doublyLinkedList::resetStockCount() {
    // reset stock count
    Node *temp = this->head;
    while(temp != nullptr) {
        temp->data->on_hand = DEFAULT_STOCK_LEVEL;
        temp = temp->next;
    }
}

void doublyLinkedList::saveStock(string _stockFile) {
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
