#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2pp/SDL2pp.hh>
#include "game.h"
#include <chrono>
#include <vector>

using namespace SDL2pp;

class Screen {
private:
    SDL sdl;
    Window window;
    Renderer renderer;
    Game game;
    std::vector<entities_t> entities;

    void update();

public:
    Screen(Game& game);

    ~Screen();
    
    void start();

    void present();

    void clear();

    void parseKey(SDL_Keycode);
};
#endif

