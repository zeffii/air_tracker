// Functions.h
#pragma once 
#include <string>
using namespace std;

vector<int> add_indices_for_hex2(vector<int> inarray);
void print_int_array(vector<int> inarray);

vector<int> find_token_in_string(string input_string, string token);
int find_int_in_array(int num_to_find, int numbers[], int arraysize);

string kb_key_to_noterepr(string kb_key, int octave);

void pattern_descriptor_to_handler(string descriptor);