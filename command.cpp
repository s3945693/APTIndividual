#include <iostream>
#include <functional>
#include <string>
#include "VendingMachine.h"

class Command {
private:
    VendingMachine* vendingMachine;
public:
    Command(VendingMachine* vendingMachine) : vendingMachine(vendingMachine) {}
    virtual void execute() = 0;
protected:
    VendingMachine* getVendingMachine() { return vendingMachine; }
};


class DisplayItems : public Command {
public:
    DisplayItems(VendingMachine* vendingMachine) : Command(vendingMachine) {}
    void execute() override {
        getVendingMachine()->displayItems();
    }
};

class DisplayCoins : public Command {
public:
    DisplayCoins(VendingMachine* vendingMachine) : Command(vendingMachine) {}
    void execute() override {
        getVendingMachine()->displayCoins();
    }
};

class PurchaseItem : public Command {
public:
    PurchaseItem(VendingMachine* vendingMachine) : Command(vendingMachine) {}
    void execute() override {
        getVendingMachine()->purchaseItem();
    }
};

class AddItem : public Command {
public:
    AddItem(VendingMachine* vendingMachine) : Command(vendingMachine) {}
    void execute() override {
        getVendingMachine()->addItem();
    }
};

class ResetCoinCount : public Command {
public:
    ResetCoinCount(VendingMachine* vendingMachine) : Command(vendingMachine) {}
    void execute() override {
        getVendingMachine()->resetCoinCount();
    }
};

class RemoveItem : public Command {
public:
    RemoveItem(VendingMachine* vendingMachine) : Command(vendingMachine) {}
    void execute() override {
        getVendingMachine()->removeItem();
    }
};

class ResetStock : public Command {
public:
    ResetStock(VendingMachine* vendingMachine) : Command(vendingMachine) {}
    void execute() override {
        getVendingMachine()->resetStock();
    }
};

class Abort : public Command {
public:
    Abort(VendingMachine* vendingMachine) : Command(vendingMachine) {}
    void execute() override {
        getVendingMachine()->abort();
    }
};

class SaveData : public Command {
public:
    SaveData(VendingMachine* vendingMachine) : Command(vendingMachine) {}
    void execute() override {
        getVendingMachine()->saveData();
    }
};

class DisplayMenu : public Command {
public:
    DisplayMenu(VendingMachine* vendingMachine) : Command(vendingMachine) {}
    void execute() override {
        getVendingMachine()->displayMenu();
    }
};
