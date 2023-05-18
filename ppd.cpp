#include <iostream>
#include <string>
#include <fstream>

#include "LinkedList.h"
#include "helper.h"
#include "VendingMachine.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::stoi;

int main(int argc, char **argv)
{
    // check for 3 arguments and valid input files
    if (argc == 3) {
        // start vending machine
        VendingMachine* vendingMachine = new VendingMachine(argv[1], argv[2]);
        vendingMachine->start();

        delete vendingMachine;

    } else {
        // not correct amount of arguments
        cout << "Error: invalid arguments passed in." << endl;
        cout << "Correct arguments are:" << endl;
	    cout << "   ./ppd <stockfile> <coinfile>" << endl;
        cout << "Where <stockfile> and <coinfile> are two valid files in the expected format." << endl;
    }

    return EXIT_SUCCESS;
}