#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
#include "Window.h"
#include "Rect.h"
#include "Text.h"
#include "Pattern.h"
#include "Functions.h"
#include "Selector.h"

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

/*

SDL_Event ev;

...

while (SDL_PollEvent(&ev) != 0){

    if (ev.type == SDL_TEXTINPUT || ev.type == SDL_KEYDOWN) {
        system('cls');  // or 'clear' for 'nx
        if(ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0)
            text = text.substr(0, text.length() -1);
        else if (ev.type == SDL_TEXTINPUT)
            text += ev.text.text;

        std::cout << text << std::endl;
    }
}

*/

int main(int argc, char* args[])
{
    int tick_offsetx = 4 * 6;

    Window window("Air Tracker", 900, 600);

    Pattern mypat(Window::renderer, "res/pattern_data_1.air");
    Rect cursor(6, 13, 20 + tick_offsetx, 20, 2, 2, 2, 255);
    Selector selection(6, 13, 20 + tick_offsetx, 20, 220, 42, 42, 255);

    const Uint8 *keyState = SDL_GetKeyboardState(NULL);
    
    while (!window.isClosed()){

        //pollModifierKeys(window, (const Uint8**)keyState);
        SDL_PumpEvents();
        window.set_pressing_ctrl(keyState[SDL_SCANCODE_LCTRL]);
        window.set_pressing_lshift(keyState[SDL_SCANCODE_LSHIFT]);
 
        pollEvents(window, cursor, mypat, selection);
        
        cursor.draw();
        selection.draw();
        mypat.display(20, 20, Window::renderer);
        window.clear();
    }
    return 0;
}