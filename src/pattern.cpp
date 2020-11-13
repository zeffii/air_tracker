// pattern.cpp

#include <SDl2/SDL.h>
#include <SDl2/SDL_ttf.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Pattern.h"


using namespace std;

void readPattern(const char* filename, std::vector<string> &lines){
    lines.clear();
    ifstream file (filename);
    string s;
    while (getline(file, s))
        lines.push_back(s);

    file.close();
}


Pattern::Pattern(SDL_Renderer *renderer, const char* pattern_path)
{
    
    SDL_Color colwhite = {255, 255, 255, 255};

    std::vector<string> pattern_data;
    readPattern(pattern_path, pattern_data);

    // 001 C-5 83 D#5 80 G-5 80 ... ..  20 50 40 4E  20 EE 30
    // TTT = tick
    // S* = space
    // H* = hex
    /* 
       TTTSNNNSHHSNNNSHHSNNNSHHSNNNSHHSSHHSHHSHHSHHSSHHSHHSHH
           0   1  2   3  4   5  6   7   8  9  10 11  12 13 14  concept index
           3   2  3   2  3   2  3   2   2  2  2  2   2  2  2   length
           0   4  7   11 14  18 21  24  28 31 34 37  41 44 47  index start
    */

    TTF_Font *font = TTF_OpenFont("res/consola.ttf", 11);
    if (!font) { cerr << "failed to load font\n"; }

    _text_rects.clear();
    for (int unsigned i = 0; i < pattern_data.size(); i++){
    
        //auto text_surface = TTF_RenderText_Blended(font, pattern_data[i].c_str(), colors[hcolor[i%8]]);

        auto text_surface = TTF_RenderText_Blended(font, pattern_data[i].c_str(), colwhite);
        if (!text_surface) { cerr << "failed to create text surface \n"; }

        auto text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        if (!text_texture) { cerr << "failed to create text texture \n"; }

        SDL_Rect trect = {0, 0, 0, 0};
        
        SDL_FreeSurface(text_surface);
        SDL_QueryTexture(text_texture, nullptr, nullptr, &trect.w, &trect.h);
        
        // how wide is the average char, should be monospace.
        // cout << trect.w / pattern_data[i].length() << endl;


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





