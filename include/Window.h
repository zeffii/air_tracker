#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

using namespace std;

class Window {
    public:

        Window(const string &title, int width, int height);
        ~Window();

        void load_font();
        void close_font();

        // void set_window_title(const char *newtitle);

        void pollEvents(SDL_Event &event);

        bool is_lctrl_pressed();
        bool is_rctrl_pressed();
        bool is_lalt_pressed();
        bool is_ralt_pressed();
        bool is_lshift_pressed();
        bool is_rshift_pressed();
        void set_pressing_lctrl(bool newstate);
        void set_pressing_rctrl(bool newstate);
        void set_pressing_lalt(bool newstate);
        void set_pressing_ralt(bool newstate);
        void set_pressing_lshift(bool newstate);
        void set_pressing_rshift(bool newstate);

        void set_active_area(int shift_area);
        int get_active_area();

        void clear() const;
        inline bool isClosed() const { return _closed; }

    private:
        bool init();
        string _title;
        int _width = 800;
        int _height = 600;
        bool _closed = false;

        bool _pressing_lctrl = false;
        bool _pressing_rctrl = false;
        bool _pressing_lalt = false;
        bool _pressing_ralt = false;        
        bool _pressing_lshift = false;
        bool _pressing_rshift = false;

        int active_area = 0;
        int number_of_areas = 3;  // 0 = pattern , 1 = envelope  . 2 = synth

        SDL_Window *_window = nullptr;
    public:
        static SDL_Renderer *renderer;
        static TTF_Font *font;
        const Uint8 *keyState = SDL_GetKeyboardState(NULL);

};