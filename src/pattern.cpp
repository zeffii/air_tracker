// pattern.cpp

#include <SDl2/SDL.h>
#include <SDl2/SDL_ttf.h>
#include <string>
#include <vector>
#include <iostream>
#include "Pattern.h"

using namespace std;

Pattern::Pattern(SDL_Renderer *renderer){ // , string pattern_data[]){
    TTF_Font *font = TTF_OpenFont("res/consola.ttf", 12);
    if (!font) { cerr << "failed to load font\n"; }

    string msg[3] = {"AAAAAaa", "bbBBBbb", "ccccCCCCcc"};
    SDL_Color colors[3] = { {122, 122, 122, 255}, {182, 202, 212, 255}, {222, 222, 222, 255}};

    // _text_textures.clear();
    _text_rects.clear();

    for (int i=0; i < 3; i++){

        auto text_surface = TTF_RenderText_Solid(font, msg[i].c_str(), colors[i]);
        if (!text_surface) { cerr << "failed to create text surface \n"; }

        auto text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
        if (!text_texture) { cerr << "failed to create text texture \n"; }

        SDL_Rect trect = {0, 0, 0, 0};
        
        SDL_FreeSurface(text_surface);
        SDL_QueryTexture(text_texture, nullptr, nullptr, &trect.w, &trect.h);
        _text_rects.push_back(trect);
        _text_textures.push_back(text_texture);
    }
    cout << "reaches here\n";

};

void Pattern::display(int x, int y, SDL_Renderer *renderer) const { 

    for (int i = 0; i < 3; i++){
        _text_rects[i].x = x + i * 60;
        _text_rects[i].y = y;
        SDL_RenderCopy(renderer, _text_textures[i], nullptr, &_text_rects[i]);
    }

};





