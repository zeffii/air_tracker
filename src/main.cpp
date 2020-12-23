#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
#include "Window.h"
#include "Rect.h"
#include "Text.h"
#include "Pattern.h"
#include "Functions.h"
#include "Selector.h"
#include "ConsoleGrammar.h"
#include "Wavetable.h"
#include "Synth_mk1.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

#define WIDTH 1280
#define HEIGHT 720


void pollEvents(Window &window, Rect &cursor, Pattern &mypat, Selector &selection, Envelope &env, Synth_mk1 &synth){
    SDL_Event event;

    if (SDL_PollEvent(&event)){
        // case SDL_MOUSEMOTION  : even.mouse.x  
        cursor.pollEvents(event, mypat, window, selection, env, synth);
        window.pollEvents(event);
    }
}

void pollModifierKeys(Window &window){
    SDL_PumpEvents();
    window.set_pressing_lctrl(window.keyState[SDL_SCANCODE_LCTRL]);
    window.set_pressing_rctrl(window.keyState[SDL_SCANCODE_RCTRL]);
    window.set_pressing_lalt(window.keyState[SDL_SCANCODE_LALT]);
    window.set_pressing_ralt(window.keyState[SDL_SCANCODE_RALT]);
    window.set_pressing_lshift(window.keyState[SDL_SCANCODE_LSHIFT]);
    window.set_pressing_rshift(window.keyState[SDL_SCANCODE_RSHIFT]);
}


int main(int argc, char* args[])
{
    int tick_offsetx = 4 * 6;

    Window window("Air Tracker", 900, 1000);
    Pattern mypat("res/pattern_data_1.air");

    int wsx = 580;  // widget start x
    
    SDL_Rect env_rect = {wsx, 20, 270, 100};
    Envelope env("ADSR", env_rect);

    SDL_Rect wt_rect = {wsx, 150, 270, 150};
    Wavetable wt("custom wavetable", wt_rect);

    Rect cursor(6, 13, 20 + tick_offsetx, 20, 2, 2, 2, 255);
    Selector selection(6, 13, 20 + tick_offsetx, 20, 220, 42, 42, 255);

    SDL_Rect rui_rect = {wsx, 350, 270, 150};
    Synth_mk1 synth("ravetable", rui_rect);
    
    while (!window.isClosed()){

        pollModifierKeys(window);
        pollEvents(window, cursor, mypat, selection, env, synth);

        env.draw_envelope(window, Window::renderer);
        cursor.draw();
        wt.draw_wt_window();
        synth.draw_ui(window);
        selection.draw();
        mypat.display(20, 20, Window::renderer);

        if (mypat.get_console_listening_state())
            mypat.display_console(Window::renderer);

        window.clear();
    }
    return 0;
}