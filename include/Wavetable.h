// Watetable.h
#include <SDL2/SDL.h>
#include "Window.h"
// #include "Augmentations.h"
#include <math.h> 
#include <vector>
// #include <algorithm>

class Wavetable
{
public:
    Wavetable(std::string name, SDL_Rect &_wt_rect);
    //~Wavetable();
    void draw_wt_window_text(Window &window);
    void draw_wt_window(Window &window);
    void generate_wavetable(int numsamples);
    void draw_samples();

private:
    std::string wt_name = "";
    SDL_Rect wt_rect;

    SDL_Color wt_text_color = {90, 90, 250, 255};
    SDL_Texture *wt_text_texture;
    mutable SDL_Rect wt_text_rect;

    // std::vector<SDLX_Point> samples;
};