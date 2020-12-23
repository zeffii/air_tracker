// wavetable.cpp
#include <math.h> 
#include <SDL2/SDL.h>
#include "Window.h"
#include "Functions.h"
#include "Synth_mk1.h"
#include "Augmentations.h"

RT_Parameter make_param(int idx, float real_val, float min_val, float max_val, std::string name, std::string shortname){
    RT_Parameter p;
    p.index = idx;    
    p.real_val = real_val;
    p.min_val = min_val;     
    p.max_val = max_val;    
    p.name = name;    
    p.shortname = shortname;
    return p;
}

int math_value_to_slider(float x, RT_Slider sl){
    return int(float(sl.maximum) * (x / sl.max_val));
};

void init_slider_from_parameter(RT_Parameter param, RT_Slider &sl){
    sl.real_val = param.real_val;
    sl.min_val = param.min_val;
    sl.max_val = param.max_val;
    sl.value = math_value_to_slider(sl.real_val, sl);    
}

Synth_mk1::Synth_mk1(std::string name, SDL_Rect &_syn_rect)
{
    syn_name = name;
    syn_rect = _syn_rect;
    syn_text_rect.x = syn_rect.x;
    syn_text_rect.y = syn_rect.y + syn_rect.h + 6;

    generate_parameters();
    generate_sliders();
    generate_wavetable();
};


void Synth_mk1::generate_parameters(){
    gparams[0] = make_param(0,  0.2,     0.0, 6.0, "Attack",         "A");
    gparams[1] = make_param(1,  0.6,     0.0, 6.0, "Decay",          "D");
    gparams[2] = make_param(2,  0.5,     0.0, 1.0, "Sustain",        "S");
    gparams[3] = make_param(3,  0.2,     0.0, 6.0, "Release",        "R");

    gparams[4] = make_param(4,  0.2,     0.0, 6.0, "Filter Attack",  "FA");
    gparams[5] = make_param(5,  0.6,     0.0, 6.0, "Filter Decay",   "FD");
    gparams[6] = make_param(6,  0.5,     0.0, 1.0, "Filter Sustain", "FS");
    gparams[7] = make_param(7,  0.2,     0.0, 6.0, "Filter Release", "FR");

    gparams[8] = make_param(8,  1.0,     0.0, 4.0, "Amplifier",      "Amp");
    gparams[9] = make_param(9,  0.5,     0.0, 4.0, "Osc 1 Amp",      "A01");
    gparams[10] = make_param(10, 0.25,   0.0, 4.0, "Osc 2 Amp",      "A02");
    gparams[11] = make_param(11, 0.123,  0.0, 4.0, "Osc 3 Amp",      "A03");
    gparams[12] = make_param(12, 0.0625, 0.0, 4.0, "Osc 4 Amp",      "A04");

    gparams[13] = make_param(13, 0.0,    0.0, 1.0, "smoothing",      "Sm");
};


void Synth_mk1::generate_sliders(){
    /*
    fill with default values.
    */
    for (int i=0; i < num_params; i++){
        RT_Slider sl;
        sl.active = (i == 0) ? true : false;
        sl.index = i;
        init_slider_from_parameter(gparams[i], sl);
        sliders.push_back(sl);
    }
};

bool Synth_mk1::is_active(){ return active; };
void Synth_mk1::set_active(bool state){ active = state; };
int Synth_mk1::get_active_slider(){ 
    int val = 0;
    for (auto p: sliders) {
        if (p.active) { 
            val = p.index;
            break;
        }
    }
    return val;
};

void Synth_mk1::change_active_slider(int direction){ 

    int currently_active = 0;
    int last_slider_index = (unsigned)sliders.size() - 1;
    for (auto& p: sliders) {
        if (p.active) {currently_active = p.index; };
        p.active = false;
    };

    currently_active += direction;

    if (currently_active <= 0){ currently_active = 0; }
    else if (currently_active >= last_slider_index) { currently_active = last_slider_index;}
    sliders[currently_active].active = true;
};

void Synth_mk1::update_parameter(int idx, int value){

    // first update the gparam associated with this slider,
    float new_proposed_value;
    auto slider = sliders[idx];
    new_proposed_value = map(float(slider.value), float(slider.minimum), float(slider.maximum), float(slider.min_val), float(slider.max_val));
    gparams[idx].real_val = new_proposed_value;
    sliders[idx].real_val = new_proposed_value; // for bookkeeping!
    // then update the wavetable based on all current gparams associated with wavtable ( idx 8 onwards.. )
    if (idx >= 8) { generate_wavetable(); }
    cout << "after p.value " << sliders[idx].value << ", "  << "slider real_val now:" << sliders[idx].real_val << endl;    
    return;
};

void Synth_mk1::modify_slider_value(int direction){
    
    int idx = get_active_slider();
    auto& p = sliders[idx];

    cout << "before p.value " << p.value << ", " << direction << endl;

    // enters this logic gate always, but only ends early if the slider movement would reach
    // outside of minimum or maximum.
    if (direction > 0){
        if (p.value + direction > p.maximum){ 
            p.value = p.maximum; 
            update_parameter(idx, p.value);
            return; 
        }
    }
    else{
        if (p.value + direction < p.minimum){ 
            p.value = p.minimum; 
            update_parameter(idx, p.value);
            return; 
        }
    }

    p.value += direction;
    update_parameter(idx, p.value);
};

void Synth_mk1::generate_wavetable(){
    
    nfsamples.clear();
    int numsamples = int(syn_rect.w);
    float fi = M_PI * 2.0 / numsamples;

    // make sure the  values are constrained with min max val!
    for (int i = 8; i < 14; ++i){
        float_constrain(gparams[i].real_val, sliders[i].min_val, sliders[i].max_val);
    }
    
    // apply values to formula for wavetable
    for (int i = 0; i < numsamples; i++){
        float fy = (float)gparams[9].real_val * sin(fi*i) +
                   (float)gparams[10].real_val * sin(2*fi*i) +
                   (float)gparams[11].real_val * sin(3*fi*i) +
                   (float)gparams[12].real_val * sin(4*fi*i);
        fy *= gparams[8].real_val;
        
        // float_constrain(fy, -1.0, 1.0);  <-- this would be a double foldover
        float_fold_constrain(fy, -1.0, 1.0);

        RT_Point p2 = {float(i), fy};
        nfsamples.push_back(p2);
    }

    /*
    insert noise here, noise seed and noise amplitude :)

    */

    // // smoothing
    if (gparams[13].real_val > 0.0){
        // std::cout << ":: " << gparams[13].real_val << ", " << sliders[13].value << std::endl;
        unweighted_sliding_average(nfsamples, 3, gparams[13].real_val);
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

void Synth_mk1::draw_samples(Window &window){

    /*
    this rescales nfsamples into a format that will display in the wt_rect
    */
    active = (bool)(window.get_active_area() == 2);

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

    SDL_SetRenderDrawColor(window.renderer, 20, 50, 20, 255);
    for (auto p: parray) SDL_RenderDrawLine(window.renderer, p.x, p.y, p.x, syn_rect.h + syn_rect.y);

    dot_green_alpha = active ? 255 : 140;
    SDL_SetRenderDrawColor(window.renderer, 150, 250, 150, dot_green_alpha);
    SDL_RenderDrawPoints(window.renderer, parray, pcount);
};

void Synth_mk1::draw_ui(Window &window){

    SDL_SetRenderDrawColor(window.renderer, 6, 36, 6, 255);
    SDL_RenderFillRect(window.renderer, &syn_rect);

    draw_samples(window);
    draw_window_text();

    int spacer_locations[] = {4, 8};
    int num_spacers = sizeof(spacer_locations)/sizeof(spacer_locations[0]);
    int bg_green = 60;
    int slider_green = 90;
    int slider_height = 10;
    int spacer_height = 4;

    int start_y = syn_rect.y + syn_rect.h + 24;
    int start_x = syn_rect.x + 2;
    int slider_bg_width = syn_rect.w - 1;

    int current_y = start_y;

    for (auto p: sliders){

        bg_green = (p.active) ? 80 : 50;
        slider_green = (p.active) ? 120 : 90;
        
        if (find_int_in_array(p.index, spacer_locations, num_spacers)){ current_y += spacer_height; }

        SDL_Rect slider_bg = {start_x-2, current_y, slider_bg_width, slider_height};
        SDL_SetRenderDrawColor(window.renderer, 20, bg_green, 20, 255);
        SDL_RenderFillRect(window.renderer, &slider_bg);

        int slider_x = start_x + p.value;
        SDL_Rect slider = {slider_x, current_y, slider_height, slider_height};
        SDL_SetRenderDrawColor(window.renderer, 50, slider_green, 50, 255);
        SDL_RenderFillRect(window.renderer, &slider);

        current_y += slider_height + 2;
    }
};


