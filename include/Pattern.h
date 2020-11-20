// Pattern.h

#pragma once 
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "Window.h"

using namespace std;

class Pattern {

    public:
        Pattern(SDL_Renderer *renderer, const char* pattern_path);
        void display(int x, int y, SDL_Renderer *renderer) const;
        void texture_pattern(SDL_Renderer *renderer);
        void print_row(int row_number);
        void set_char_at(int row_number, int col_number, string character);

        int get_nchars_in_row();
        int get_nrows_in_column();

        int get_octave();
        void change_octave(int direction);
        void set_note_indices(std::vector<int> note_indices);
        void set_hex_indices(std::vector<int> hex_indices);
        void set_single_hop_indices(std::vector<int> single_hop);
        void set_double_hop_fw_indices(std::vector<int> double_hop_fw);
        void set_double_hop_bw_indices(std::vector<int> double_hop_bw);

        void carrot_hop_forward(int &c_index);
        void carrot_hop_backward(int &c_index);

    private:
        string pattern_descriptor_str;
        std::vector<string> pattern_data;

        std::vector<SDL_Texture *> _text_textures;
        mutable std::vector<SDL_Rect> _text_rects;
        SDL_Renderer *renderer_placeholder;
        
        int octave = 5;
        int _line_height = 13;

        int _nchars_inrow;
        int _nrows;

        std::vector<int> _note_indices;
        std::vector<int> _hex_indices;
        std::vector<int> _carret_single_hop;
        std::vector<int> _carret_double_hop_fw;
        std::vector<int> _carret_double_hop_bw;
};