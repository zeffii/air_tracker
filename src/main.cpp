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

void pollEvents(Window &window, Rect &rect){
    SDL_Event event;

    if (SDL_PollEvent(&event)){
        rect.pollEvents(event);
        window.pollEvents(event);
    }
}


int main(int argc, char* args[])
{

    Window window("Air Tracker", 900, 600);
    Pattern mypat(Window::renderer, "res/pattern_data_1.air");
    // Rect cursor(6, 13, 20, 20, 110, 22, 222, 255);
    Rect cursor(6, 13, 20, 20, 2, 2, 2, 255);

    while (!window.isClosed()){
        pollEvents(window, cursor);
        cursor.draw();
        mypat.display(20, 20, Window::renderer);
        window.clear();
    }
    return 0;
}