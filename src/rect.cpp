#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
using namespace std;

#include "rect.h"


Rect::Rect(int w, int h, int x, int y, int r, int g, int b, int a)
:_w(w), _h(h), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a){}

Rect::Rect(int w, int h, int x, int y, const string &image_path)
:_w(w), _h(h), _x(x), _y(y){
    //auto surface = IMG_load(image_path.c_str());
    SDL_Surface *surface = IMG_Load(image_path.c_str());
    if (!surface){
        cerr << "Failed to create surface \n";
    }
    _tennis_texture = SDL_CreateTextureFromSurface(Window::renderer, surface);
    if (!_tennis_texture){
        cerr << "failed to create texture\n";
    }
    SDL_FreeSurface(surface);
}

Rect::~Rect() {
    SDL_DestroyTexture(_tennis_texture);
}


void Rect::draw() const {
    SDL_Rect rect = {_x, _y, _w, _h};
    if (_tennis_texture){
        SDL_RenderCopy(Window::renderer, _tennis_texture, nullptr, &rect);    
    }
    else{
        SDL_SetRenderDrawColor(Window::renderer, _r, _g, _b, _a);
        SDL_RenderFillRect(Window::renderer, &rect);
    }
}

void Rect::pollEvents(SDL_Event &event){

    if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                _x -= 10;
                break;
            case SDLK_RIGHT:
                _x += 10;
                break;
            case SDLK_UP:
                _y -= 10;
                break;
            case SDLK_DOWN:
                _y += 10;
                break;
        }
    }

}