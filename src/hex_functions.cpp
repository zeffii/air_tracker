#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <vector>

using namespace std;

string helper_converter(int num){
    stringstream stream;
    stream << std::hex << num;
    return stream.str();
};

string uppercase(string str){
    int str_len = str.length();
    for(int i = 0; i < str_len; i++)
        str[i] = toupper(str[i]);
    return str;
};

vector<string> interpolate_hex(int elements, string h_start, string h_end){
    /*
    - first convert h_start amd h_end to integers
    - generate the range between these integers (given range of n elements)
    - print the hex range of these newly generated elements.

    - limitation, 
       -- expects first hex to be lower than the second, 
       -- expects both to be different
    */
    unsigned int x_1, x_2;
    stringstream ss_1, ss_2;

    ss_1 << std::hex << h_start;
    ss_2 << std::hex << h_end;
    ss_1 >> x_1;
    ss_2 >> x_2;

    float stepsize = ((float) x_2 - x_1) / (elements - 1);
    vector<string> data_replacement;

    for (int i = 0 ; i < elements; i++){
        float intermediate_value = x_1 + (stepsize * i);
        int temp_int = round(intermediate_value);
        string hex_value = helper_converter(temp_int);
        hex_value = uppercase(hex_value);
        data_replacement.push_back(hex_value);
    }

    return data_replacement;
}

