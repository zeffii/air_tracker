#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
#include "Window.h"
#include "Rect.h"
#include "Text.h"
#include "Pattern.h"
#include "Functions.h"
#include "Selector.h"
#include "ConsoleGrammar.h"
#include "Oscilloscope.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

#define WIDTH 1280
#define HEIGHT 720


void pollEvents(Window &window, Rect &cursor, Pattern &mypat, Selector &selection){
    SDL_Event event;

    if (SDL_PollEvent(&event)){
        cursor.pollEvents(event, mypat, window, selection);
        window.pollEvents(event);
    }
}

// void pollModifierKeys(Window &window, volatile const Uint8** keyState){
//     SDL_PumpEvents();
//     window.set_pressing_ctrl(keyState[SDL_SCANCODE_LCTRL]);
//     window.set_pressing_lshift(keyState[SDL_SCANCODE_LSHIFT]);
// }


int main(int argc, char* args[])
{
    int tick_offsetx = 4 * 6;

    Window window("Air Tracker", 700, 1000);

    Pattern mypat(Window::renderer, "res/pattern_data_1.air");
    Rect cursor(6, 13, 20 + tick_offsetx, 20, 2, 2, 2, 255);
    Selector selection(6, 13, 20 + tick_offsetx, 20, 220, 42, 42, 255);

    SDL_Rect osc_rect = {400, 20, 270, 100};
    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    
    while (!window.isClosed()){

        //pollModifierKeys(window, (const Uint8**)keyState);
        SDL_PumpEvents();
        window.set_pressing_ctrl(keyState[SDL_SCANCODE_LCTRL]);
        window.set_pressing_lshift(keyState[SDL_SCANCODE_LSHIFT]);
        window.set_pressing_rshift(keyState[SDL_SCANCODE_RSHIFT]);
 
        pollEvents(window, cursor, mypat, selection);

        draw_oscilloscope(Window::renderer, osc_rect);
        cursor.draw();
        selection.draw();
        mypat.display(20, 20, Window::renderer);

        if (mypat.get_console_listening_state() == true){
            mypat.display_console(Window::renderer);
        }

        window.clear();
    }
    return 0;
}