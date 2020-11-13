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
/*
void Rect::pollEvents(SDL_Event &event){

    int x_offset = 20;
    int y_offset = 20;

    //
    //                                  28           41
    //         3  6   10 13  17 20  24 27  31 34 37 40  44 47
    //  TTTSNNNSHHSNNNSHHSNNNSHHSNNNSHHSSHHSHHSHHSHHSSHHSHHSHH
    //      0   1  2   3  4   5  6   7   8  9  10 11  12 13 14  concept index
    //      3   2  3   2  3   2  3   2   2  2  2  2   2  2  2   length
    //      0   4  7   11 14  18 21  24  29 32 35 38  42 45 48  index start
    //    

    if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                column_index -= 1;
                _x -= charwidth;
                if (_x <= (x_offset + 3*6)) { _x = 20 + (nchars_inrow-1) * charwidth; }
                break;
            case SDLK_RIGHT:
                column_index += 1;
                _x += charwidth;
                if (_x >= (x_offset + nchars_inrow * charwidth)) { _x = x_offset + 4*6; }
                break;
            case SDLK_UP:
                row_index -= 1;
                _y -= line_height;
                if (_y < y_offset){ _y = y_offset + (nrows-1) * line_height; } 
                break;
            case SDLK_DOWN:
                row_index += 1;
                _y += line_height;
                if (_y >= (y_offset + nrows * line_height)){ _y = y_offset;}
                break;
        }
    }
    cout << column_index << ", " << row_index << endl;
}
*/

void Rect::pollEvents(SDL_Event &event){

    int x_offset = 20;
    int y_offset = 20;

    /*
                                        28           41
               3  6   10 13  17 20  24 27  31 34 37 40  44 47
        TTTSNNNSHHSNNNSHHSNNNSHHSNNNSHHSSHHSHHSHHSHHSSHHSHHSHH
            0   1  2   3  4   5  6   7   8  9  10 11  12 13 14  concept index
            3   2  3   2  3   2  3   2   2  2  2  2   2  2  2   length
            0   4  7   11 14  18 21  24  29 32 35 38  42 45 48  index start
    */    

    if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                column_index -= 1;
                if (column_index < 0) { column_index = nchars_inrow-5; }
                _x = (x_offset + 4 * charwidth) + (column_index * charwidth);
                
                break;
            case SDLK_RIGHT:
                column_index += 1;
                column_index %= nchars_inrow-4;
                _x = (x_offset + 4 * charwidth) + (column_index * charwidth);
                
                break;
            case SDLK_UP:
                row_index -= 1;
                if (row_index < 0) { row_index = 15; }
                _y = y_offset + (row_index * line_height);
                
                break;
            case SDLK_DOWN:
                row_index += 1;
                row_index %= 16;
                _y = y_offset + (row_index * line_height);
                break;
        }
    }
    cout << column_index << ", " << row_index << endl;
}