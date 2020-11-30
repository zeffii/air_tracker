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

vector<string> split_string(string str, string delim){

    vector<string> v;
    size_t pos = 0;
    string token;

    try {

        while ((pos = str.find(delim)) != string::npos) {
            token = str.substr(0, pos);
            if (token == " ")
                continue;        
            v.push_back(token);
            str.erase(0, pos + delim.length());
        }
    }
    catch (...) {
        v.clear();
        v.push_back("FAIL");
    }


    return v;
};

ConsoleGrammar::ConsoleGrammar(Selector &selection, Pattern &mypat, string commands){
    cout << ">" << commands << endl;
    cout << "current selection state: " << selection.get_selector_state() << endl;

    if (!(selection.get_selector_state())){
        // do something else.
        return;
    }

    string operand = "";


    vector<string> elements = split_string(commands, " ");
    if (elements[0] == "FAIL"){
        cout << "parsing failed, see the manual!\n";
        return;
    }

    if (!find_str_in_vector(operands, elements[0])){
        cout << elements[0] << "  is not a valid operand, see the manual\n";
        return;
    }

    if (elements[0] == "amp"){
        if (elements.size() == 2){
            double amt = ::atof(elements[1].c_str());
            cout << "Attempting to amplify. by " << amt << endl;
        }
    }

    Selection_Range sr = {};
    mypat.get_corrected_selection_range(selection, sr);

    int char_offset = 4;
    int selection_length = (sr.last_col_idx - sr.first_col_idx) + 1;
    int selection_start = sr.first_col_idx + char_offset;
    cout << selection_start << ", " << selection_length << endl;
    
};


