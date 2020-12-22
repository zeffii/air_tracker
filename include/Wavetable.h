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
    void generate_default_wavetable();
    void insert_values_into_wavetable(std::vector<float> points);
    void draw_samples();
    void set_dimensions(int x, int y, int w, int h);

private:
    std::string wt_name = "";
    SDL_Rect wt_rect;

    std::vector<RT_Point> nfsamples;
    SDL_Color wt_text_color = {120, 120, 250, 255};
    SDL_Texture *wt_text_texture;
    mutable SDL_Rect wt_text_rect;

};