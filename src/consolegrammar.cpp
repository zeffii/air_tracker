#include <string>
#include <vector>
#include <iostream>
// #include "SelectRange.h"
#include "Functions.h"
#include "Pattern.h"
#include "Hex_functions.h"
#include "ConsoleGrammar.h"

using namespace std;

vector<string> operands = {
    "amp", "rev", "spd", "linf", "rep"
};



ConsoleGrammar::ConsoleGrammar(Selector &selection, Pattern &mypat, string commands){
    //cout << ">" << commands << endl;
    //cout << "current selection state: " << selection.get_selector_state() << endl;

    if (!(selection.get_selector_state())){
        cout << "end earlier state\n";
        return;
    }

    vector<string> elements = split_string(commands, " ");
    if (elements.size() == 1){
        cout << "parsing |" << elements[0] << "| failed, see the manual!\n";
        return;
    }

    if (!find_str_in_vector(operands, elements[0])){
        cout << elements[0] << "  is not a valid operand, see the manual\n";
        return;
    }

    if (elements[0] == "amp"){
        cout << elements.size() << endl;
        print_string_vector(elements);
        if (elements.size() == 2){
            double amt = ::atof(elements[1].c_str());
            cout << "Attempting to amplify. by " << amt << endl;
            mypat.amp_selection(selection, amt);
        }
    }


    
};


