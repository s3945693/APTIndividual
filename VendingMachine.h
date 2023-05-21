#ifndef VENDING_H
#define VENDING_H

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <filesystem>
#include <algorithm>
#include <cstddef>
#include "LinkedList.h"
#include "helper.h"
#include "Coin.h"
#include "doublyLinkedList.h"
#include "command.cpp"
using std::vector;
using std::string;
using std::map;
using std::cout;
using std::endl;
using std::cin;

class VendingMachine
{
    public:
        VendingMachine(string stockFile, string coinFile);

        ~VendingMachine();

        void start();

        LinkedList* stock_list;

        map<Denomination, int>* coin_map;

        void execute(Command& command);

        bool loadStock();

        bool loadCoin();

        void displayMenu();

        void displayItems();

        void displayCoins();

        void purchaseItem();

        void addItem();

        void resetCoinCount();

        void removeItem();

        void resetStock();

        void abort();

        void saveData();

        string giveChange(float change, map<Denomination, int>& coinMap);

        void updateCoins(map<Denomination, int>* purchaseMethodCoinMap, float userPayment);

        string stockFile;

        string coinFile;
};

#endif // VENDING_H