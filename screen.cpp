#include "screen.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512

#define VIEWFIELD_X 10
#define VIEWFIELD_Y 5

//rutas a archivos
#define BACKGROUND_PATH "../resources/images/background.png"
#define BEAM_PATH "../resources/images/grdl8.png"


Screen::Screen() :
	sdl(SDL_INIT_VIDEO), //para sonido agregar la flag correspondiente
	window(
		"Worms 2: el regreso de la lombriz solitaria",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN
	),
	renderer(window /*donde renderiza*/, -1 /*cualquier driver*/, SDL_RENDERER_ACCELERATED),
	backgroundSprite(renderer, BACKGROUND_PATH),
	beamSprite(renderer, BEAM_PATH) {

	this->beams.push_back({ 100, 300, 0});
}



void Screen::draw() {
	//limpio la pantalla
	renderer.Clear();

	//armo la pantalla nueva
	//Texture background(this->renderer, BACKGROUND_PATH);
	renderer.Copy(backgroundSprite, NullOpt, NullOpt);

	for(auto beam : this->beams) {
		renderer.Copy(
			beamSprite,
			Rect(0,0,140,20),
			Rect(beam.x, beam.y, 140, 20),
			(- beam.angle), Point(0, 0)
		);
	}

	//presento la pantalla nueva
	renderer.Present();
	//SDL_Delay(1);
}

Screen::~Screen() {}

void Screen::processInput() {
	std::cout << "todavia no proceso este input" << std::endl;
}

void Screen::start() {

	int i = 0;
	while(1) {

		SDL_Event event;
        //unsigned int frame_ticks = SDL_GetTicks();
		while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
				return;
			}
            if (event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_q) {
                    return;
                }
                processInput();
            }
		}

		draw();
		std::chrono::seconds(1/30);
		i++;

	}
}
