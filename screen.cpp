#include "screen.h"

Screen::Screen() : 
sdl(SDL_INIT_VIDEO),
window("POC",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
    1000, 780,
    SDL_WINDOW_RESIZABLE), renderer(window, -1, SDL_RENDERER_ACCELERATED) {
}


void Screen::createSquare(int x, int y, int width, int height) {
    Texture square(renderer, DATA_PATH "/bloque_poc.png");
    renderer.Copy(square, Rect(0, 0, 729, 800), Rect(x, y, width, height));    
}

void Screen::clear() {
    renderer.Clear();
}

void Screen::present() {
    renderer.Present();

    SDL_Delay(1);
}

Screen::~Screen() {}
