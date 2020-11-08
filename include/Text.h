// Text.h

#pragma once 
#include <SDl2/SDL.h>
#include <SDl2/SDL_ttf.h>
#include <string>

using namespace std;

class Text
{
public:
    Text(SDL_Renderer *renderer, const string &font_path, int font_size, const string &message_text, const SDL_Color &color);
    // ~Text();
    void display(int x, int y, SDL_Renderer *renderer) const;

    static SDL_Texture *loadFont(SDL_Renderer *renderer, const string &font_path, 
        int font_size, const string &message_text, const SDL_Color &color);

private:

    SDL_Texture *_text_texture = nullptr;
    mutable SDL_Rect _text_rect;

};