// Selector_rect.h

#pragma once

#include "window.h"
#include "pattern.h"

#include <string>
#include <iostream>
using namespace std;

class Selector{
public:
    Selector(int w, int h, int x, int y, int r, int g, int b, int a);
    void draw() const;
    void pollEvents(SDL_Event &event, Pattern &mypat, Window &window);
    
    int get_selector_state();
    void push_selector_state();
    void set_dimensions();
    void set_start(int x, int y);
    void set_end(int x, int y);

private:

    int _w, _h, _x, _y, _r, _g, _b, _a;
    int _cw;

    int selector_state = 0;
    int charwidth = 6;
    int line_height = 13;

    // should be moved to pattern? and be automated.    
    int row_index = 0;
    int column_index = 0;

    int column_start, column_end;
    int row_start, row_end;
};