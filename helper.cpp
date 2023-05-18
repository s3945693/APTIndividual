#include "helper.h"
#include <cstdlib>
#include <ostream>
using std::string;
using std::vector;

Helper::Helper(){}

// from Assigment 1 starter code
void Helper::printInvalidInput()
{
    // Print out Invalid input in the colour red
    std::cout << "Invalid input." << "\n" << std::endl;
}

// from Assigment 1 starter code
bool Helper::isNumber(string s)
{
    string::const_iterator it = s.begin();
    char dot = '.';
    int nb_dots = 0;
    while (it != s.end()) 
    {
        if (*it == dot)
        {
            nb_dots++;
            if (nb_dots>1)
            {
                break;
            }
        }   
        else if (!isdigit(*it))
        {
            break;
        } 

        ++it;
    }
    return !s.empty() && s[0] != dot && it == s.end();
}

// from Assigment 1 starter code
void Helper::splitString(string s, vector<string>& tokens, string delimeter)
{
    tokens.clear();
    char* _s = new char[s.length()+1];
    strcpy(_s, s.c_str());

    char * pch;
    pch = strtok (_s, delimeter.c_str());
    while (pch != NULL)
    {
        tokens.push_back(pch);
        pch = strtok (NULL, delimeter.c_str());
    }
    delete[] _s;
}

// from Assigment 1 starter code
string Helper::readInput()
{
    string input;
    std::getline(std::cin, input);
    return input;
}