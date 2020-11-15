#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
using namespace std;

#include "Rect.h"
#include "Pattern.h"
#include "Window.h"

Rect::Rect(int w, int h, int x, int y, int r, int g, int b, int a)
:_w(w), _h(h), _x(x), _y(y), _r(r), _g(g), _b(b), _a(a){}



void Rect::draw() const {
    // SDL_Rect rect = {_x, _y, _w, _h};
    SDL_Rect rect = {_x-1, _y-1, _w+2, _h};
    SDL_SetRenderDrawColor(Window::renderer, _r, _g, _b, _a);
    SDL_RenderFillRect(Window::renderer, &rect);

    // SDL_Rect outlineRect = {_x-1, _y-1, _w+2, _h};
    // // SDL_SetRenderDrawColor(Window::renderer, 0xE9, 0x6E, 0x6D, 0xFF );
    // SDL_SetRenderDrawColor(Window::renderer, 0x89, 0x3E, 0x3D, 0xFF );
    // SDL_RenderDrawRect(Window::renderer, &outlineRect );    
}

int find_int_in_array(int num_to_find, int numbers[], int arraysize){
    for(int i = 0; i < arraysize; i++){
         if(numbers[i] == num_to_find){ return 1; }
    }
    return 0;
}

void carrot_hop_forward(int &c_index){
    int numbers[12] = {3, 6, 10, 13, 17, 20, 24, 31, 34, 37, 44, 47};
    int spacer_numbers[2] = {27, 40};

    if (find_int_in_array(c_index, numbers, 12)) { c_index += 1; }
    else if (find_int_in_array(c_index, spacer_numbers, 2)) { c_index += 2; }
}

void carrot_hop_backward(int &c_index){
    int numbers[12] = {3, 6, 10, 13, 17, 20, 24, 31, 34, 37, 44, 47};
    int spacer_numbers[2] = {28, 41};

    if (find_int_in_array(c_index, numbers, 12)) { c_index -= 1; }
    else if (find_int_in_array(c_index, spacer_numbers, 2)) { c_index -= 2; }
}

void Rect::pollEvents(SDL_Event &event, Pattern &mypat, Window &window){

    int x_offset = 20;
    int y_offset = 20;

    /*
                                        28           41
               3  6   10 13  17 20  24 27  31 34 37 40  44 47
        TTTSNNNSHHSNNNSHHSNNNSHHSNNNSHHSSHHSHHSHHSHHSSHHSHHSHH
            0   1  2   3  4   5  6   7   8  9  10 11  12 13 14  concept index
            3   2  3   2  3   2  3   2   2  2  2  2   2  2  2   length
            0   4  7   11 14  18 21  24  29 32 35 38  42 45 48  index start
    */    

    if (event.type == SDL_KEYDOWN){
        switch (event.key.keysym.sym) {
            case SDLK_LEFT:
                column_index -= 1;
                carrot_hop_backward(column_index);
                if (column_index < 0) { column_index = nchars_inrow-5; }
                _x = (x_offset + 4 * charwidth) + (column_index * charwidth);
                
                break;
            case SDLK_RIGHT:
                column_index += 1;
                carrot_hop_forward(column_index);
                column_index %= nchars_inrow-4;
                _x = (x_offset + 4 * charwidth) + (column_index * charwidth);
                
                break;
            case SDLK_UP:
                row_index -= 1;
                if (row_index < 0) { row_index = 15; }
                _y = y_offset + (row_index * line_height);
                
                break;
            case SDLK_DOWN:
                row_index += 1;
                row_index %= 16;
                _y = y_offset + (row_index * line_height);
                break;
            case SDLK_RETURN:
                // cout << "YES! ";
                mypat.print_row(row_index);
                break;


            // HEX INPUT (mixed notes too) ---------------------- //

            case SDLK_a:
                mypat.set_char_at(row_index, column_index, "A");  // hex 
                break;
            case SDLK_b:
                mypat.set_char_at(row_index, column_index, "B");  // hex   note G
                break;
            case SDLK_c:
                mypat.set_char_at(row_index, column_index, "C");  // hex   note D
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

            // ONLY NOTES  -------------------------------------- //
            /*

                        +1                   +2
            |  C#  D#      F#  G#  A#   |  C#  D#
            | |_2_|_3_| | |_5_|_6_|_7_| | |_9_|_0_| |
            |_Q_|_W_|_E_|_R_|_T_|_Y_|_U_|_I_|_O_|_P_|
            | C   D   E   F   G   A   B | C   D   E 

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
                mypat.set_char_at(row_index, column_index, "X");  //       note D
                break;
            //case SDLK_d:                                        //       note D#
            //case SDLK_c:                                        //       note E
            case SDLK_v:
                mypat.set_char_at(row_index, column_index, "V");  //       note F
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
}