#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <vector>
#include <random>

using namespace std;

string helper_converter(int num);
string uppercase(string str);

int hex_to_int(string hexvalue);
string int_to_hex(int num, int numchars);

vector<string> interpolate_hex(int elements, string h_start, string h_end);
string pick_random_hex(int numchars);
string multiply_hex(string hexvalue, float amount);