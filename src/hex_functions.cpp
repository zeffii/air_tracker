#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <vector>
#include <random>
#include <iomanip>

using namespace std;


string helper_converter(int num, int numchars){

    string retval = "";
    stringstream stream;
    stream << std::setfill('0') << std::setw(numchars) << std::hex << num;
    return stream.str();
};

string uppercase(string str){
    int str_len = str.length();
    for(int i = 0; i < str_len; i++)
        str[i] = toupper(str[i]);
    return str;
};

int hex_to_int(string hexvalue){
    unsigned int x_1;
    stringstream ss_1;
    ss_1 << std::hex << hexvalue;
    ss_1 >> x_1;
    return x_1;
};

string int_to_hex(int num, int numchars){
    string interim_hex = helper_converter(num, numchars);
    return uppercase(interim_hex);
};


vector<string> interpolate_hex(int elements, string h_start, string h_end){
    /*
    - first convert h_start amd h_end to integers
    - generate the range between these integers (given range of n elements)
    - print the hex range of these newly generated elements.
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
        int numchars = h_start.length();
        string hex_value = helper_converter(temp_int, numchars);
        hex_value = uppercase(hex_value);
        data_replacement.push_back(hex_value);
    }

    return data_replacement;
}


string pick_random_hex(int numchars){

    vector<string> hexvals {
        "A", "B", "C", "D", "E", "F",
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"
    };
    int unsigned len = hexvals.size() - 1;
    string replacement = (numchars == 1) ? "." : "..";
   
    switch (numchars){
        case 1:
            {
                replacement = hexvals[rand() % len];
            }
            break;
        case 2:
            {
                replacement = hexvals[rand() % len] + hexvals[rand() % len];
            }
            break;
        default:
            break;
    }

    return replacement;


};

string multiply_hex(string hexvalue, float amount){

    int maxintval = 0;
    string maxhexval = "F";
    string hex_result = "";

    unsigned int x_1;
    stringstream ss_1;

    ss_1 << std::hex << hexvalue;
    ss_1 >> x_1;

    int numchars = hexvalue.length();
    switch (numchars) {
        case 4:
            maxintval = 65535;
            maxhexval = "FFFF";
            break;
        case 2:
            maxintval = 255;
            maxhexval = "FF";
            break;
        case 1:
            maxintval = 16;
            maxhexval = "F";
            break;
        default:
            return hexvalue;
    }

    int temp_int = round((float)x_1 * amount);
    if (temp_int > maxintval) {
        hex_result = maxhexval;
    } else {
        hex_result = helper_converter(temp_int, numchars);
        hex_result = uppercase(hex_result);
    }
    return hex_result;

};