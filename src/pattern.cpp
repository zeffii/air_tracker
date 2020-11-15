// pattern.cpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Pattern.h"
#include "Window.h"

using namespace std;

int find_int_in_array2(int num_to_find, int numbers[], int arraysize){
    for(int i = 0; i < arraysize; i++){
         if(numbers[i] == num_to_find){ return 1; }
    }
    return 0;
}

void readPattern(const char* filename, std::vector<string> &lines){
    lines.clear();
    ifstream file (filename);
    string s;
    while (getline(file, s))
        lines.push_back(s);

    file.close();
}

Pattern::Pattern(SDL_Renderer *renderer, const char* pattern_path){
    readPattern(pattern_path, pattern_data);
    renderer_placeholder = renderer;
    texture_pattern(renderer);
};

void Pattern::texture_pattern(SDL_Renderer *renderer){
    TTF_Font *font = TTF_OpenFont("res/consola.ttf", 11);
    if (!font) { cerr << "failed to load font\n"; }

    SDL_Color colwhite = {255, 255, 255, 255};
    _text_rects.clear();
    _text_textures.clear();
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
    int note_indices[] = {0, 7, 14, 21};
    int hex_indices[] = {
        4, 5, 11, 12, 18, 19, 24, 25, 29, 30, 32, 33, 35, 36, 38, 39, 42, 43, 45, 46, 48, 49
    };

    // deal with hex data on hex params
    if (find_int_in_array2(col_number, hex_indices, 22)){

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
    // deal with note data on note params
    else if (find_int_in_array2(col_number, note_indices, 4)){
        cout << "trying to change a note\n";
    }
};

