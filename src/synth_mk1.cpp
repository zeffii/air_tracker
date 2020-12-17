// wavetable.cpp
#include <math.h> 
#include <SDL2/SDL.h>
#include "Window.h"
#include "Functions.h"
#include "Synth_mk1.h"
#include "Augmentations.h"

Synth_mk1::Synth_mk1(std::string name, SDL_Rect &_syn_rect){
    syn_name = name;
    syn_rect = _syn_rect;
    syn_text_rect.x = syn_rect.x;
    syn_text_rect.y = syn_rect.y + syn_rect.h + 6;

    generate_default_wavetable();

};

bool Synth_mk1::is_active(){ return active; };
void Synth_mk1::set_active(bool state){ active = state; };

void Synth_mk1::generate_default_wavetable(){
    
    int numsamples = int(syn_rect.w);
    float fi = M_PI * 2.0 / numsamples;
    
    for (int i = 0; i < numsamples; i++){
        float fy = (float) 0.5*sin(fi*i) + 
                   (float) 0.25*sin(2*fi*i) + 
                   (float) 0.125*sin(3*fi*i) + 
                   (float) 0.0625*sin(4*fi*i);

        RT_Point p2 = {float(i), fy};
        nfsamples.push_back(p2);
    }
};

void Synth_mk1::insert_values_into_wavetable(std::vector<float> points){
    nfsamples.clear();
    int numsamples = int(syn_rect.w);
    for (int i = 0; i < numsamples; i++){
        RT_Point p2 = {float(i), points[i]}; 
        nfsamples.push_back(p2);
    }
};

void Synth_mk1::set_dimensions(int x, int y, int w, int h){
    syn_rect.x = x;
    syn_rect.y = y;
    syn_rect.w = w;
    syn_rect.h = h;
};


void Synth_mk1::draw_window_text(){
    // destroy if present!
    SDL_DestroyTexture(syn_text_texture);

    auto details_surface = TTF_RenderText_Blended(Window::font, syn_name.c_str(), syn_text_color);
    if (!details_surface) { cerr << "failed to create env-text surface \n"; }

    syn_text_texture = SDL_CreateTextureFromSurface(Window::renderer, details_surface);
    if (!syn_text_texture) { cerr << "failed to create env-tetxt texture \n"; }

    SDL_FreeSurface(details_surface);
    SDL_QueryTexture(syn_text_texture, nullptr, nullptr, &syn_text_rect.w, &syn_text_rect.h);
    SDL_RenderCopy(Window::renderer, syn_text_texture, nullptr, &syn_text_rect);

};

void Synth_mk1::draw_samples(){

    /*
    this rescales nfsamples into a format that will display in the wt_rect
    */
    // active = (Window::active_area == 2);

    int y_multiplier = syn_rect.h / 2;
    int y_offset = syn_rect.h / 2 + syn_rect.y;
    int x_offset = syn_rect.x;
    int dot_green_alpha = 255;
    int pcount = nfsamples.size();
    SDL_Point parray[pcount];
    for (int i=0; i < pcount; i++){
        SDL_Point p2 = {int(nfsamples[i].x + x_offset), int((nfsamples[i].y * y_multiplier) + y_offset)};
        parray[i] = p2;
    }

    SDL_SetRenderDrawColor(Window::renderer, 20, 50, 20, 255);
    for (auto p: parray) SDL_RenderDrawLine(Window::renderer, p.x, p.y, p.x, syn_rect.h + syn_rect.y);

    dot_green_alpha = active ? 255 : 140;
    SDL_SetRenderDrawColor(Window::renderer, 150, 250, 150, dot_green_alpha);
    SDL_RenderDrawPoints(Window::renderer, parray, pcount);

    // int pcount = handles.size();
    // SDL_Point parray[pcount];
    // std::copy(points.begin(), points.end(), parray);
    // SDL_SetRenderDrawColor(renderer, 60, 60, 250, 255);
    // SDL_RenderDrawLines(renderer, parray, pcount);

};

void Synth_mk1::draw_ui(){

    SDL_SetRenderDrawColor(Window::renderer, 6, 36, 6, 255);
    SDL_RenderFillRect(Window::renderer, &syn_rect);

    // if (window.get_active_area() == 0)
    //     SDL_SetRenderDrawColor(renderer, 155, 20, 20, 255);
    // else


    draw_samples();
    draw_window_text();

    // SDL_SetRenderDrawColor(Window::renderer, 50, 150, 50, 255);
    //SDL_SetRenderDrawColor(Window::renderer, 0, 20, 0, 255);
    //SDL_RenderDrawRect(Window::renderer, &syn_rect);

    int num_params = 8;
    int active_param = 3;
    int start_y = syn_rect.y + syn_rect.h + 24;
    int start_x = syn_rect.x;
    int slider_height = 10;
    int slider_bg_width = syn_rect.w;
    int spacer_height = 4;
    int spacer_locations[] = {4};
    int bg_green = 60;
    int slider_green = 90;

    int current_y = start_y;
    for (int i = 0; i < num_params; i++){
        
        if (find_int_in_array(i, spacer_locations, 1)){ current_y += spacer_height; }

        SDL_Rect slider_bg = {start_x, current_y, slider_bg_width, slider_height};
        bg_green = (i == active_param) ? 80 : 50;
        SDL_SetRenderDrawColor(Window::renderer, 20, bg_green, 20, 255);
        
        SDL_RenderFillRect(Window::renderer, &slider_bg);

        int slider_x = start_x + (i * 30);
        SDL_Rect slider = {slider_x, current_y, slider_height, slider_height};
        slider_green = (i == active_param) ? 120 : 90;
        SDL_SetRenderDrawColor(Window::renderer, 50, slider_green, 50, 255);
        SDL_RenderFillRect(Window::renderer, &slider);

        current_y += slider_height + 2;
    }

};


