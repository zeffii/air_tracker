// functions.cpp
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include "Functions.h"
#include "Pattern.h"
#include "Augmentations.h"

using namespace std;

/*
weighted smoothing

s = (Yj-2 + 2Yj-1 + 3Yj + 2Yj+1 + Yj+2) / 9

*/

void generate_noise(float *noise_samples, int numsamples, unsigned int seed){
    /*
    usage:

    unsigned int seed = 20;
    int numsamples = 12;
    float noise_samples[numsamples];
    generate_noise(noise_samples, numsamples, seed);    

    */

    srand(seed);
    for (int i = 0; i < numsamples; ++i) {
        float random = ((float) rand()) / (float) RAND_MAX;
        float x = -1.0f + random * 2.0f;
        noise_samples[i] = x;
    }
};

void shift_float_array(float *noise_samples, int numsamples, int numspaces){
    /*
    not fully error checked, but you should only pass this numspaces == ( -numsamples / +numsamples )
    and of that pair i'm only testing against +numsamples.
    */
    if ((numspaces == 0) || (numspaces == numsamples))
        return;
    if (numspaces > numsamples)
        numspaces %= numsamples;

    float remapped_samples[numsamples];

    if (numspaces > 0){

        for (int i = 0; i < numsamples; ++i){
            int offset_i = ((i - numspaces) >= 0) ? (i - numspaces) : numsamples - numspaces + i;
            remapped_samples[i] = noise_samples[offset_i];
        }
    
    } else {

        for (int i = 0; i < numsamples; ++i)
            remapped_samples[i] = noise_samples[((i + numspaces) % numsamples)];
    }

    for (int i = 0; i < numsamples; ++i)
        noise_samples[i] = remapped_samples[i];
};

float float_lerp(float a, float b, float mix){
    float_constrain(mix, 0.0, 1.0);
    if (mix == 0.0) return a;
    if (mix == 1.0) return b;

    float result = a + mix * (b - a);
    return result;
};

void mix_signal_into_nfsamples(std::vector<RT_Point> &nfsamples, float *noise_samples, float mix){
    int numsamples = nfsamples.size();
    for (int i = 0; i < numsamples; ++i) {
        nfsamples[i].y = float_lerp(nfsamples[i].y, noise_samples[i], mix);
    }
};

void unweighted_sliding_average(std::vector<RT_Point> &nfsamples, int width, float mix){
    cout << mix << endl;
    
    std::vector<RT_Point> smoothed;
    int numfsamples = nfsamples.size();
    if (width == 3){
        for (int i = 0; i < numfsamples; i++) {

            int idx = ((i-1) < 0) ? numfsamples-1 : i-1;
            float A = nfsamples[idx].y;
            float B = nfsamples[i].y;
            float C = nfsamples[(i+1) % numfsamples].y;
            float fy = (A + B + C) / 3.0;

            RT_Point p = {float(i), fy};
            smoothed.push_back(p);
        }
        for (int i = 0; i < numfsamples; i++) {
            float mixed = float_lerp(nfsamples[i].y, smoothed[i].y, mix);
            nfsamples[i].y = mixed;
        }
    }
};


void find_midpoint(int x1, int y1, int x2, int y2, int& rx, int& ry){
    rx = (x1 + x2) / 2;
    ry = (y1 + y2) / 2;
};

void find_interpolation_between(int x1, int x2, float ratio, int& estimated){
    float flip_ratio = 1.0 - ratio;
    estimated = int((flip_ratio * x1) + (ratio * x2));
};


void qubic_interpolation_ints4(int p0, int p1, int p2, int p3, float mu, int& est){
    /*
    Paul Breeuwsma / http://paulbourke.net/miscellaneous/interpolation/ / cubic interpolation
    mu:  is the interval between p1 and p2, it's a float. so exactly in the middle p1p2, then mu = 0.5
    */
    float mu2 = mu * mu;
    float a0 = -0.5*p0 + 1.5*p1 - 1.5*p2 + 0.5*p3;
    float a1 = p0 - 2.5*p1 + 2*p2 - 0.5*p3;
    float a2 = -0.5*p0 + 0.5*p2;
    float a3 = p1;
    est = a0*mu*mu2 + a1*mu2 + a2*mu + a3;
};

/*
vector<float> quadratic_interval(float start, float end, float thru){
    float P0x = 0.0;
    float P0y = startval;
    float P2x = 1.0;
    float P2y = endval;
    vector<RT_Point> outputs;

    for (int i=0; i < ntimes; i++){
        float t = (1 / ntimes) * i;
        float P1x = midval;
        float P1y = (startval - endval) * midval;
        float px = (1-t)**2 *P0x + 2*(1-t)*t*P1x + t*t*P2x;
        float py = (1-t)**2 *P0y + 2*(1-t)*t*P1y + t*t*P2y;
        RT_Point p = {px, py};
        outputs.push_back(p);
    }
};
*/

void float_constrain(float& x, float x_min, float x_max){
    if (x <= x_min) x = x_min;
    else if (x >= x_max) x = x_max;
};

void float_fold_constrain(float& x, float x_min, float x_max){
    if (x < x_min) {
        float diff = abs(x - x_min);
        x = x_min + diff;
    }
    else if (x > x_max) {
        float diff = abs(x - x_max);
        x = x_max -          diff;
    }
    float_constrain(x, x_min, x_max);
};

float map(float x, float in_min, float in_max, float out_min, float out_max){
    // linear rescaling
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
};

bool is_string_numeric(string str){
    /*
    numeric strings may contain numbers, and at most one decimal point. 
    */
    int point = 0;
    for (int unsigned i = 0; i < str.length(); i++){
        if (isdigit(str[i])) { continue; }

        else if ((str[i] == '.') && (point == 0)) {
            point += 1;
        } 
        else { return false; }
    }
    return true;
};    

int average_int_vector(vector<int> invec){
    int _val = 0;
    for (auto i: invec)
        _val += i;
    return (int) _val / invec.size();
};


vector<float> range(float start, float end, int elements){
    vector<float> v;
    float stepsize = ((float) end - start) / (elements - 1);
    for (int i = 0 ; i < elements; i++){
        float new_value = start + (i * stepsize);
        // cout << i << ": " << new_value << endl;
        v.push_back(new_value);
    };
    return v;
};

vector<int> range(int start, int end){
    vector<int> v;
    for (int i = start ; i < end; i++){ v.push_back(i); };
    return v;
};



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

vector<int> add_num_to_indices(vector<int> inarray, int addnum){
    vector<int> new_indices;
    for (int unsigned i=0; i < inarray.size(); i++){
        new_indices.push_back(inarray[i] + addnum);
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

void print_string_vector(vector<string> cp){
    for (auto s: cp){
        cout << s << endl;
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

bool find_str_in_vector(vector<string> inarray, string token){
    for (auto s: inarray)
        if (s == token)
            return true;
    return false;
};

vector<string> split_string(string str, string delim){

    vector<string> v;

    auto start = 0U;
    auto end = str.find(delim);
    while (end != std::string::npos) {
        v.push_back(str.substr(start, end - start));
        start = end + delim.length();
        end = str.find(delim, start);
    }
    v.push_back(str.substr(start, end));

    return v;
};


string get_empty_repr_of_row(string row){
    int numchars = row.length();
    string empty_str (numchars, ' ');

    for (int i = 0; i < numchars; i++){
        if (!(row[i] == ' ')){
            empty_str[i] = '.';
        }
    } 
    return empty_str;
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
    pattern.set_octave_indices(note_indices);

    vector<int> fw_double_spaces = find_token_in_string(descriptor, "  ");
    vector<int> bw_double_spaces = add_one_to_indices_for_hex2(fw_double_spaces);
    vector<int> joined_vecs = join_two_vectors(fw_double_spaces, bw_double_spaces);
    vector<int> all_spaces = find_token_in_string(descriptor, " ");
    vector<int> nnnumbers = filter_out_int_array_A_from_B(all_spaces, joined_vecs);

    pattern.set_single_hop_indices(nnnumbers);
    pattern.set_double_hop_fw_indices(fw_double_spaces);
    pattern.set_double_hop_bw_indices(bw_double_spaces);

};