#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

using namespace std;

class Window {
    public:

        Window(const string &title, int width, int height);
        ~Window();
        void pollEvents(SDL_Event &event);
        bool is_ctrl_pressed();
        void set_pressing_ctrl(bool newstate);

        void clear() const;
        inline bool isClosed() const { return _closed; }
    private:
        bool init();
        string _title;
        int _width = 800;
        int _height = 600;
        bool _closed = false;

        bool _pressing_ctrl = false;

        SDL_Window *_window = nullptr;
    public:
        static SDL_Renderer *renderer;
};