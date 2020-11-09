#include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
#include "window.h"
#include "Rect.h"
#include "Text.h"

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

void readPattern(const char* filename, std::vector<string> &lines){
    lines.clear();
    ifstream file(filename);
    string s;
    while (getline(file, s))
        lines.push_back(s);
}

int main(int argc, char* args[])
{
    int hcolor[16] = {2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0};
    SDL_Color colors[3] = {
        {122, 122, 122, 255},
        {202, 202, 202, 255},
        {222, 222, 222, 255}
    };

    // ofstream pattern_data_file;
    // pattern_data_file.open("res/pattern_data_1.air");
    // pattern_data_file << "this line ";   // writes to the file
    std::vector<string> pattern_data;
    readPattern("res/pattern_data_1.air", pattern_data);
    cout << pattern_data.size();

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