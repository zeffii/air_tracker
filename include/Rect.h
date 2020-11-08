#pragma once

#include "window.h"
#include <string>
#include <iostream>
using namespace std;

class Rect{
public:
    Rect(int w, int h, int x, int y, int r, int g, int b, int a);
    Rect(int w, int h, int x, int y, const string &image_path);
    ~Rect();
    void draw() const;
    void pollEvents(SDL_Event &event);
private:
    int _w, _h, _x, _y, _r, _g, _b, _a;
    SDL_Texture *_tennis_texture = nullptr;  
};