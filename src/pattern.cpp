// pattern.cpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include "Selector.h"
#include "Pattern.h"
#include "Window.h"
#include "Functions.h"
#include "Hex_functions.h"


using namespace std;


void readPattern(const char* filename, std::vector<string> &lines, string &pattern_descriptor_str){
    lines.clear();
    ifstream file (filename);

    // read first line of this file, the descriptor, will look something like
    // TTTSNNNSHHSNNNSHHSNNNSHHSNNNSHHSSHHSHHSHHSHHSSHHSHHSHH
    getline(file, pattern_descriptor_str);
    
    // read remaining pattern data
    string s;
    while (getline(file, s))
        lines.push_back(s);

    file.close();
}

Pattern::Pattern(SDL_Renderer *renderer, const char* pattern_path){
    readPattern(pattern_path, pattern_data, pattern_descriptor_str);
    _nchars_inrow = pattern_descriptor_str.length();
    _nrows = pattern_data.size();

    renderer_placeholder = renderer;
    texture_pattern(renderer);
    pattern_descriptor_to_handler(pattern_descriptor_str, *this);
};


void Pattern::texture_pattern(SDL_Renderer *renderer){
    TTF_Font *font = TTF_OpenFont("res/consola.ttf", 11);
    if (!font) { cerr << "failed to load font\n"; }

    SDL_Color colwhite = {255, 255, 255, 255};
    _text_rects.clear();
    
    // this may not do a SDL_DestroyTexture
    if (_text_textures.empty()){
        cout << "air tracker: started!\n"; //"first init of _text_textures!
    }
    else {
        //cout << "re-using _text_textures to populate more!\b";
        //for (int unsigned i = 0; i < _text_textures.size(); i++){
        //    SDL_DestroyTexture(_text_textures[i]);
        //}
        _text_textures.clear();
    }


    for (int unsigned i = 0; i < pattern_data.size(); i++){
    
        auto text_surface = TTF_RenderText_Blended(font, pattern_data[i].c_str(), colwhite);
        if (!text_surface) { cerr << "failed to create text surface \n"; }

        auto text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        if (!text_texture) { cerr << "failed to create text texture \n"; }

        SDL_Rect trect = {0, 0, 0, 0};
        
        SDL_FreeSurface(text_surface);
        SDL_QueryTexture(text_texture, nullptr, nullptr, &trect.w, &trect.h);
        
        _text_rects.push_back(trect);
        _text_textures.push_back(text_texture);
    }
    TTF_CloseFont( font );
};

void Pattern::display(int x, int y, SDL_Renderer *renderer) const { 

    int offset = shift_vertical_times * 16;
    int num_rows = static_cast<int>(pattern_data.size());
    
    for (int i = 0; i < num_rows; i++){

        int ri = i;

        if (shift_vertical_times != 0){
            ri = (i + offset) % num_rows;
            if (ri < 0){
                ri = num_rows + ri;
            }
        }

        _text_rects[i].x = pattern_x;
        _text_rects[i].y = pattern_y + ri * _line_height;
        SDL_Color lc = colors[hcolor[i%8]];

        // SDL_SetTextureColorMod( _text_textures[i], 155, 233, 222 );
        SDL_SetTextureColorMod( _text_textures[i], lc.r, lc.g, lc.b );
        SDL_RenderCopy(renderer, _text_textures[i], nullptr, &_text_rects[i]);
        SDL_Delay(1);
    }
    // cout << endl;
};

void Pattern::scroll_vertical(int numrows){
    // pattern_y += (numrows * _line_height);
    shift_vertical_times += copysign(1, numrows);
    cout << "scroll pattern " << numrows << " rows | shift by " << shift_vertical_times << "\n";
};


void Pattern::print_row(int row_number){ cout << pattern_data[row_number] << endl; };

int Pattern::get_octave(){ return octave; };
void Pattern::change_octave(int direction){ 

    octave += direction;
    if (octave > 7){
        octave = 7; 
    }
    else if (octave < 0) {
        octave = 0; 
    }
    cout << octave << endl;
};

void Pattern::adjust_visual_cursor_for_scroll(int &row_number){
    /*
    the row_number visually is different from the row number of the selection.
    */

    if (shift_vertical_times != 0){

        int offset = shift_vertical_times * 16;
        int ri = (row_number + offset) % _nrows;
        
        if (ri < 0){ 
            ri = _nrows + ri;  
        }
        row_number = ri;
    }

};

void Pattern::set_char_at(int row_number, int col_number, string character){

    adjust_visual_cursor_for_scroll(row_number);

    /*
                                        28           41
               3  6   10 13  17 20  24 27  31 34 37 40  44 47
        TTTSNNNSHHSNNNSHHSNNNSHHSNNNSHHSSHHSHHSHHSHHSSHHSHHSHH
            0   1  2   3  4   5  6   7   8  9  10 11  12 13 14  concept index
            3   2  3   2  3   2  3   2   2  2  2  2   2  2  2   length
            0   4  7   11 14  18 21  24  29 32 35 38  42 45 48  index start
    */    

    cout << row_number << ", " << col_number << " : " << character << endl;

    // deal with hex data on hex params
    if (find_int_in_vector(col_number, _hex_indices)){

        string allowed = "0123456789ABCDEF.";
        int findex = allowed.find(character);

        if (findex >= 0){
            pattern_data[row_number].replace(col_number + 4, 1, character);
            texture_pattern(renderer_placeholder);
        }
        else{
            cout << "yeah dufus, no.. \n";
        }
    }

    /*

                +1                   +2
    |  C#  D#      F#  G#  A#   |  C#  D#
    | |_2_|_3_| | |_5_|_6_|_7_| | |_9_|_0_| |
    |_Q_|_W_|_E_|_R_|_T_|_Y_|_U_|_I_|_O_|_P_|
    | C   D   E   F   G   A   B | C   D   E 

                +0               
    |  C#  D#      F#  G#  A#   |
    | |_S_|_D_| | |_G_|_H_|_J_| |
    |_Z_|_X_|_C_|_V_|_B_|_N_|_M_|
    | C   D   E   F   G   A   B |

    deal with note data on note params
    */

    else if (find_int_in_vector(col_number, _note_indices)){

        string allowed = "ZSXDCVGBHNJMQ2W3ER5T6Y7UI9O0P";
        int findex = allowed.find(character);

        if (findex >= 0){
            cout << "trying to change a note\n";
            string newval = kb_key_to_noterepr(character, octave);
            pattern_data[row_number].replace(col_number + 4, 3, newval);
            texture_pattern(renderer_placeholder);
        }
        else {
            if (character == "1"){
                 pattern_data[row_number].replace(col_number + 4, 3, "^^^");
                 texture_pattern(renderer_placeholder);
            } else if (character == "`"){
                 pattern_data[row_number].replace(col_number + 4, 3, "===");
                 texture_pattern(renderer_placeholder);
            } else if (character == "."){
                 pattern_data[row_number].replace(col_number + 4, 3, "...");
                 texture_pattern(renderer_placeholder);
            }

            else {

                cout << "this is not a valid key for a note column, see manual\n";
            }
        }
    }
    // else if note in _note_indices + 1  , then hash toggle sharp on off

    else if (find_int_in_vector(col_number, _octave_indices)){
        // else if note in _note_indices + 2  , then all numeric between 0 and 9 are accepted
        string allowed = "0123456789";
        int findex = allowed.find(character);
        if (findex >= 0){
            pattern_data[row_number].replace(col_number + 4, 1, character);
            texture_pattern(renderer_placeholder);            
        }

    }
};

void print_string_vector(vector<string> yourvec){
    for (int unsigned i = 0; i < yourvec.size(); i++){
        cout << yourvec[i] << "," << endl;
    }
};

bool does_selection_contain_gutter(string input_hex){
    // selection always contains equal data in each row, we only test the first row
    int findex = input_hex.find(" ");
    return (findex >= 0) ? true : false;
};

bool does_selection_contain_dots(string input_hex1, string input_hex2){
    // selection always contains equal data in each row, we only test the first row
    int findex = input_hex1.find(".");
    int findex2 = input_hex2.find(".");
    return ((findex >= 0) or (findex2 >= 0)) ? true : false;
};

void Pattern::interpolate_single(Selection_Params s){
    vector<string> data_replacement = interpolate_hex(s.numrows, s.first_hex, s.last_hex);
    
    if (int(data_replacement.size()) == s.numrows) { 

        int m = 0;
        for (int i = s.first_row_idx; i < (s.first_row_idx + s.numrows); i++){
            pattern_data[i].replace(s.selection_start, s.selection_length, data_replacement[m]);
            m += 1;
        }
        texture_pattern(renderer_placeholder);
    }
    else {
        cout << "not equal!\n";
    }

}


void Pattern::perform_selection_interpolation(vector<int> selection_range, string mode){

    int char_offset = 4;

    int first_col_idx = selection_range[0];
    int last_col_idx = selection_range[1];
    int first_row_idx = selection_range[2];
    int last_row_idx = selection_range[3];

    adjust_visual_cursor_for_scroll(first_row_idx);
    adjust_visual_cursor_for_scroll(last_row_idx);

    int selection_length = (last_col_idx - first_col_idx) + 1;
    int selection_start = first_col_idx + char_offset;
    int numrows = (last_row_idx - first_row_idx) + 1;  // num rows in selection

    if (first_row_idx == last_row_idx){
        cout << "end early, not possible to interpolate a single value\n";
        return;
    }


    string first_hex = pattern_data[first_row_idx].substr(selection_start, selection_length);
    string last_hex = pattern_data[last_row_idx].substr(selection_start, selection_length);

    if (does_selection_contain_gutter(first_hex)){
        cout << "selection contains a gutter, currently only single rows are supported\n";
        return;
    }
    if (does_selection_contain_dots(first_hex, last_hex)){
        cout << "one of the selection extents contains a dot (.), currently not supported\n";
        return;
    }
    if (first_hex.length() == 3){
        cout << "note column not yet supported\n";
        return;
    }

    if (mode == "multi"){
        cout << "performing multi value linear interpolation\n";
        
        vector<Sparse_Selection> sparse_selection_vector;

        for (int i = first_row_idx; i <= last_row_idx; i++){
            string row_value = pattern_data[i].substr(selection_start, selection_length);
            int row_contains_dot = row_value.find(".");
            if (row_contains_dot < 0){
                sparse_selection_vector.push_back({i, row_value});
            }
        }

        if (sparse_selection_vector.size() >= 3){
            cout << "2 or more transitions!\n";

            for (int unsigned i = 0; i < sparse_selection_vector.size()-1; i++){
                Sparse_Selection v = sparse_selection_vector[i];
                Sparse_Selection v2 = sparse_selection_vector[i+1];

                if ((v2.start_idx - v.start_idx) == 1){
                    continue;
                }
                interpolate_single({
                    v.hex_value,                        // first hex
                    v2.hex_value,                       // second hex
                    ((v2.start_idx - v.start_idx) + 1), // numrows
                    v.start_idx,                        // first row idx
                    selection_start,                    // column selection start
                    selection_length}                   // column selection length
                );
            }
        }

    }
    else if (mode == "tween"){

        Selection_Params sel;
        sel.first_hex = first_hex;
        sel.last_hex = last_hex;
        sel.numrows = numrows;
        sel.first_row_idx = first_row_idx;
        sel.selection_start = selection_start;
        sel.selection_length = selection_length;
        interpolate_single(sel);

    }
    
};

void Pattern::randomize_selection(vector<int> selection_range, int factor){

    int char_offset = 4;

    int first_col_idx = selection_range[0];
    int last_col_idx = selection_range[1];
    int first_row_idx = selection_range[2];
    int last_row_idx = selection_range[3];

    adjust_visual_cursor_for_scroll(first_row_idx);
    adjust_visual_cursor_for_scroll(last_row_idx);

    int selection_length = (last_col_idx - first_col_idx) + 1;
    int selection_start = first_col_idx + char_offset;
    // int numrows = (last_row_idx - first_row_idx) + 1;  // num rows in selection

    int changes = 0;
    for (int i = first_row_idx; i <= last_row_idx; i++){

        string row_value = pattern_data[i].substr(selection_start, selection_length);
        int row_contains_dot = row_value.find(".");
        if (row_contains_dot < 0){

            cout << row_value << endl;
            int numchars = row_value.length();

            string replacement = pick_random_hex(numchars);

            pattern_data[i].replace(selection_start, selection_length, replacement);
            changes += 1;
        }
    }

    if (changes > 0){
        cout << "randomize " << changes << " values\n";
        texture_pattern(renderer_placeholder);
    }

};


int Pattern::get_nchars_in_row(){ return _nchars_inrow; };
int Pattern::get_nrows_in_column(){ return _nrows; };


void Pattern::set_note_indices(std::vector<int> note_indices){
    _note_indices = note_indices; };

void Pattern::set_octave_indices(std::vector<int> note_indices){
    _octave_indices = add_num_to_indices(note_indices, 2); };

void Pattern::set_hex_indices(std::vector<int> hex_indices){
    _hex_indices = hex_indices; };

void Pattern::set_single_hop_indices(std::vector<int> single_hop){
    _carret_single_hop = single_hop; };

void Pattern::set_double_hop_fw_indices(std::vector<int> double_hop_fw){
    _carret_double_hop_fw = double_hop_fw; };

void Pattern::set_double_hop_bw_indices(std::vector<int> double_hop_bw){
    _carret_double_hop_bw = double_hop_bw; };


void Pattern::carrot_hop_forward(int &c_index){
    if (find_int_in_vector(c_index, _carret_single_hop)) { c_index += 1; }
    else if (find_int_in_vector(c_index, _carret_double_hop_fw)) { c_index += 2; }
};

void Pattern::carrot_hop_backward(int &c_index){
    if (find_int_in_vector(c_index, _carret_single_hop)) { c_index -= 1; }
    else if (find_int_in_vector(c_index, _carret_double_hop_bw)) { c_index -= 2; }
};