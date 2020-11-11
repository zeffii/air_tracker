// Pattern.h

#pragma once 
#include <SDl2/SDL.h>
#include <SDl2/SDL_ttf.h>
#include <string>
#include <vector>

using namespace std;

class Pattern {

    public:
        Pattern(SDL_Renderer *renderer); // , string pattern_data[]);
        void display(int x, int y, SDL_Renderer *renderer) const;

    private:
        std::vector<SDL_Texture *> _text_textures;
        mutable std::vector<SDL_Rect> _text_rects;
               
};