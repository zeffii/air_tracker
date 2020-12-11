#include <SDL2/SDL.h>
#include "Window.h"
#include <math.h> 
#include "Abstractions.h"
#include <vector>


class Envelope {

public:
    Envelope(std::string name, SDL_Rect &_env_rect);
    void DrawDottedLine(SDL_Renderer *renderer, Line line, SDL_Color color);
    void SDLX_draw_dotted_line(SDL_Renderer *renderer, Line line, SDL_Color color);
    void draw_looppoint(SDL_Renderer *renderer);
    void draw_envelope(Window &window, SDL_Renderer *renderer);
    void draw_handle(SDL_Renderer *renderer, RT_Handle handle);
    void set_active_handle(int nudge_dir);
    void move_handle(int x, int y);
    void modify_handle_count(int num);
    int get_index_of_active_handle();
    void ensure_proper_indexing_of_handles(int active_index);
    void set_looppoint();

private:
    //SDL_Window *_window = nullptr;
    SDL_Rect env_rect;
    std::vector<RT_Handle> handles;
    int num_handles_default = 6;
    int handle_size_default = 5;
    int index_of_sustain = 3;
};