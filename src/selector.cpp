// selector_rect.cpp

#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>    // std::minmax
using namespace std;

#include "Rect.h"
#include "Pattern.h"
#include "Window.h"
#include "Functions.h"
#include "Selector.h"


Selector::Selector(int w, int h, int x, int y, int r, int g, int b, int a)
:_w(w), _h(h), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a){}

int Selector::get_selector_state(){ return selector_state; };
void Selector::push_selector_state(){ 
    selector_state += 1;
    selector_state %= 3;
};

void Selector::set_start(int cx, int cy){
    column_start = cx;
    row_start = cy;
};

void Selector::set_end(int cx, int cy){
    column_end = cx;
    row_end = cy;
};

void Selector::set_dimensions(){

    auto result_column = std::minmax({column_start, column_end});
    auto result_row = std::minmax({row_start, row_end});
    
    int low_column = result_column.first;
    int high_column = result_column.second;
    int low_row = result_row.first;
    int high_row = result_row.second;

    _w = (high_column - low_column + 1) * charwidth;
    _h = (high_row - low_row + 1) * line_height;
    _x = (20 + 4 * charwidth) + (low_column * charwidth);
    _y = 20 + (low_row * line_height);
};

vector<int> Selector::get_dimensions(){
    auto result_column = std::minmax({column_start, column_end});
    auto result_row = std::minmax({row_start, row_end});
    return {result_column.first, result_column.second, result_row.first, result_row.second};    
};

void Selector::draw() const {

    if (selector_state == 1 or selector_state == 2){
        
        if (selector_state == 2){
            SDL_Rect rect = {_x, _y, _w, _h};
            SDL_SetRenderDrawColor(Window::renderer, (int)_r/3, (int)_g/3, (int)_b/3, (int)_a/2);
            SDL_RenderFillRect(Window::renderer, &rect);            
        }

        if ((selector_state == 1) || (selector_state == 2)){
            SDL_Rect outlineRect = {_x-1, _y-1, _w+2, _h};

            if (selector_state == 1)
                SDL_SetRenderDrawColor(Window::renderer, _r, _g, _b, _a);
            else
                SDL_SetRenderDrawColor(Window::renderer, 50, 255, 50, _a/3);

            SDL_RenderDrawRect(Window::renderer, &outlineRect );
        }

    }
};
