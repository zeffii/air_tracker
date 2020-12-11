//window.cpp
#include <SDL2/SDL.h>
#include "Window.h"
#include "Envelope.h"
#include <math.h>
#include "Functions.h"

Envelope::Envelope(std::string name){

    int x = 400;
    int y = 100;
    int yoffset = 50;
    for (int i=0; i < num_handles_default; i++){
        handles.push_back({
            x + (i * yoffset),
            y,
            5,        // size
            i,        // index
            (int)(i == 0)  // active?
        });
    }
};


void Envelope::DrawDottedLine(SDL_Renderer *renderer, Line line, SDL_Color color){
    // modified from
    // https://stackoverflow.com/a/57646376/1243487
    
    // there seems to be a off by one pixel error in this algorithm.
    std::vector<SDL_Point> points;

    int x0 = line.x1;
    int y0 = line.y1;
    int x1 = line.x2;
    int y1 = line.y2;

    int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = dx+dy, e2;
    int count = 0;
    while (1) {
        if (count < 10) {
            points.push_back({x0, y0});
        }
        if (x0==x1 && y0==y1) break;
        e2 = 2*err;
        if (e2 > dy) { err += dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
        count = (count + 1) % 20;
    }

    unsigned int pcount = points.size();
    SDL_Point parray[pcount];
    std::copy(points.begin(), points.end(), parray);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoints(renderer, parray, pcount);
};


void Envelope::SDLX_draw_dotted_line(SDL_Renderer *renderer, Line line, SDL_Color color){
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

void Envelope::draw_handle(SDL_Renderer *renderer, RT_Handle handle){

    if (handle.active)
        SDL_SetRenderDrawColor(renderer, 255, 20, 20, 255);
    else
        SDL_SetRenderDrawColor(renderer, 155, 20, 20, 255);

    SDL_Rect handle_rect = { handle.x-2, handle.y-2, handle.size, handle.size };
    SDL_RenderDrawRect(renderer, &handle_rect);
};

void Envelope::set_active_handle(int nudge_dir){
    // find active index, and generate new index
    unsigned num_handles = handles.size();

    // get the active and turn it off.
    int current_index = 0;
    for (int unsigned i=0; i < num_handles; i++){
        if (handles[i].active){
            current_index = handles[i].index;
            handles[i].active = 0;
            break;
        }
    }
    current_index += nudge_dir;
    if (current_index < 0)
        current_index = 0;
    else if ((unsigned)current_index >= (unsigned)(num_handles - 1))
        current_index = num_handles-1;

    // set new active handle
    handles[current_index].active = 1;

};

void Envelope::draw_looppoint(SDL_Renderer *renderer, SDL_Rect env_rect){

    int loop_point_x = 90;
    for (int unsigned j = 0; j < handles.size(); j++){
        if (j == (unsigned) index_of_sustain){
            loop_point_x = handles[j].x;
            break;
        }
    }
    
    Line line = { loop_point_x, env_rect.y, loop_point_x, env_rect.y + env_rect.h };
    SDL_Color col_elem = {255, 0, 0, 255};
    SDLX_draw_dotted_line(renderer, line, col_elem);

};



void Envelope::draw_envelope(Window &window, SDL_Renderer *renderer, SDL_Rect env_rect){


    // SDL_Color col_elem2 = {155, 150, 255, 255};
    // Line line2 = {osc_rect.x + 190, osc_rect.y, osc_rect.x + 290, osc_rect.y + osc_rect.h};
    // DrawDottedLine(renderer, line2, col_elem2);

    if (window.get_active_area() == 0)
        SDL_SetRenderDrawColor(renderer, 155, 20, 20, 255);
    else
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    SDL_RenderDrawRect(renderer, &env_rect);

    if (handles.empty())
        return;


    // draw handles!
    vector<SDL_Point> points;
    for (auto handle: handles){
        draw_handle(renderer, handle);
        points.push_back({handle.x, handle.y});
    }

    draw_looppoint(renderer, env_rect); // the line dotted

    int pcount = handles.size();
    SDL_Point parray[pcount];
    std::copy(points.begin(), points.end(), parray);
    SDL_SetRenderDrawColor(renderer, 225, 60, 20, 255);
    SDL_RenderDrawLines(renderer, parray, pcount);

};


void Envelope::move_handle(int x, int y){
    for (int unsigned i=0; i < handles.size(); i++){
        if (handles[i].active){
            handles[i].x += x;
            handles[i].y += y;
            break;
        }
    }
};

void Envelope::modify_handle_count(int active_index, int num){
    int rx = 50;
    int ry = 50;
    int a = 0;
    int b = 1;
    int num_handles = handles.size();

    if (num < 0){        // remove a handle
        /*
        - removes active handle
        - reshuffles handles so indices match
        - toggles active handle on handle+=1
        */
    }
    else if (num > 0){   // insert new handle
        /*
        - find location for new handle
        - insert handle into handles
        - set new handle as active
        */
        if (active_index == num_handles-1){
            // if the last handle is active, insert to the left of last handle
            a = num_handles - 2;
            b = num_handles - 1;
            cout << "between idx " << a << " and idx " << b << endl;

            find_midpoint(handles[a].x, handles[a].y, handles[b].x, handles[b].y, rx, ry);
            cout << "location: " << rx << ", " << ry;

        }
    }

};
