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
    void generate_parameters();
    void generate_sliders();
    void generate_wavetable(); // float scale, float amp1, float amp2, float amp3, float amp4);

    bool is_active();
    void set_active(bool state);
    int get_active_slider();

    void draw_window_text();
    void draw_ui(Window &window);
    void insert_values_into_wavetable(std::vector<float> points);
    void draw_samples(Window &window);
    void set_dimensions(int x, int y, int w, int h);
    void change_active_slider(int direction);
    void modify_slider_value(int direction);
    void update_parameter(int idx, int value);

private:

    std::string syn_name = "";
    SDL_Rect syn_rect;

    int num_params = 14;
    RT_Parameter gparams[14];
    // std::vector<RT_Parameter> gparams;  <--- why the fuck not?

    std::vector<RT_Point> nfsamples;
    std::vector<RT_Slider> sliders;
    SDL_Color syn_text_color = {120, 220, 150, 255};
    SDL_Texture *syn_text_texture;
    mutable SDL_Rect syn_text_rect;
    bool active = false;


};