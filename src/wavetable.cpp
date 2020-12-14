// wavetable.cpp
#include <SDL2/SDL.h>
#include "Window.h"
#include "Functions.h"
#include "Wavetable.h"

Wavetable::Wavetable(std::string name, SDL_Rect &_wt_rect){
    wt_name = name;
    wt_rect = _wt_rect;
    wt_text_rect.x = wt_rect.x;
    wt_text_rect.y = wt_rect.y + wt_rect.h + 6;

    generate_wavetable(wt_rect.w);

};

void Wavetable::generate_wavetable(int numsamples){
    // float fi = 5.0 / numsamples;
    // for (int i = 0; i < numsamples; i++){
    //     samples.push_back({sin(fi * i), float(i)});
    // }
};

void Wavetable::draw_wt_window_text(Window &window){
    // destroy if present!
    SDL_DestroyTexture(wt_text_texture);

    auto details_surface = TTF_RenderText_Blended(window.font, wt_name.c_str(), wt_text_color);
    if (!details_surface) { cerr << "failed to create env-text surface \n"; }

    wt_text_texture = SDL_CreateTextureFromSurface(window.renderer, details_surface);
    if (!wt_text_texture) { cerr << "failed to create env-tetxt texture \n"; }

    SDL_FreeSurface(details_surface);
    SDL_QueryTexture(wt_text_texture, nullptr, nullptr, &wt_text_rect.w, &wt_text_rect.h);
    SDL_RenderCopy(window.renderer, wt_text_texture, nullptr, &wt_text_rect);

};

void Wavetable::draw_samples(){

    // int pcount = samples[0].size();
    // // resize and rescale  ( -1, 1 => rect.h / 2 + rect.y
    // for (auto p: samples){
    //     p[0] = int(p[0] * (wt_rect.h / 2.0) + wt_rect.y);
    // }

    // SDL_Point parray[pcount];
    // std::copy(samples.begin(), samples.end(), parray);

    // SDL_SetRenderDrawColor(Window::renderer, 150, 150, 250, 255);
    // SDL_RenderDrawPoints(Window::renderer, parray, pcount);

}

// void Wavetable::draw_wt_window(Window &window, SDL_Renderer *renderer){
void Wavetable::draw_wt_window(Window &window){

    SDL_SetRenderDrawColor(Window::renderer, 26, 26, 26, 255);
    SDL_RenderFillRect(Window::renderer, &wt_rect);

    // if (window.get_active_area() == 0)
    //     SDL_SetRenderDrawColor(renderer, 155, 20, 20, 255);
    // else
    SDL_SetRenderDrawColor(Window::renderer, 50, 50, 250, 255);
    SDL_RenderDrawRect(Window::renderer, &wt_rect);

    draw_samples();

    // int pcount = handles.size();
    // SDL_Point parray[pcount];
    // std::copy(points.begin(), points.end(), parray);
    // SDL_SetRenderDrawColor(renderer, 60, 60, 250, 255);
    // SDL_RenderDrawLines(renderer, parray, pcount);

    draw_wt_window_text(window);

};


