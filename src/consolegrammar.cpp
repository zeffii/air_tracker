#include <string>
#include <vector>
#include <iostream>
// #include "SelectRange.h"
#include "Pattern.h"
#include "Hex_functions.h"
#include "ConsoleGrammar.h"

using namespace std;

ConsoleGrammar::ConsoleGrammar(Selection_Range sr, Pattern &mypat, string commands){
    cout << ">" << commands << endl;
    cout << sr.first_col_idx << endl;
    cout << sr.last_col_idx << endl;
    cout << sr.first_row_idx << endl;
    cout << sr.last_row_idx << endl;    
    cout << "----\n";

};


