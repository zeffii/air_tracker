// Functions.h
#pragma once 
#include <string>
#include <cstdlib>
#include "Pattern.h"
#include "Augmentations.h"
using namespace std;

// smoothing utils
float get_denominator_for_multipliers(int width);
float sum_of_floats(float* inarray, int arrsize);

// signal
void mix_signal_into_nfsamples(std::vector<RT_Point> &nfsamples, float *noise_samples, float mix);
void dynamic_smoothing(std::vector<RT_Point> &nfsamples, std::vector<RT_Point> &smoothed, int width); 
void unweighted_sliding_average(std::vector<RT_Point> &nfsamples, int width, float mix);
void generate_noise(float *noise_samples, int numsamples, unsigned int seed);
void shift_float_array(float *noise_samples, int numsamples, int numspaces);

// geometric
void find_midpoint(int x1, int y1, int x2, int y2, int& rx, int& ry);
void find_interpolation_between(int x1, int x2, float ratio, int& estimated);
void qubic_interpolation_ints4(int x0, int x1, int x2, int x3, float mu, int& est);
float float_lerp(float a, float b, float mix);

// numeric
void float_constrain(float& x, float x_min, float x_max);
void float_fold_constrain(float& x, float x_min, float x_max);
float map(float x, float in_min, float in_max, float out_min, float out_max);

bool is_string_numeric(string str);
int average_int_vector(vector<int> invec);

vector<float> range(float start, float end, int elements);
vector<int> range(int start, int end);

vector<int> join_two_vectors(vector<int> A, vector<int> B);
vector<int> filter_out_int_array_A_from_B(vector<int> inarray, vector<int> drop);
vector<int> add_one_to_indices_for_hex2(vector<int> inarray);
vector<int> add_num_to_indices(vector<int> inarray, int addnum);

int find_int_in_vector(int num_to_find, vector<int> inarray);
int find_int_in_array(int num_to_find, int numbers[], int arraysize);
bool find_str_in_vector(vector<string> inarray, string token);

vector<int> add_indices_for_hex2(vector<int> inarray);
vector<int> find_token_in_string(string input_string, string token);
vector<string> split_string(string str, string delim);

string get_empty_repr_of_row(string row);
string kb_key_to_noterepr(string kb_key, int octave);

void print_string_vector(vector<string> cp);
void print_int_array(vector<int> inarray);
void pattern_descriptor_to_handler(string descriptor, Pattern& pattern);

