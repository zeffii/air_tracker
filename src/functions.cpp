// functions.cpp
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include "Functions.h"
#include "Pattern.h"

using namespace std;

vector<int> join_two_vectors(vector<int> A, vector<int> B){
    vector<int> new_indices;
    for (int unsigned i=0; i < A.size(); i++){
        new_indices.push_back(A[i]);
    }
    for (int unsigned i=0; i < B.size(); i++){
        new_indices.push_back(B[i]);
    }
    return new_indices;
};

vector<int> filter_out_int_array_A_from_B(vector<int> inarray, vector<int> drop){
    vector<int> new_indices;
    
    // convert vector to array
    /*
    int drop_array[drop.size()];
    std::copy(drop.begin(), drop.end(), drop_array);
    */
    for (int unsigned i=0; i < inarray.size(); i++){
        if (!find_int_in_vector(inarray[i], drop)){
            new_indices.push_back(inarray[i]);
        }
    }    
    return new_indices;
};

vector<int> add_one_to_indices_for_hex2(vector<int> inarray){
    vector<int> new_indices;
    for (int unsigned i=0; i < inarray.size(); i++){
        new_indices.push_back(inarray[i]+1);
    }
    return new_indices;
};

vector<int> add_indices_for_hex2(vector<int> inarray){
    vector<int> broad_indices;
    for (int unsigned i=0; i < inarray.size(); i++){
        broad_indices.push_back(inarray[i]);
        broad_indices.push_back(inarray[i]+1);
    }
    return broad_indices;
};

void print_int_array(vector<int> inarray){
    for (int unsigned i=0; i < inarray.size(); i++){
        cout << inarray[i];
        if (i != inarray.size()-1){
            cout << ", ";
        }
        else{
            cout << endl;
        }
    }
};


vector<int> find_token_in_string(string input_string, string token){
    vector<int> indices;
    int token_size = token.length();

    for(int unsigned i =0; i < input_string.size(); i++){
        string s1 = input_string.substr(i, token_size);
        int token_equals = s1.compare(token);
        if (token_equals == 0){
            indices.push_back(i);
        }
    }
    return indices;
}

int find_int_in_array(int num_to_find, int numbers[], int arraysize){
    for(int i = 0; i < arraysize; i++){
         if (numbers[i] == num_to_find){ return 1; }
    }
    return 0;
}

int find_int_in_vector(int num_to_find, vector<int> inarray){
    vector<int>::iterator it = std::find(inarray.begin(), inarray.end(), num_to_find);
    return (it != inarray.end()) ? 1 : 0;
};


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

void pattern_descriptor_to_handler(string descriptor, Pattern& pattern){
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

    descriptor = descriptor.substr(4, -1);
    replace( descriptor.begin(), descriptor.end(), 'S', ' ');

    string last_char = "";
    // note input, only ever allow the first index of the note param
    vector<int> note_indices = find_token_in_string(descriptor, "NNN");

    // hex input, both positions, we call a second function to wided the accepted input index
    vector<int> hex_indices = find_token_in_string(descriptor, "HH");
    hex_indices = add_indices_for_hex2(hex_indices);

    pattern.set_note_indices(note_indices);
    pattern.set_hex_indices(hex_indices);

    vector<int> fw_double_spaces = find_token_in_string(descriptor, "  ");
    vector<int> bw_double_spaces = add_one_to_indices_for_hex2(fw_double_spaces);
    vector<int> joined_vecs = join_two_vectors(fw_double_spaces, bw_double_spaces);
    vector<int> all_spaces = find_token_in_string(descriptor, " ");
    vector<int> nnnumbers = filter_out_int_array_A_from_B(all_spaces, joined_vecs);

    pattern.set_single_hop_indices(nnnumbers);
    pattern.set_double_hop_fw_indices(fw_double_spaces);
    pattern.set_double_hop_bw_indices(bw_double_spaces);

};