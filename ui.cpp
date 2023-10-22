#include "ui.h"

Ui::Ui() : sdl(SDL_INIT_VIDEO), window("SDL2 Window", 100, 100, 640, 480, SDL_WINDOW_SHOWN), renderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
{
    //ctor
}


void Ui::start() {

    while(1) {
        
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            //  y aca evaluamos event.type
        }

    }

}