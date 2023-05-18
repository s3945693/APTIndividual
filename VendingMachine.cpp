#include "VendingMachine.h"

VendingMachine::VendingMachine(string stockFile, string coinFile)
{   
    coin_map = new map<Denomination, int>;
    stock_list = new LinkedList();

    this->stockFile = stockFile;
    this->coinFile = coinFile;
}

VendingMachine::~VendingMachine()
{
    delete stock_list;
    
    delete coin_map;
}

void VendingMachine::start()
{
    bool endLoop = false;

    // check if files valid
    if (!loadStock() || !loadCoin()){
        // don't start, exit instead
        endLoop = true;
    }

    while(!endLoop && !cin.eof()) {
        // Print main menu 
        displayMenu();
        // get user input
        string input = Helper::readInput();
        int userMenu = 0;
        //checking if input is a number
        bool isNumber = Helper::isNumber(input);
        if (isNumber == false) {
            Helper::printInvalidInput();
        }
        else{
            userMenu = stoi(input);
            //ensuring number is within valid range
            if (userMenu > 0 && userMenu < 10) {
                // Display Items
                if(userMenu == 1) {
                    this->displayItems();
                // Purchase Item
                } else if(userMenu == 2) {
                    this->purchaseItem();
                // Save and exit
                } else if(userMenu == 3) {
                    cout << "Saving Data..." << endl;
                    this->saveData();
                    cout << "Data Saved!\n" << endl;
                    cout << "Goodbye!" << endl;
                    endLoop = true;
                // Add item
                } else if(userMenu == 4) {
                    this->addItem();
                // Remove item
                } else if(userMenu == 5) {
                    this->removeItem();
                }
                // Display coins
                else if(userMenu == 6) {
                    this->displayCoins();
                // Reset stock
                } else if(userMenu == 7) {
                    this->resetStock();
                } 
                // Reset coins
                else if(userMenu == 8) {
                    this->resetCoinCount();
                } 
                // Abort
                else if(userMenu == 9) {
                    this->abort();
                    endLoop = true;
                }
            }
        }
    }
}

void VendingMachine::displayMenu()
{
    // display menu options
    cout << "\nMain Menu"  << endl;
    cout << "    1. Display Items" << endl;
    cout << "    2. Purchase Items" << endl;
    cout << "    3. Save and Exit" << endl;
    cout << "Administrator-Only Menu:" << endl;
    cout << "    4. Add Item" << endl;
    cout << "    5. Remove Item" << endl;
    cout << "    6. Display Coins" << endl;
    cout << "    7. Reset Stock" << endl;
    cout << "    8. Reset Coins" << endl;
    cout << "    9. Abort Program" << endl;
    cout << endl;
    cout << "Select your option (1-9): ";
}

void VendingMachine::displayItems()
{
    stock_list->printList();
}

void VendingMachine::displayCoins()
{
    // display coin amounts
    cout << "Coins Summary" << endl;
    cout << "-------------" << endl;
    cout << "Denomination    |    Count" << endl;
    cout << "---------------------------" << endl;
    cout << "5 Cents                  " << (*coin_map)[FIVE_CENTS] << endl;
    cout << "10 Cents                 " << (*coin_map)[TEN_CENTS] << endl;
    cout << "20 Cents                 " << (*coin_map)[TWENTY_CENTS] << endl;
    cout << "50 Cents                 " << (*coin_map)[FIFTY_CENTS] << endl;
    cout << "1 Dollars                " << (*coin_map)[ONE_DOLLAR] << endl;
    cout << "2 Dollars                " << (*coin_map)[TWO_DOLLARS] << endl;
    cout << "5 Dollars                " << (*coin_map)[FIVE_DOLLARS] << endl;
    cout << "10 Dollars               " << (*coin_map)[TEN_DOLLARS] << endl;
}

void VendingMachine::resetCoinCount()
{
    // reset coin amounts to specified DEFAULT_COIN_COUNT 
    (*coin_map)[TEN_DOLLARS] = DEFAULT_COIN_COUNT;
    (*coin_map)[FIVE_DOLLARS] = DEFAULT_COIN_COUNT;
    (*coin_map)[TWO_DOLLARS] = DEFAULT_COIN_COUNT;
    (*coin_map)[ONE_DOLLAR] = DEFAULT_COIN_COUNT;
    (*coin_map)[FIFTY_CENTS] = DEFAULT_COIN_COUNT;
    (*coin_map)[TWENTY_CENTS] = DEFAULT_COIN_COUNT;
    (*coin_map)[TEN_CENTS] = DEFAULT_COIN_COUNT;
    (*coin_map)[FIVE_CENTS] = DEFAULT_COIN_COUNT;
    cout << "All coins has been reset to the default amount of " << DEFAULT_COIN_COUNT << "." << endl;
}

void VendingMachine::purchaseItem()
{
    // purchase and item
    cout << "Purchase Item" << endl;
    cout << "-------------" << endl;
    cout << "Please enter the id of the item you wish to purchase: ";
    // Get itemID
    string itemID = Helper::readInput();
    // Convert itemID to all uppercase
    for (auto& c : itemID) {
        c = std::toupper(c);
    }

    /*
        Travserse through linkedlist, the linked list stores nodes that are stock objects
        A method should be created, that returns the found node, a found node is a node that has
        matching itemID. 
        
        The foundStock should store the returned Stock* if it is found, the return will be NOT a
        nullptr. 
        itemID is already converted to all caps:
            If i0001 is entered, I0001 will be read so it will match the data in the nodes
            all other cases will return a nullptr
    */

    Stock* foundStock = stock_list->getItemID(itemID);

    // if found and stock on hand
    if(foundStock != nullptr && foundStock->on_hand > 0)
    {
        cout << "You have selected \"" << foundStock->name << " - " << foundStock->description 
        << "\". This will cost you $ " << foundStock->price.dollars 
        << "." << foundStock->price.cents << "." << endl;

        cout << "Please hand over the money - type in the value of each note/coin in cents." << endl;
        cout << "Please enter or ctrl-d on a new line to cancel this purchase:" << endl;

        // Get the item price and convert it to cents
        unsigned int dollars = foundStock->price.dollars;
        unsigned int cents = foundStock->price.cents;
        unsigned int itemInCents = (dollars * 100) + cents;

        // total payment received in cents
        unsigned int payment = 0;

        // remaining amount due in cents 
        float remaining = itemInCents;

        // Create a copy of coin_map
        map<Denomination, int>* purchaseMethodCoinMap = new map<Denomination, int>(*coin_map);

        bool endLoop = false;
        while(remaining > 0 && !endLoop)
        {
            cout << "You still need to give us $" << std::fixed << std::setprecision(2) << remaining / 100 << ": ";
            string input = Helper::readInput();
            // Check if user pressed Ctrl+D
            if(std::cin.eof()) {
                endLoop = true;
                std::cout << std::endl;
                // EXIT_SUCCESS;
            } else if(input.empty()) {
                // User pressed enter, refunding all the coins
                endLoop = true;
            } else {
                float userPayment = 0;
                try {
                    userPayment = std::stoul(input);
                } 
                catch (const std::invalid_argument& ex) {
                    Helper::printInvalidInput();
                    cout << "Please enter a valid integer." << endl;
                }
                catch (const std::out_of_range& ex) {
                    Helper::printInvalidInput();
                    cout << "Please enter a valid integer within range." << endl;
                }

                if(userPayment <= 0) {
                    Helper::printInvalidInput();
                    cout << "Please enter a postive amount." << endl;
                // check payment is valid denomiation
                } else if(userPayment != 5 && userPayment != 10 && userPayment != 20 && userPayment != 50 && 
                        userPayment != 100 && userPayment != 200 && userPayment != 500 && userPayment != 1000) {
                    cout << "Error: $" << std::fixed << std::setprecision(2) << userPayment / 100 << " is not a valid denomination of money. Please try again." << endl;
                } else {
                    payment += userPayment;
                    remaining -= userPayment;

                    // Call the update coin to update the count, i.e., the number of coins the vending machine has on hand
                    // The copy of the coin map is passed through with the userPayment
                   updateCoins(purchaseMethodCoinMap, userPayment);

                    // if not given exact amount of money, give change
                    if(remaining <= 0) {

                        // calculate the change
                        float change = payment - itemInCents;
                        
                        if(change > 0) {
                            // This method needs to calculate the change based on what is avaiable in the coins
                            // returns empty string if didn't have enough change
                            string formattedChange = this->giveChange(change, *purchaseMethodCoinMap);
                            if (!formattedChange.empty()){
                                cout << "Here is your " << foundStock->name << " and your change of $ " << std::fixed 
                                << std::setprecision(2) << change / 100 << ": " << formattedChange << endl;
                                
                                // Update the coin_map to be the purchaseMethodCoinMap
                                coin_map->swap(*purchaseMethodCoinMap);
                                // Dispense item
                                foundStock->on_hand--;
                            } else {
                                cout << "Sorry, not enough change. Transaction reverted." << endl;
                            }
                        } else {
                            // Dispense item
                            foundStock->on_hand--;

                            // Update the coin_map to be the purchaseMethodCoinMap
                            coin_map->swap(*purchaseMethodCoinMap);

                            cout << "Here is your " << foundStock->name << endl;
                        }
                    }
                }
            }
        }

        delete purchaseMethodCoinMap;
        
    } else {
        cout << "Invalid itemID" << endl;
    }
}

void VendingMachine::addItem()
{
    // add item to stock list
    string id;
    if (stock_list->getCount() < 9 ){
        id = "I000";
    }
    else{
        id = "I00";
    }
    cout<< "The id for the new item will be "<< id << stock_list->getCount()+1 << endl;
    cout << "Enter the name of the item: ";
    string name= Helper::readInput();
    
    while (name.length() > NAMELEN){
        cout << "Name is too long, please enter a name with less than " << NAMELEN << " characters: ";
        cin >> name;
    }

    cout << "Enter the description of the item: ";
    string description= Helper::readInput();
    while (description.length() > DESCLEN){
        cout << "Description is too long, please enter a description with less than " << DESCLEN << " characters: ";
        cin >> description;
    }
    cout << "Enter the price of the item: ";
    string dollars = Helper::readInput();
    vector<string> split;
    //split the string into dollars and cents
    Helper::splitString(dollars,split, ".");
   
    //check if the price is valid
    while (split.size() != 2 || !Helper::isNumber(split[0]) || !Helper::isNumber(split[1])){
        cout << "Not a valid price, please enter a valid price: ";
        dollars = Helper::readInput();
        Helper::splitString(dollars,split, ".");
    }
    // create new stock
    Stock *temp = new Stock();
    temp->id = id + std::to_string(stock_list->getCount()+1);
    temp->name = name;
    temp->description = description;
    temp->price.dollars = stoi(split[0]);
    temp->price.cents = stoi(split[1]);
    temp->on_hand = DEFAULT_STOCK_LEVEL;
    stock_list->insertStock(temp);
    cout << "This item \"" << name << " - " << description << "\" has now been added to the menu." << endl;
}

void VendingMachine::removeItem()
{
    // remove stock from stock list

    cout << "Enter the itemID of the item you want to remove: ";
    string id = Helper::readInput();

    // Convert id to all uppercase
    for (auto& c : id) {
        c = std::toupper(c);
    }
    // find stock
    Stock* foundStock = stock_list->getItemID(id);
    if(foundStock != nullptr) {
        string itemID = foundStock->id;
        string itemName = foundStock->name;
        string itemDescription = foundStock->description;

        stock_list->remove(id);

        cout << "\"" << itemID << " - " << itemName << " - " << itemDescription << "\"" << " has been removed from the system." << endl;
        
    } else {
        Helper::printInvalidInput();
        cout << "Item id does not exist" << endl;
    }
}

void VendingMachine::resetStock()
{
    // reset stock count of all stock to default
    stock_list->resetStockCount();
    cout << "''All stock has been reset to the default level of X''" << endl;
}

bool VendingMachine::loadStock()
{
    bool loadSuccess = true;

    std::ifstream file(stockFile);
    // check file opened successfully 
    if (file.is_open()){
        std::string line;

        while (std::getline(file, line)) 
        {
            // Seperating the string
            std::stringstream ss(line);
            std::vector<std::string> tokens;
            std::string token;

            while (std::getline(ss, token, '|')) {
                tokens.push_back(token);
            }

            
            // Check correct amount of fields
            if (tokens.size() != 6) {
                loadSuccess = false;
                cout << "ERROR: Incorrect amount fields in stock entry" << endl;
            }

            // TODO 
            // CHECK POSITION 1 if IT IS IN THE 2D ARRAY, IF YES NEW LIST, IF NOT, NO NEW LIST
            // Check float/int for price
            else if (!Helper::isNumber(tokens[4])){
                loadSuccess = false;
                cout << "ERROR: Price is not a number." << endl;
            }
            // Check int for stock
            else if (!(Helper::isNumber(tokens[5]) && tokens[4].find(".") == std::string::npos)){
                loadSuccess = false;
                cout << "ERROR: Stock amount is not a integer." << endl;
            }
            else {
                // put into stock list

                Stock* data = new Stock;

                data->id = tokens[1];
                data->name = tokens[2];
                data->description = tokens[3];
                
                // Seperating the Dollar and Cent
                int tempDollar = std::stoi(tokens[4]);
                float tempPrice = std::stof(tokens[4]);
                int result = static_cast<int>((tempPrice - tempDollar) * 100);

                data->price.dollars = tempDollar;
                data->price.cents =  result;

                data->on_hand = std::stoul(tokens[5]);

                stock_list->insertStock(data);
            }
        }
        file.close();

    } else {
        cout << "Could not open coin file. '" << stockFile << "' not found" << endl;
        loadSuccess = false;
    }

    return loadSuccess;
}

bool VendingMachine::loadCoin()
{
    bool loadSuccess = true;

    // Open the file for reading
    std::ifstream file(coinFile);
    // check file opened successfully 
    if (file.is_open()){
        std::string line;
        int line_count = 0;
        while (std::getline(file, line))
        {
            // split line
            std::vector<string> tokens;
            Helper::splitString(line, tokens, DELIM);
            // check splits into two ints
            if (tokens.size() == 2
            && Helper::isNumber(tokens[0]) && tokens[0].find(".") == std::string::npos
            && Helper::isNumber(tokens[1]) && tokens[1].find(".") == std::string::npos){
                // add to coin map
                (*coin_map)[static_cast<Denomination>(line_count)] = stoi(tokens[1]);
                
            } else {
                loadSuccess = false;
                cout << "ERROR: Incorret coin format" << endl;
            }
            ++line_count;
        }
        file.close();

        // check correct amount of rows
        if (line_count != 8) {
            loadSuccess = false;
            cout << "ERROR: Incorret number of rows in coin file" << endl;
        }

    } else {
        cout << "Could not open coin file. '" << coinFile << "' not found" << endl;
        loadSuccess = false;
    }

    return loadSuccess;
}

void VendingMachine::saveData()
{
    // save coin and stock data to respective .dat files

    // save coin data
    std::ofstream outfile;
    // open the coin file
    // outfile.open("text.txt"); 
    outfile.open(coinFile); 
    // write to file
    outfile << "1000," << (*coin_map)[TEN_DOLLARS] << endl;
    outfile << "500," << (*coin_map)[FIVE_DOLLARS] << endl;
    outfile << "200," << (*coin_map)[TWO_DOLLARS] << endl;
    outfile << "100," << (*coin_map)[ONE_DOLLAR] << endl;
    outfile << "50," << (*coin_map)[FIFTY_CENTS] << endl;
    outfile << "20," << (*coin_map)[TWENTY_CENTS] << endl;
    outfile << "10," << (*coin_map)[TEN_CENTS] << endl;
    outfile << "5," << (*coin_map)[FIVE_CENTS] << endl;
    
    // close the file
    outfile.close();
    
    stock_list->saveStock(stockFile);
}

void VendingMachine::abort()
{
    cout << "\nGoodbye!\n" << endl;
}

string VendingMachine::giveChange(float changeLeft, map<Denomination, int>& coinMap) {
    string return_string = "";
    int denominations_in_cents[] = {1000, 500, 200, 100, 50, 20, 10, 5};

    for (std::map<Denomination, int>::size_type i = 0; i < coinMap.size(); ++i){
        int denom = denominations_in_cents[i];
        // while there is an amount left of that denom and still change to give, and denom not too big to give
        while (coinMap[static_cast<Denomination>(i)] > 0 && changeLeft > 0 && changeLeft >= denom) {
            changeLeft -= denom;
            --coinMap[static_cast<Denomination>(i)];
            // correctly format
            if (denom >= 100){
                return_string += "$" + std::to_string(denom/100) + " ";
            } else {
                return_string += std::to_string(denom) + "c ";
            }
        }
    }

    if (changeLeft > 0){
        return_string = "";
    }

    return return_string;

}

void VendingMachine::updateCoins(map<Denomination, int>* purchaseMethodCoinMap, float userPayment)
{
    if(userPayment == 5) {
        (*purchaseMethodCoinMap)[FIVE_CENTS]++;
    } else if(userPayment == 10) {
        (*purchaseMethodCoinMap)[TEN_CENTS]++;
    } else if(userPayment == 20) {
        (*purchaseMethodCoinMap)[TWENTY_CENTS]++;
    } else if(userPayment == 50) {
        (*purchaseMethodCoinMap)[FIFTY_CENTS]++;
    } else if(userPayment == 100) {
        (*purchaseMethodCoinMap)[ONE_DOLLAR]++;
    } else if(userPayment == 200) {
        (*purchaseMethodCoinMap)[TWO_DOLLARS]++;
    } else if(userPayment == 500) {
        (*purchaseMethodCoinMap)[FIVE_DOLLARS]++;
    } else if(userPayment == 1000) {
        (*purchaseMethodCoinMap)[TEN_DOLLARS]++;
    }
}