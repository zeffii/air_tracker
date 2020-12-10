#include <SDL2/SDL.h>
#include "Window.h"
#include <math.h> 
#include "Abstractions.h"
#include <vector>


class Envelope {

public:
    Envelope(std::string name);
    void DrawDottedLine(SDL_Renderer *renderer, Line line, SDL_Color color);
    void SDLX_draw_dotted_line(SDL_Renderer *renderer, Line line, SDL_Color color);
    void draw_envelope(Window &window, SDL_Renderer *renderer, SDL_Rect osc_rect);
    void draw_handle(SDL_Renderer *renderer, RT_Handle handle);
    void set_active_handle(int nudge_dir);
    void move_handle(int x, int y);

private:
    //SDL_Window *_window = nullptr;

    std::vector<RT_Handle> handles;
    int num_handles_default = 6;
};