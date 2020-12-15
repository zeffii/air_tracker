// wavetable.cpp
#include <math.h> 
#include <SDL2/SDL.h>
#include "Window.h"
#include "Functions.h"
#include "Wavetable.h"

Wavetable::Wavetable(std::string name, SDL_Rect &_wt_rect){
    wt_name = name;
    wt_rect = _wt_rect;
    wt_text_rect.x = wt_rect.x;
    wt_text_rect.y = wt_rect.y + wt_rect.h + 6;

    generate_wavetable();

};

void Wavetable::generate_wavetable(){
    
    int numsamples = int(wt_rect.w);
    float fi = M_PI * 2.0 / numsamples;
    
    for (int i = 0; i < numsamples; i++){
        RT_Point p2 = {float(i), sin(fi * i)};
        nfsamples.push_back(p2);
    }
};

void Wavetable::draw_wt_window_text(){
    // destroy if present!
    SDL_DestroyTexture(wt_text_texture);

    auto details_surface = TTF_RenderText_Blended(Window::font, wt_name.c_str(), wt_text_color);
    if (!details_surface) { cerr << "failed to create env-text surface \n"; }

    wt_text_texture = SDL_CreateTextureFromSurface(Window::renderer, details_surface);
    if (!wt_text_texture) { cerr << "failed to create env-tetxt texture \n"; }

    SDL_FreeSurface(details_surface);
    SDL_QueryTexture(wt_text_texture, nullptr, nullptr, &wt_text_rect.w, &wt_text_rect.h);
    SDL_RenderCopy(Window::renderer, wt_text_texture, nullptr, &wt_text_rect);

};

void Wavetable::draw_samples(){

    /*
    this rescales nfsamples into a format that will display in the wt_rect
    */

    int y_multiplier = wt_rect.h / 2;
    int y_offset = wt_rect.h / 2 + wt_rect.y;
    int x_offset = wt_rect.x;

    int pcount = nfsamples.size();
    SDL_Point parray[pcount];
    for (int i=0; i < pcount; i++){
        SDL_Point p2 = {int(nfsamples[i].x + x_offset), int((nfsamples[i].y * y_multiplier) + y_offset)};
        parray[i] = p2;
    }

    SDL_SetRenderDrawColor(Window::renderer, 150, 150, 250, 255);
    SDL_RenderDrawPoints(Window::renderer, parray, pcount);

    // int pcount = handles.size();
    // SDL_Point parray[pcount];
    // std::copy(points.begin(), points.end(), parray);
    // SDL_SetRenderDrawColor(renderer, 60, 60, 250, 255);
    // SDL_RenderDrawLines(renderer, parray, pcount);

};

void Wavetable::draw_wt_window(){

    SDL_SetRenderDrawColor(Window::renderer, 26, 26, 26, 255);
    SDL_RenderFillRect(Window::renderer, &wt_rect);

    // if (window.get_active_area() == 0)
    //     SDL_SetRenderDrawColor(renderer, 155, 20, 20, 255);
    // else

    SDL_SetRenderDrawColor(Window::renderer, 50, 50, 250, 255);
    SDL_RenderDrawRect(Window::renderer, &wt_rect);

    draw_samples();
    draw_wt_window_text();
};


