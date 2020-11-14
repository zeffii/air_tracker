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
    
    readPattern(pattern_path, pattern_data);
    texture_pattern(renderer, pattern_data);
};

void Pattern::texture_pattern(SDL_Renderer *renderer, std::vector<string> &pattern_data){
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


void Pattern::print_row(int row_number){
    cout << pattern_data[row_number] << endl;
};



