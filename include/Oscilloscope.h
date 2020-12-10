#include <SDL2/SDL.h>
#include "Window.h"
#include <math.h> 
#include "Abstractions.h"

void DrawDottedLine(SDL_Renderer *renderer, Line line, SDL_Color color);
void SDLX_draw_dotted_line(SDL_Renderer *renderer, Line line, SDL_Color color);
void draw_oscilloscope(SDL_Renderer *renderer, Window &window, SDL_Rect osc_rect);