// pattern.cpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Pattern.h"
#include "Window.h"
#include "Functions.h"

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
    renderer_placeholder = renderer;
    texture_pattern(renderer);
    cout << pattern_descriptor_str << endl;
    pattern_descriptor_to_handler(pattern_descriptor_str, *this);

    cout << "note_indices --> : ";
    print_int_array(_note_indices);
    cout << "hex_indices --> : ";
    print_int_array(_hex_indices);

};

void Pattern::texture_pattern(SDL_Renderer *renderer){
    TTF_Font *font = TTF_OpenFont("res/consola.ttf", 11);
    if (!font) { cerr << "failed to load font\n"; }

    SDL_Color colwhite = {255, 255, 255, 255};
    _text_rects.clear();
    
    // this may not do a SDL_DestroyTexture
    if (_text_textures.empty()){
        cout << "first init of _text_textures!\n";
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

    int hcolor[8] = {2, 0, 0, 0, 1, 0, 0, 0};
    SDL_Color colors[3] = {
        {122, 122, 122, 255},
        {182, 202, 212, 255},
        {222, 222, 222, 255}
    };

    for (int i = 0; i < 16; i++){

        _text_rects[i].x = x;
        _text_rects[i].y = y + i * _line_height;
        SDL_Color lc = colors[hcolor[i%8]];

        // SDL_SetTextureColorMod( _text_textures[i], 155, 233, 222 );
        SDL_SetTextureColorMod( _text_textures[i], lc.r, lc.g, lc.b );
        SDL_RenderCopy(renderer, _text_textures[i], nullptr, &_text_rects[i]);
    }
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


void Pattern::set_char_at(int row_number, int col_number, string character){

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

        string allowed = "0123456789ABCDEF";
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
            cout << "this is not a valid key for a note column, see manual\n";
        }
    }
};

void Pattern::set_note_indices(std::vector<int> note_indices){
    _note_indices = note_indices; };

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