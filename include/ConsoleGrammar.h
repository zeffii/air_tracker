#include <string>
#include <vector>
#include <iostream>
// #include "SelectRange.h"
#include "Pattern.h"
#include "Hex_functions.h"


using namespace std;

class ConsoleGrammar {

    public:
        ConsoleGrammar(Selector &selection, Pattern &mypat, string commands);

    private:
        vector<string> replacement_data;
        Selection_Range sr;
};