// Pattern.h

#pragma once 
#include <SDl2/SDL.h>
#include <SDl2/SDL_ttf.h>
#include <string>
#include <vector>

using namespace std;

class Pattern {

    public:
        Pattern(SDL_Renderer *renderer, const char* pattern_path); // , string pattern_data[]);
        void display(int x, int y, SDL_Renderer *renderer) const;
        //void texture_pattern(

    private:
        std::vector<SDL_Texture *> _text_textures;
        mutable std::vector<SDL_Rect> _text_rects;
        
        int _line_height = 13;
};