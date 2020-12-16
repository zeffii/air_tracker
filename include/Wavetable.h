// Watetable.h
#include <SDL2/SDL.h>
#include "Window.h"
#include "Augmentations.h"
#include <vector>
// #include <algorithm>

class Wavetable
{
public:
    Wavetable(std::string name, SDL_Rect &_wt_rect);
    //~Wavetable();
    void draw_wt_window_text();
    void draw_wt_window();
    void generate_wavetable();
    void draw_samples();

private:
    std::string wt_name = "";
    SDL_Rect wt_rect;

    std::vector<RT_Point> nfsamples;
    SDL_Color wt_text_color = {120, 120, 250, 255};
    SDL_Texture *wt_text_texture;
    mutable SDL_Rect wt_text_rect;

};