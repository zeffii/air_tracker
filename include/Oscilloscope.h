#include <SDL2/SDL.h>
#include "Window.h"
#include <math.h> 
#include "Abstractions.h"

void SDLX_draw_dotted_line(SDL_Renderer *renderer, Line line, SDL_Color color);
void draw_oscilloscope(SDL_Renderer *renderer, SDL_Rect osc_rect);