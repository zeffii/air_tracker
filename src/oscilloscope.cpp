//window.cpp
#include <SDL2/SDL.h>
#include "Window.h"
#include "Oscilloscope.h"
#include <math.h>
#include "Functions.h"

// for (auto i: range(0.0, 6.24, 150)){
//     int x = (sin(i) * 50) + 600;
//     int y = (cos(i) * 50) + 600;
//     SDL_RenderDrawPoint(renderer, x, y);
// }

/*
https://stackoverflow.com/a/57646376/1243487
void DrawDottedLine(SDL_Renderer* renderer, int x0, int y0, int x1, int y1) {
    int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = dx+dy, e2;
    int count = 0;
    while (1) {
        if (count < 10) {SDL_RenderDrawPoint(renderer,x0,y0);}
        if (x0==x1 && y0==y1) break;
        e2 = 2*err;
        if (e2 > dy) { err += dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
        count = (count + 1) % 20;
    }
}
*/

void SDLX_draw_dotted_line(SDL_Renderer *renderer, Line line, SDL_Color color){
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int numpoints = (line.y2 - line.y1) / 3;
    SDL_Point pointset[numpoints];

    int j;
    for (int i = line.y1; i < line.y2; i += 3){
        pointset[j] = {line.x1, i};
        j +=1;
    }
    SDL_RenderDrawPoints(renderer, pointset, numpoints);
};



void draw_oscilloscope(SDL_Renderer *renderer, SDL_Rect osc_rect){

    SDL_Color col_elem = {255, 0, 0, 255};
    Line line = {osc_rect.x + 90, osc_rect.y, osc_rect.x + 90, osc_rect.y + osc_rect.h};
    SDLX_draw_dotted_line(renderer, line, col_elem);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &osc_rect);  

};
