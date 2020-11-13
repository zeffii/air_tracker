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

    SDL_Rect outlineRect = {_x-1, _y-1, _w+2, _h};
    SDL_SetRenderDrawColor(Window::renderer, 0xE9, 0x3E, 0x4D, 0xFF );        
    SDL_RenderDrawRect(Window::renderer, &outlineRect );    
}

void Rect::pollEvents(SDL_Event &event){

    //int x_offset = 20;
    int y_offset = 20;
    int charwidth = 6;
    int nrows = 16;
    int line_height = 13;

    if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                _x -= charwidth;
                column_index -= 1;
                break;
            case SDLK_RIGHT:
                _x += charwidth;
                column_index += 1;
                break;
            case SDLK_UP:
                _y -= line_height;
                if (_y <= y_offset){ _y = y_offset + (nrows-1)*line_height; } 
                row_index -= 1;
                break;
            case SDLK_DOWN:
                _y += line_height;
                if (_y >=(y_offset + nrows*line_height)){ _y = y_offset;}
                row_index += 1;
                break;
        }
    }
    cout << column_index << ", " << row_index << endl;
}