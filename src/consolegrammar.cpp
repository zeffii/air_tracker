#include <string>
#include <vector>
#include <iostream>
// #include "SelectRange.h"
#include "Pattern.h"
#include "Hex_functions.h"
#include "ConsoleGrammar.h"

using namespace std;

ConsoleGrammar::ConsoleGrammar(Selector &selection, Pattern &mypat, string commands){
    cout << ">" << commands << endl;
    cout << "current selection state: " << selection.get_selector_state() << endl;

    if (selection.get_selector_state()){

        Selection_Range sr = {};
        mypat.get_corrected_selection_range(selection, sr);

        int char_offset = 4;
        int selection_length = (sr.last_col_idx - sr.first_col_idx) + 1;
        int selection_start = sr.first_col_idx + char_offset;
        cout << selection_start << ", " << selection_length << endl;
    }
};


