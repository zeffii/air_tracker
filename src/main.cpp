#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
#include "window.h"
#include "Rect.h"
#include "Text.h"

#include <vector>
#include <iostream>
#include <string>
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
    int hcolor[16] = {2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0};
    SDL_Color colors[3] = {
        {122, 122, 122, 255},
        {202, 202, 202, 255},
        {222, 222, 222, 255}
    };

    string pattern_data[16] = {
        "001 C-5 83 D#5 80 G-5 80 ... ..  20 50 40 4E  20 EE 30",
        "002 ... .. ... .. ... .. ... ..  .. .. .. ..  24 .. ..",
        "003 ... .. ... .. ... .. ... ..  .. .. .. ..  28 .. ..",
        "004 C-5 AC D#5 A0 G-5 A0 ... ..  20 50 AA EE  20 .. 40",
        "005 ... .. ... .. ... .. ... ..  .. .. .. ..  24 .. ..",
        "006 ... .. ... .. ... .. ... ..  .. .. .. ..  27 .. ..",
        "007 ... .. ... .. ... .. ... ..  .. .. .. ..  .. .. ..",
        "008 ... .. ... .. ... .. ... ..  .. .. .. ..  .. .. 80",
        "009 ... .. ... .. ... .. ... ..  .. .. .. ..  .. .. ..",
        "010 ... .. ... .. ... .. ... ..  .. .. .. ..  .. .. ..",
        "011 ... .. ... .. ... .. ... ..  .. .. .. ..  .. .. ..",
        "012 C-5 AC D#5 A0 G-5 A0 ... ..  10 A0 65 EE  40 90 60",
        "013 ... .. ... .. ... .. ... ..  .. .. .. ..  44 .. ..",
        "014 ... .. ... .. ... .. ... ..  .. .. .. ..  54 .. ..",
        "015 ... .. ... .. ... .. ... ..  .. .. .. ..  24 .. ..",
        "016 ... .. ... .. ... .. ... ..  .. .. .. ..  24 .. .."
    };

    int line_height = 16;
    Window window( "Air Tracker", 800, 600);
    Rect rect(120, 120, 900, 100, "res/tennis_ball.png");

    std::vector<Text> texts = {};

    for (int i=0; i<16; i++){
        texts.push_back(Text(Window::renderer, "res/consola.ttf", 12, pattern_data[i], colors[hcolor[i]] ));
    }

    while (!window.isClosed()){
        pollEvents(window, rect);
        rect.draw();
        for (int i=0; i < 16; i++){
            int ypos = 20 + line_height * i;
            texts[i].display(20, ypos, Window::renderer);
        }
        // text.display(20, 20, Window::renderer);
        window.clear();
    }
    return 0;
}