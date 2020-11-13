#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
using namespace std;

#include "rect.h"


Rect::Rect(int w, int h, int x, int y, int r, int g, int b, int a)
:_w(w), _h(h), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a){}



void Rect::draw() const {
    SDL_Rect rect = {_x, _y, _w, _h};
    SDL_SetRenderDrawColor(Window::renderer, _r, _g, _b, _a);
    SDL_RenderFillRect(Window::renderer, &rect);

    SDL_Rect outlineRect = {_x, _y, _w, _h};
    SDL_SetRenderDrawColor(Window::renderer, 0x00, 0x00, 0x90, 0xFF );        
    SDL_RenderDrawRect(Window::renderer, &outlineRect );    
}

void Rect::pollEvents(SDL_Event &event){

    if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                _x -= 6;
                break;
            case SDLK_RIGHT:
                _x += 6;
                break;
            case SDLK_UP:
                _y -= 13;
                break;
            case SDLK_DOWN:
                _y += 13;
                break;
        }
    }

}