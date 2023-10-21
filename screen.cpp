#include "screen.h"

Screen::Screen() : 
sdl(SDL_INIT_VIDEO),
window("POC",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
    1124, 612,
    SDL_WINDOW_RESIZABLE), renderer(window, -1, SDL_RENDERER_ACCELERATED) {
}


void Screen::createSquare(int x, int y, int width, int height, int angle) {
    std::string ruta;
    ruta += DATA_PATH "/imagenes_rotadas/output_";
    int num_image = (angle / (2*3.14159265)) * 100;
    num_image %= 101;
    ruta += std::to_string(num_image);
    ruta += ".png";
    Texture square(renderer, ruta);
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
