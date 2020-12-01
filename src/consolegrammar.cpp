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
    "amp",  //   amp value |
    "rev",  //   rev       |  rev row
    "spd",  //   spd dbl   |  spd 2.0  | spd 0.5
    "linf", //   linf      |  linf a, b  (a=start amp, b=end amp)  -> linf 1.0 0.2
            //   default => linf => linf 1.0 0.0
    "rep",  //   rep
            //   default => rep ^  (repeat selection till end of pattern)
            //   rep 12  => repeat 12 times (or until end of pattern)
    "avg",  //   average all values in selection, set all values to the avg
    "hum"   //   humanize  ( hum 20 )
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
        if ((elements.size() == 2) && is_string_numeric(elements[1])){

            double amt = ::atof(elements[1].c_str());
            cout << "Attempting to amplify. by " << amt << endl;
            mypat.amp_selection(selection, amt);
            return;
        }
    }

    cout << "command not implemented yet --->" << commands << endl;
    
};


