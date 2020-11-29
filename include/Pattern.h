// Pattern.h

#pragma once 
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "Window.h"
#include "Selector.h"
#include "Hex_functions.h"
#include "SelectRange.h"
// #include "ConsoleGrammar.h"

using namespace std;

class Pattern {

    public:
        Pattern(SDL_Renderer *renderer, const char* pattern_path);
        ~Pattern();
        void load_font();
        void close_font();

        void texture_pattern(SDL_Renderer *renderer);
        void display(int x, int y, SDL_Renderer *renderer) const;

        void texture_console(SDL_Renderer *renderer);
        void display_console(SDL_Renderer *renderer) const;

        void get_corrected_selection_range(Selector &selection, Selection_Range &sr);
        void store_selection_in_clipboard(Selector &selection);
        void paste_clipboard(int row_index, int column_index);
        void wipe_selection(Selector &selection);

        void print_row(int row_number);
        void set_char_at(int row_number, int col_number, string character);

        bool source_and_destination_similar(int column_index, int selection_length);
        void perform_selection_interpolation(Selector &selection, string mode);
        void interpolate_single(Selection_Params sel);
        void randomize_selection(Selector &selection, int factor);

        int get_nchars_in_row();
        int get_nrows_in_column();

        int get_octave();
        void change_octave(int direction);
        void set_note_indices(std::vector<int> note_indices);
        void set_octave_indices(std::vector<int> note_indices);
        void set_hex_indices(std::vector<int> hex_indices);
        void set_single_hop_indices(std::vector<int> single_hop);
        void set_double_hop_fw_indices(std::vector<int> double_hop_fw);
        void set_double_hop_bw_indices(std::vector<int> double_hop_bw);

        void carrot_hop_forward(int &c_index);
        void carrot_hop_backward(int &c_index);
        void scroll_vertical(int numrows);

        void adjust_visual_cursor_for_scroll(int &row_number);

        void set_console_listening_state(bool state);
        bool get_console_listening_state();
        void execute_console_command(Selector &selection);

        string get_console_string();
        void update_console_string(string new_console_string);

    private:
        string pattern_descriptor_str;
        std::vector<string> pattern_data;
        std::vector<string> clipboard;

        std::vector<SDL_Texture *> _text_textures;
        mutable std::vector<SDL_Rect> _text_rects;

        // console 
        SDL_Texture *_console_texture;
        SDL_Rect _console_rect = {20, 6, 0, 0};
        SDL_Color _console_color = {115, 255, 165, 255};
        bool console_running = false;
        string console_string = "";

        // misc
        SDL_Renderer *renderer_placeholder;
        TTF_Font *font;
        
        int octave = 5;
        int _line_height = 13;

        int _nchars_inrow;
        int _nrows;

        int pattern_x = 20;
        int pattern_y = 20;
        int shift_vertical_times = 0;


        std::vector<int> _note_indices;
        std::vector<int> _octave_indices;
        std::vector<int> _hex_indices;
        std::vector<int> _carret_single_hop;
        std::vector<int> _carret_double_hop_fw;
        std::vector<int> _carret_double_hop_bw;

        // theme data

        int hcolor[8] = {2, 0, 0, 0, 1, 0, 0, 0};
        SDL_Color colors[3] = {
            {122, 122, 122, 255},
            {182, 202, 212, 255},
            {222, 222, 222, 255}
        };
};