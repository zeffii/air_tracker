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

    //_text_textures.clear();
    //_text_rects.clear();
    // for (int i=0; i < 3; i++){
    //     auto text_surface = TTF_RenderText_Solid(font, msg[i].c_str(), colors[i]);
    //     if (!text_surface) { cerr << "failed to create text surface \n"; }

    //     auto text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    //     if (!text_texture) { cerr << "failed to create text texture \n"; }

    //     _text_rects.push_back(nullptr);
    //     SDL_FreeSurface(text_surface);
    //     SDL_QueryTexture(text_texture, nullptr, nullptr, &_text_rects[i].w, &_text_rects[i].h);
    //     _text_texture.push_back(text_texture);
    // }
    cout << "reaches here\n";

    auto text_surface1 = TTF_RenderText_Solid(font, msg[0].c_str(), colors[0]);
    if (!text_surface1) { cerr << "failed to create text surface \n"; }

    auto text_texture1 = SDL_CreateTextureFromSurface(renderer, text_surface1);
    if (!text_texture1) { cerr << "failed to create text texture \n"; }

    SDL_FreeSurface(text_surface1);
    SDL_QueryTexture(text_texture1, nullptr, nullptr, &_text_rect1.w, &_text_rect1.h);
    _text_texture1 = text_texture1;


    auto text_surface2 = TTF_RenderText_Solid(font, msg[1].c_str(), colors[1]);
    if (!text_surface2) { cerr << "failed to create text surface \n"; }

    auto text_texture2 = SDL_CreateTextureFromSurface(renderer, text_surface2);
    if (!text_texture2) { cerr << "failed to create text texture \n"; }

    SDL_FreeSurface(text_surface2);
    SDL_QueryTexture(text_texture2, nullptr, nullptr, &_text_rect2.w, &_text_rect2.h);
    _text_texture2 = text_texture2;


    auto text_surface3 = TTF_RenderText_Solid(font, msg[2].c_str(), colors[2]);
    if (!text_surface3) { cerr << "failed to create text surface \n"; }

    auto text_texture3 = SDL_CreateTextureFromSurface(renderer, text_surface3);
    if (!text_texture3) { cerr << "failed to create text texture \n"; }

    SDL_FreeSurface(text_surface3);
    SDL_QueryTexture(text_texture3, nullptr, nullptr, &_text_rect3.w, &_text_rect3.h);
    _text_texture3 = text_texture3;

};

void Pattern::display(int x, int y, SDL_Renderer *renderer) const { 
    // for (int i=0; i<3; i++){
    //     _text_rects[i].x = x + i * 60;
    //     _text_rects[i].y = y;
    //     SDL_RenderCopy(renderer, _text_textures[i], nullptr, &_text_rects[i]);
    // }
    _text_rect1.x = x;
    _text_rect1.y = y;
    _text_rect2.x = x + 60;
    _text_rect2.y = y;
    _text_rect3.x = x + 120;
    _text_rect3.y = y;

    SDL_RenderCopy(renderer, _text_texture1, nullptr, &_text_rect1);
    SDL_RenderCopy(renderer, _text_texture2, nullptr, &_text_rect2);
    SDL_RenderCopy(renderer, _text_texture3, nullptr, &_text_rect3);

};





