// Functions.h
#pragma once 
#include <string>
#include "Pattern.h"

using namespace std;

vector<int> join_two_vectors(vector<int> A, vector<int> B);
vector<int> filter_out_int_array_A_from_B(vector<int> inarray, vector<int> drop);
vector<int> add_one_to_indices_for_hex2(vector<int> inarray);
vector<int> add_num_to_indices(vector<int> inarray, int addnum);

int find_int_in_vector(int num_to_find, vector<int> inarray);
int find_int_in_array(int num_to_find, int numbers[], int arraysize);

vector<int> add_indices_for_hex2(vector<int> inarray);
vector<int> find_token_in_string(string input_string, string token);

string kb_key_to_noterepr(string kb_key, int octave);

void print_int_array(vector<int> inarray);
void pattern_descriptor_to_handler(string descriptor, Pattern& pattern);