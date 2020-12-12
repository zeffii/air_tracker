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
    void draw_envelope_text_details(Window &window);
    void draw_envelope(Window &window, SDL_Renderer *renderer);
    void draw_handle(SDL_Renderer *renderer, RT_Handle handle);
    void set_active_handle(int nudge_dir);
    void move_handle(int x, int y);
    void modify_handle_count(int num);
    int get_index_of_active_handle();
    void ensure_proper_indexing_of_handles(int active_index);
    void set_looppoint();

private:

    std::string envelope_str;

    SDL_Rect env_rect;
    std::vector<RT_Handle> handles;
    int num_handles_default = 6;
    int handle_size_default = 5;
    int index_of_sustain = 3;

    SDL_Rect _envelope_text_rect = {20, 6, 0, 0};
    SDL_Color _envelope_text_color = {215, 55, 55, 255};
    SDL_Texture *_env_text_texture;
    mutable SDL_Rect _env_text_rect;
};