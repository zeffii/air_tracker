#pragma once

#include "Window.h"
#include "Pattern.h"
#include "Selector.h"
#include "Envelope.h"

#include <string>
#include <iostream>
using namespace std;

class Rect{
public:
    Rect(int w, int h, int x, int y, int r, int g, int b, int a);
    void draw() const;
    void pollEvents(
        SDL_Event &event,
        Pattern &mypat,
        Window &window,
        Selector &selection,
        Envelope &env
    );

private:
    int _w, _h, _x, _y, _r, _g, _b, _a;
    int _cw;
    

    int charwidth = 6;
    int line_height = 13;

    // should be moved to pattern? and be automated.    
    int row_index = 0;
    int column_index = 0;

    int column_index_start = 0;
    int column_index_end = 0;
    int row_index_start = 0;
    int row_index_end = 0;

};