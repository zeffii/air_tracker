//window.cpp
#include <SDL2/SDL.h>
#include "Window.h"
#include "Oscilloscope.h"
#include <math.h>
#include "Functions.h"

void draw_oscilloscope(SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (auto i: range(0.0, 6.24, 150)){
        int x = (sin(i) * 50) + 600;
        int y = (cos(i) * 50) + 600;
        SDL_RenderDrawPoint(renderer, x, y);
    }
    // SDL_RenderDrawLine(renderer, line.x1, line.y1, line.x2, line.y2);
};
