#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
#include "window.h"
#include "Rect.h"
#include "Text.h"
#include "Pattern.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
using namespace std;

#define WIDTH 1280
#define HEIGHT 720

void pollEvents(Window &window){
    SDL_Event event;

    if (SDL_PollEvent(&event)){
        window.pollEvents(event);
    }
}


int main(int argc, char* args[])
{

    Window window( "Air Tracker", 800, 600);
    Pattern mypat(Window::renderer, "res/pattern_data_1.air");

    while (!window.isClosed()){
        pollEvents(window);
        mypat.display(20, 20, Window::renderer);
        window.clear();
    }
    return 0;
}