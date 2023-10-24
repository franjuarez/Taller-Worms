#include "screen.h"
#include "motor.h"
#include <chrono>

#define PATH_BACKGROUND "../data/fondo.png"
#define BACKGROUND_PIXEL_X 740
#define BACKGROUND_PIXEL_Y 422

#define PATH_BANANERO "../data/banana.png"

#define BANANERO_PIXEL_HEIGHT 140 
#define BANANERO_PIXEL_WIDTH 100
#define START_PIXEL_FRONT_X 4
#define START_PIXEL_FRONT_Y 2
#define START_PIXEL_RUN_X 4
#define START_PIXEL_RUN_Y 140
#define PIXEL_RUN_WIDTH 100
#define PIXEL_RUN_HEIGHT 132
#define IMAGE_MARGIN 8

#define GROUND_PIXEL_HEIGHT (-1 * GROUND_HEIGHT * m_to_pix_y) / 2
#define GROUND_PIXEL_WIDTH (GROUND_WIDTH * m_to_pix_x)

#define PATH_BANANA "../data/la_banana.png"
//bananero
#define BANANA_PIXEL_HEIGHT 150
#define BANANA_PIXEL_WIDTH 328
#define BANANA_START_PIXEL_X 1
#define BANANA_START_PIXEL_X 1
//banana
#define LA_BANANA_PIXEL_HEIGHT 997
#define LA_BANANA_PIXEL_WIDTH 1060
#define LA_BANANA_START_PIXEL_X 7
#define LA_BANANA_START_PIXEL_Y 7
#define LA_BANANA_TAMANIO 60

Screen::Screen() : 
sdl(SDL_INIT_VIDEO),
window("EL BANANEROOOOOO",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
    1024, 512,
    SDL_WINDOW_RESIZABLE), renderer(window, -1, SDL_RENDERER_ACCELERATED) {
}   


void Screen::draw(unsigned int frame_ticks) {
    Texture background(renderer, PATH_BACKGROUND);
    renderer.Copy(background, NullOpt, NullOpt);

    Texture piso(renderer, PATH_BANANERO);
    renderer.Copy(piso, Rect(START_PIXEL_FRONT_X,START_PIXEL_FRONT_Y,PIXEL_RUN_WIDTH, PIXEL_RUN_HEIGHT), 
    Rect(0, SCREEN_HEIGHT - GROUND_PIXEL_HEIGHT, GROUND_PIXEL_WIDTH, GROUND_PIXEL_HEIGHT)); 
    
    Surface surface(PATH_BANANERO);
	
    Texture bananero(renderer, surface.SetColorKey(true,0));
    bananero.SetBlendMode(SDL_BLENDMODE_BLEND);

    int x = this->entities.at(0).x;
    int y = this->entities.at(0).y;
    
    //El 1er Reactangulo dice: desde donde empiezo a copiar (en mi imagen) (en x y) y que tamaño tiene (en x y)
    //El 2do Reactangulo dice: desde donde empiezo a pegar (en la pantalla) (en x y) y que tamaño tiene (en x y)
    uint phase = (frame_ticks / 100) % 4;
    if (this->entities.at(0).dir == FRONT) {
        renderer.Copy(bananero, Rect(START_PIXEL_FRONT_X, START_PIXEL_FRONT_Y, PIXEL_RUN_WIDTH,PIXEL_RUN_HEIGHT), Rect(x,y,BANANERO_PIXEL_WIDTH,BANANERO_PIXEL_HEIGHT));
    } else if (this->entities.at(0).dir == LEFT) {        
        renderer.Copy(bananero, Rect(START_PIXEL_RUN_X + phase * (PIXEL_RUN_WIDTH + IMAGE_MARGIN), START_PIXEL_RUN_Y, PIXEL_RUN_WIDTH, PIXEL_RUN_HEIGHT), Rect(x,y,BANANERO_PIXEL_WIDTH,BANANERO_PIXEL_HEIGHT));
    } else if (this->entities.at(0).dir == RIGHT) {
        renderer.Copy(bananero, Rect(START_PIXEL_RUN_X + phase * (PIXEL_RUN_WIDTH + IMAGE_MARGIN), START_PIXEL_RUN_Y, PIXEL_RUN_WIDTH, PIXEL_RUN_HEIGHT), Rect(x,y,BANANERO_PIXEL_WIDTH,BANANERO_PIXEL_HEIGHT), 0.0, NullOpt, SDL_FLIP_HORIZONTAL);
    }
    
    std::cout << "BANMortyANA: " << " x: " << this->entities.at(0).x << " y: " << this->entities.at(0).y << std::endl;

    for (size_t i = 1; i < this->entities.size(); i++) {
        std::cout << "BANANA: " << i << " x: " << this->entities.at(i).x << " y: " << this->entities.at(i).y << std::endl;        
        Surface surfaceBanana(PATH_BANANA);
	
        Texture banana(renderer, surfaceBanana.SetColorKey(true,0));
        banana.SetBlendMode(SDL_BLENDMODE_BLEND);

        int x = this->entities.at(i).x;
        int y = this->entities.at(i).y;

        
        if (this->entities.at(i).dir == LEFT) {        
            renderer.Copy(banana, Rect(LA_BANANA_START_PIXEL_X , LA_BANANA_START_PIXEL_Y, LA_BANANA_PIXEL_WIDTH, LA_BANANA_PIXEL_HEIGHT), Rect(x,y,LA_BANANA_TAMANIO,LA_BANANA_TAMANIO));
        } else if (this->entities.at(i).dir == RIGHT) {
            renderer.Copy(banana, Rect(LA_BANANA_START_PIXEL_X , LA_BANANA_START_PIXEL_Y, LA_BANANA_PIXEL_WIDTH, LA_BANANA_PIXEL_HEIGHT), Rect(x,y,LA_BANANA_TAMANIO,LA_BANANA_TAMANIO), 0.0, NullOpt, SDL_FLIP_HORIZONTAL);
        }
    }
}



/*
	// Load sprites image as a new texture; since there's no alpha channel
	// but we need transparency, use helper surface for which set color key
	// to color index 0 -> black background on image will be transparent on our
	// texture
	Texture sprites(renderer, Surface(DATA_PATH "/M484SpaceSoldier.png")
			.SetColorKey(true, 0));
*/

void Screen::clear() {
    renderer.Clear();
}

void Screen::present() {
    renderer.Present();
    SDL_Delay(1);
}

void Screen::run() {	
	int i = 0;
	while(1) {

		SDL_Event event;
        unsigned int frame_ticks = SDL_GetTicks();
		while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
				return;
			}
            if (event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_q) {
                    return;
                }
                parseKey(event.key.keysym.sym);
            }
		}

		clear();
		this->entities = motor.step();
		draw(frame_ticks);
		present();
		std::chrono::seconds(1/30);
		i++;

	}
}

void Screen::parseKey(SDL_Keycode key){
    if(key == SDLK_RIGHT) {
        motor.move(RIGHT);
        printf("derecha\n");
    } else if( key == SDLK_LEFT ) {
        motor.move(LEFT);
        printf("izquierda\n");
    } else if (key == SDLK_b) {
        motor.throwBanana();
        printf("banana\n");
    } else if (key == SDLK_SPACE) {
        motor.jump();
        printf("jump\n");
    } 
}

Screen::~Screen() {}
