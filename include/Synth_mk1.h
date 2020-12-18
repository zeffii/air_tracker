#pragma once
// Watetable.h
#include <SDL2/SDL.h>
#include "Window.h"
#include <vector>
#include "Augmentations.h"

class Synth_mk1
{
public:
    Synth_mk1(std::string name, SDL_Rect &_syn_rect);

    void draw_window_text();
    void draw_ui(Window &window);
    void generate_default_wavetable();
    void insert_values_into_wavetable(std::vector<float> points);
    void draw_samples(Window &window);
    void set_dimensions(int x, int y, int w, int h);
    bool is_active();
    void set_active(bool state);
    // int get_active_param();
    void set_active_param(int dir);

private:
    std::string syn_name = "";
    SDL_Rect syn_rect;

    std::vector<RT_Point> nfsamples;
    SDL_Color syn_text_color = {120, 220, 150, 255};
    SDL_Texture *syn_text_texture;
    mutable SDL_Rect syn_text_rect;
    bool active = false;
    int num_params = 8;
    // int active_param = 0;
};