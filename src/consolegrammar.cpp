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
    "amp",  // [x]  amp <float>
            //      : amp all the same
            // [x]  amp <float 1> <float 2>
            //      : linear amp transition  starting from float 1 going to float 2

    "rev",  // [ ]  rev         => rev row

    "spd",  // [ ]  spd dbl     => spd 2.0  | spd 0.5

    "rep",  // [x]  rep ^       
            //      : repeat selection till end of pattern 
            // [x]  rep <int>   
            //      : repeat n times (or until end of pattern, including partial copies)

    "avg",  // [x]  avg |       => average all values in selection, set all values to the avg

    "hum"   // [ ]  hum <int>   => humanize 20%
};


ConsoleGrammar::ConsoleGrammar(Selector &selection, Pattern &mypat, string commands){
    //cout << ">" << commands << endl;
    //cout << "current selection state: " << selection.get_selector_state() << endl;

    if (!(selection.get_selector_state())){
        cout << "selection must be active or completed\n";
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

    string operand = elements[0];

    if (operand == "amp"){
        if ((elements.size() == 2) && is_string_numeric(elements[1])) {
            mypat.amp_selection(selection, ::atof(elements[1].c_str()));
            return;
        }
        else if (elements.size() == 3) {
            if (is_string_numeric(elements[1]) && is_string_numeric(elements[2])){
                float start_amp = ::atof(elements[1].c_str());
                float end_amp = ::atof(elements[2].c_str());
                mypat.amp_selection(selection, start_amp, end_amp);
                return;
            }
            cout << "expected:  amp <start float> <end float>\n";
        }
    }
    else if (operand == "avg") { mypat.average_selection(selection); return;}
    else if (operand == "rep") { mypat.repeat_selection(selection, elements[1]); return; }
    else if (operand == "rev") { mypat.reverse_selection(selection); return;}
    cout << "command not implemented yet --->" << commands << endl;
    
};


