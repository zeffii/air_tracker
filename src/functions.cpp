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
        // cout << note << ":" << add_octave << endl;
        //cout << notes[note] << octave + add_octave << endl;
        rvalue = notes[note] + std::to_string(octave + add_octave);
    }

    return rvalue;
};
// kb-key to note f.ex:  (Z->C(octave))  E->C(octave+1)