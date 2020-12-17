/*
// synth_mk1.cpp
#include <math.h> 
#include <SDL2/SDL.h>
#include "Window.h"
#include "Functions.h"
#include "Synth_mk1.h"
#include "Wavetable.h"

Synth_mk1::Synth_mk1(std::string synthname, SDL_Rect &_rui_rect){
    rui_rect = _rui_rect;
    scope = Wavetable(synthname, rui_rect);    
};

void Synth_mk1::draw_ui(){
    scope.draw_wt_window();
};
*/