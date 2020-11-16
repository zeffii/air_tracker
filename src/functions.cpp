// functions.cpp
#include <iostream>
#include <string>
#include "Functions.h"

using namespace std;



int find_int_in_array(int num_to_find, int numbers[], int arraysize){
    for(int i = 0; i < arraysize; i++){
         if(numbers[i] == num_to_find){ return 1; }
    }
    return 0;
}

string kb_key_to_noterepr(string kb_key, int octave){
    // before it enters this function, kb string is checked.
    // but we'll test again :)
    string rvalue = "^^^";
    string allowed = "ZSXDCVGBHNJMQ2W3ER5T6Y7UI9O0P";
    string notes[] = {
        "C-", "C#", "D-", "D#", "E-", "F-", "F#", 
        "G-", "G#", "A-", "A#", "B"};

    int findex = allowed.find(kb_key);
    if (findex >= 0){
        int note = findex % 12;
        int add_octave = findex / 12;
        rvalue = notes[note] + std::to_string(octave + add_octave);
    }

    return rvalue;
};

void pattern_descriptor_to_handler(string descriptor){
    /*
    this function will take the descriptor string, and populate various arrays with
    information useful for helping the user add data to the pattern.

                                    28           41
           3  6   10 13  17 20  24 27  31 34 37 40  44 47
    TTTSNNNSHHSNNNSHHSNNNSHHSNNNSHHSSHHSHHSHHSHHSSHHSHHSHH
        0   1  2   3  4   5  6   7   8  9  10 11  12 13 14  concept index
        3   2  3   2  3   2  3   2   2  2  2  2   2  2  2   length
        0   4  7   11 14  18 21  24  29 32 35 38  42 45 48  index start

    */


};