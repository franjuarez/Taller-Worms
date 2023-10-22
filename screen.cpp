#include "screen.h"

// #define SCREEN_WIDTH 1024
// #define SCREEN_HEIGHT 512

#define PATH_BACKGROUND "../resources/fondo.png"
#define BACKGROUND_PIXEL_X 740
#define BACKGROUND_PIXEL_Y 422

#define PATH_BANANERO "../resources/banana.png"


Screen::Screen(Game& game) : sdl(SDL_INIT_VIDEO), 
        window("El Bananero", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN), 
        renderer(window, -1, SDL_RENDERER_ACCELERATED), game(game) {}

Screen::~Screen() {}

void Screen::start() {
    while(true) { //ver si podemos sacar este while true
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            // aca evaluamos los event.type
            if (event.type == SDL_QUIT) {
				return;
			}
            if (event.type == SDL_KEYDOWN) {
                parseKey(event.key.keysym.sym);
            }
        }
        clear();
        update();
        present();
        std::chrono::seconds(1/12);
    }
}

void Screen::clear() {
    renderer.Clear();
}

void Screen::update() {
    this->entities = game.step();
}

void Screen::present() {

    Texture background(renderer, PATH_BACKGROUND);
    renderer.Copy(background, NullOpt, NullOpt);
    //despues los personajes
    Texture bananero(renderer, PATH_BANANERO);

    int x = this->entities.at(0).x;
    int y = this->entities.at(0).y;
    

    //El 1er Reactangulo dice: desde donde empiezo a copiar (en x y) y que tamaño tiene (en x y)
    //El 2do Reactangulo dice: desde donde empiezo a pegar (en x y) y que tamaño tiene (en x y)
    renderer.Copy(bananero, Rect(4,2,102,134), Rect(x,y,50,70));

    Texture piso(renderer, PATH_BANANERO);
    renderer.Copy(piso, Rect(4,2,102, 134), Rect(0, 390, 1000, 1));
    
    renderer.Present();

}



void Screen::parseKey(SDL_Keycode key){
    if(key == SDLK_RIGHT) {
        printf("derecha\n");
    } else if( key == SDLK_LEFT ) {
        printf("izquierda\n");
    } else if (key == SDLK_b) {
        printf("banana\n");
    }
}