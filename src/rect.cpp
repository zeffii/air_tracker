#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
using namespace std;

#include "Rect.h"
#include "Pattern.h"
#include "Window.h"
#include "Functions.h"
#include "Selector.h"
#include "Synth_mk1.h"

Rect::Rect(int w, int h, int x, int y, int r, int g, int b, int a)
:_w(w), _h(h), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a){}



void Rect::draw() const {
    
    // maybe outlineRect should be calculated less frequently, only when cursor/caret moves.
    int outline_start_x = charwidth * draw_cell.cell_start + 20 - 2;
    int outline_start_y = _y-2;
    int outline_width = draw_cell.cell_length * charwidth + 4;
    int outline_height = _h+2;
    SDL_Rect outlineRect = {outline_start_x, outline_start_y, outline_width, outline_height};

    // draw the full cell
    SDL_SetRenderDrawColor(Window::renderer, 0x80, 0x80, 0x90, 0x55 );
    SDL_RenderDrawRect(Window::renderer, &outlineRect );

    // draw the active index (row, column) darker.
    SDL_Rect rect = {_x-1, _y-1, _w+2, _h};
    SDL_SetRenderDrawColor(Window::renderer, _r, _g, _b, _a);
    SDL_RenderFillRect(Window::renderer, &rect);

};

void handle_selection(Selector &selection, int column_index, int row_index){
    selection.push_selector_state();

    switch (selection.get_selector_state()){
        case 1:
            selection.set_start(column_index, row_index);
            selection.set_end(column_index, row_index);
            selection.set_dimensions();
            break;
        case 2:
            selection.set_end(column_index, row_index);
            selection.set_dimensions();
            break;
        default:
            break;
    }
};

void handle_synth_keymap(SDL_Event &event, Synth_mk1 &synth, Window &window){

    int delta = 1;
    if (window.is_rctrl_pressed() || window.is_lctrl_pressed())
        delta = 5;
    else if (window.is_ralt_pressed() || window.is_lalt_pressed())
        delta = 10;

    switch (event.key.keysym.sym) {

        case SDLK_UP:
            synth.change_active_slider(-delta); break;
        case SDLK_DOWN:
            synth.change_active_slider(+delta); break;
        case SDLK_LEFT:
            synth.modify_slider_value(-delta); break; 
        case SDLK_RIGHT:
            synth.modify_slider_value(+delta); break;
        default:
            break;
    }

};

void update_selection_if_active(Selector &selection, int column_index, int row_index){
    if (selection.get_selector_state() == 1){
        selection.set_end(column_index, row_index);
        selection.set_dimensions();
    }
};

void Rect::pollEvents(SDL_Event &event,
    Pattern &mypat, Window &window, Selector &selection, Envelope &env, Synth_mk1 &synth){

    int x_offset = 20;
    int y_offset = 20;
    int nchars_inrow = mypat.get_nchars_in_row();
    int nrows = mypat.get_nrows_in_column();

    Cell_Range cr = {};
    mypat.get_range_of_cell(row_index, column_index, cr);
    draw_cell = cr;

    if (mypat.get_console_listening_state() == true){

        string text = mypat.get_console_string();

        if (event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN) {
            
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && text.length() > 1){

                text = mypat.get_console_string();
                text = text.substr(0, text.length() -1);
                mypat.update_console_string(text);
                mypat.texture_console(Window::renderer);
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN){
                mypat.set_console_listening_state(false);
                mypat.execute_console_command(selection);
                mypat.texture_console(Window::renderer);
            }
            else if (event.type == SDL_TEXTINPUT){
                text = mypat.get_console_string();
                text += event.text.text;
                mypat.update_console_string(text);
                mypat.texture_console(Window::renderer);
            }
        }
        return;
    }

    if (window.get_active_area() == 2){

        // end handling early, moving to next area
        if (event.type == SDL_KEYDOWN){
            if (event.key.keysym.sym == SDLK_TAB){
                window.set_active_area(+1);
                return;
            }
            handle_synth_keymap(event, synth, window);
        }
        return;
    }


    if (window.get_active_area() == 1){
        /*
        when the active area is an envelope, all subsequent key pressed should be captured
        */

        if (event.type == SDL_KEYDOWN){

            int movement = 1;
            if (window.is_rctrl_pressed())
                movement = 4;

            switch (event.key.keysym.sym) {
                case SDLK_TAB:
                    window.set_active_area(+1); break;

                case SDLK_INSERT:
                    env.modify_handle_count(+1); break;
                case SDLK_DELETE:
                    env.modify_handle_count(-1); break;

                case SDLK_LEFT:
                    if (window.is_ralt_pressed()){
                        env.set_active_handle(-1); break;
                    }
                    env.move_handle(-movement, 0); break;

                case SDLK_RIGHT:
                    if (window.is_ralt_pressed()){
                        env.set_active_handle(+1); break;
                    }
                    env.move_handle(movement, 0); break;

                case SDLK_UP:
                    env.move_handle(0, -movement); break;

                case SDLK_DOWN:                
                    env.move_handle(0, movement); break;

                case SDLK_l:
                    env.set_looppoint(); break;

                case SDLK_s:
                    env.store_envelope(); break;

                default:
                    break;
            }
        }

        return;
    }


    if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym) {

            case SDLK_TAB:
                window.set_active_area(+1);
                break;

            case SDLK_BACKSLASH:
                handle_selection(selection, column_index, row_index);
                break;

            case SDLK_LEFT:
                column_index -= 1;
                mypat.carrot_hop_backward(column_index);
                if (column_index < 0) { column_index = nchars_inrow-5; }
                _x = (x_offset + 4 * charwidth) + (column_index * charwidth);
                update_selection_if_active(selection, column_index, row_index);
                break;

            case SDLK_RIGHT:
                column_index += 1;
                mypat.carrot_hop_forward(column_index);
                column_index %= nchars_inrow-4;
                _x = (x_offset + 4 * charwidth) + (column_index * charwidth);
                update_selection_if_active(selection, column_index, row_index);
                break;

            case SDLK_UP:
                if (window.is_lshift_pressed()){
                    //mypat.scroll_vertical(16);
                }
                else {
                    row_index -= 1;
                    if (row_index < 0) { row_index = (nrows-1); }
                    _y = y_offset + (row_index * line_height);
                    update_selection_if_active(selection, column_index, row_index);
                }
                break;

            case SDLK_DOWN:
                if (window.is_lshift_pressed()){
                    //mypat.scroll_vertical(-16);
                }
                else {            
                    row_index += 1;
                    row_index %= nrows;
                    _y = y_offset + (row_index * line_height);
                    update_selection_if_active(selection, column_index, row_index);
                }
                break;

            case SDLK_PAGEUP:
                mypat.scroll_vertical(16); break;

            case SDLK_PAGEDOWN:
                mypat.scroll_vertical(-16); break;

            case SDLK_DELETE: {
                mypat.wipe_cell(selection, column_index, row_index);
                row_index += 1;
                row_index %= nrows;
                _y = y_offset + (row_index * line_height);
                break;
            }

            case SDLK_RETURN:
                mypat.print_row(row_index);
                break;

            case SDLK_EQUALS:
                if (window.is_lshift_pressed()){
                    cout << "next pattern\n";
                }
                break;

            case SDLK_MINUS:
                if (window.is_lshift_pressed()){
                    cout << "last pattern\n";
                }
                break;

            case SDLK_HASH:
                // --> toggle sharp on off.
                mypat.set_char_at(row_index, column_index, "#");
                break;

            case SDLK_BACKQUOTE:
                mypat.set_char_at(row_index, column_index, "`");
                break;

            case SDLK_PERIOD:
                if (window.is_lctrl_pressed()){
                    mypat.wipe_selection(selection);
                } else {
                    mypat.set_char_at(row_index, column_index, ".");
                }
                break;

            case SDLK_SEMICOLON:
                if (window.is_lshift_pressed() || window.is_rshift_pressed()){
                    mypat.set_console_listening_state(true);
                }
                break;

            // CHANGE OCTAVE

            case SDLK_LEFTBRACKET:
                mypat.change_octave(-1);
                break;    
            case SDLK_RIGHTBRACKET:
                mypat.change_octave(+1);
                break;

            // HEX INPUT (mixed notes too) ---------------------- //

            case SDLK_a:
                mypat.set_char_at(row_index, column_index, "A");  // hex 
                break;
            case SDLK_b:
                mypat.set_char_at(row_index, column_index, "B");  // hex   note G
                break;
            case SDLK_c:
                if (window.is_lctrl_pressed()){
                    mypat.store_selection_in_clipboard(selection);
                } else {
                    mypat.set_char_at(row_index, column_index, "C");  // hex   note D
                }
                break;
            case SDLK_d:
                mypat.set_char_at(row_index, column_index, "D");  // hex   note D#
                break;
            case SDLK_e:
                mypat.set_char_at(row_index, column_index, "E");  // hex
                break;
            case SDLK_f:
                mypat.set_char_at(row_index, column_index, "F");  // hex
                break;

            // NUMERICS ONLY (some are captured below by note input..)

            case SDLK_1:
                mypat.set_char_at(row_index, column_index, "1");   // note cut
                break;
            case SDLK_4:
                mypat.set_char_at(row_index, column_index, "4");
                break;
            case SDLK_8:
                mypat.set_char_at(row_index, column_index, "8");
                break;

            // ONLY NOTES  -------------------------------------- //
            /*

                        +1                   +2
            |  C#  D#      F#  G#  A#   |  C#  D#
            | |_2_|_3_| | |_5_|_6_|_7_| | |_9_|_0_| |
            |_Q_|_W_|_E_|_R_|_T_|_Y_|_U_|_I_|_O_|_P_|
            | C   D   E   F   G   A   B | C   D   E 
            */

            case SDLK_q:
                mypat.set_char_at(row_index, column_index, "Q");  //       note C +1
                break;
            case SDLK_2:
                mypat.set_char_at(row_index, column_index, "2");  //       note C#+1
                break;
            case SDLK_w:
                mypat.set_char_at(row_index, column_index, "W");  //       note D +1
                break;
            case SDLK_3:
                mypat.set_char_at(row_index, column_index, "3");  //       note D#+1
                break;
            // case SDLK_e: //                                    //       note E +1
            case SDLK_r:
                if (window.is_lctrl_pressed()){
                    mypat.randomize_selection(selection, 4);
                }
                else {
                    mypat.set_char_at(row_index, column_index, "R");  //   note F +1
                }
                break;
            case SDLK_5:
                mypat.set_char_at(row_index, column_index, "5");  //       note F#+1
                break;
            case SDLK_t:
                mypat.set_char_at(row_index, column_index, "T");  //       note G +1
                break;
            case SDLK_6:
                mypat.set_char_at(row_index, column_index, "6");  //       note G#+1
                break;
            case SDLK_y:
                mypat.set_char_at(row_index, column_index, "Y");  //       note A +1
                break;
            case SDLK_7:
                mypat.set_char_at(row_index, column_index, "7");  //       note A#+1
                break;
            case SDLK_u:
                mypat.set_char_at(row_index, column_index, "U");  //       note B +1
                break;
            case SDLK_i:
                if (window.is_lctrl_pressed()){
                    mypat.perform_selection_interpolation(selection, "tween");
                }
                else if (window.is_lshift_pressed()){
                    mypat.perform_selection_interpolation(selection, "multi");
                } 
                else {
                    mypat.set_char_at(row_index, column_index, "I");  //   note C +2
                }
                break;
            case SDLK_9:
                mypat.set_char_at(row_index, column_index, "9");  //       note C#+2
                break;
            case SDLK_o:
                mypat.set_char_at(row_index, column_index, "O");  //       note D +2
                break;
            case SDLK_0:
                mypat.set_char_at(row_index, column_index, "0");  //       note D#+2
                break;
            case SDLK_p:
                mypat.set_char_at(row_index, column_index, "P");  //       note E +2
                break;

            /*

                        +0               
            |  C#  D#      F#  G#  A#   |
            | |_S_|_D_| | |_G_|_H_|_J_| |
            |_Z_|_X_|_C_|_V_|_B_|_N_|_M_|
            | C   D   E   F   G   A   B |
            */

            case SDLK_z:
                mypat.set_char_at(row_index, column_index, "Z");  //       note C
                break;
            case SDLK_s:
                mypat.set_char_at(row_index, column_index, "S");  //       note C#
                break;
            case SDLK_x:
                if (window.is_lctrl_pressed()){
                    mypat.store_selection_in_clipboard(selection);
                    mypat.wipe_selection(selection);
                } else {
                    mypat.set_char_at(row_index, column_index, "X");  //   note D
                }
                break;
            //case SDLK_d:                                        //       note D#
            //case SDLK_c:                                        //       note E
            case SDLK_v:
                if (window.is_lctrl_pressed()){
                    mypat.paste_clipboard(row_index, column_index);
                } else {
                    mypat.set_char_at(row_index, column_index, "V");  //   note F
                }
                break;
            case SDLK_g:
                mypat.set_char_at(row_index, column_index, "G");  //       note F#
                break;
            //case SDLK_b:                                        // hex   note G
            case SDLK_h:
                mypat.set_char_at(row_index, column_index, "H");  //       note G#
                break;
            case SDLK_n:
                mypat.set_char_at(row_index, column_index, "N");  //       note A
                break;                
            case SDLK_j:
                mypat.set_char_at(row_index, column_index, "J");  //       note A#
                break;                
            case SDLK_m:
                mypat.set_char_at(row_index, column_index, "M");  //       note B
                break;                
        }
    }
    // cout << column_index << ", " << row_index << endl;
};