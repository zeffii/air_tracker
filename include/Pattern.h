// Pattern.h

#pragma once 
#include <SDl2/SDL.h>
#include <SDl2/SDL_ttf.h>
#include <string>
#include <vector>

using namespace std;

class Pattern {

    public:
        Pattern(SDL_Renderer *renderer, const char* pattern_path);
        void display(int x, int y, SDL_Renderer *renderer) const;
        void texture_pattern(SDL_Renderer *renderer);
        void print_row(int row_number);
        void set_char_at(int row_number, int col_number, string character);

    private:
        std::vector<SDL_Texture *> _text_textures;
        mutable std::vector<SDL_Rect> _text_rects;
        
        int _line_height = 13;
        std::vector<string> pattern_data;
};