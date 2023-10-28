#include "screen.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512

#define VIEWFIELD_X 10
#define VIEWFIELD_Y 5

#define FPS 60.0f
#define RATE (1000.f / FPS)
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
	//no usar vsync porque no voy a poder comprobar si mi loop de fps's funciona
	renderer(window /*donde renderiza*/, -1 /*cualquier driver*/, SDL_RENDERER_ACCELERATED),
	backgroundSprite(renderer, BACKGROUND_PATH),
	beamSprite(renderer, BEAM_PATH) {

	this->beams.push_back({ 100, 300, 0});
}



void Screen::draw(int i) {
	//limpio la pantalla
	renderer.Clear();

	//armo la pantalla nueva
	//Texture background(this->renderer, BACKGROUND_PATH);
	renderer.Copy(backgroundSprite, NullOpt, NullOpt);

	for(auto &beam : this->beams) {
		renderer.Copy(
			beamSprite,
			Rect(0,0,140,20),
			Rect(beam.x, beam.y, 140, 20),
			(- beam.angle), Point(0, 0)
		);
		beam.angle += (i/i);
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
	int t1 = SDL_GetTicks();
	//float durationInSeconds;
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
		// ← aca deberia actualizar Game
		draw(i);

		int t2 = SDL_GetTicks();
		float rest = RATE - (t2 - t1);

		if (rest < 0) { //me tomo mas tiempo del que tenia
			int behind = -rest; //behind -> por cuanto me pase
			
			//lo que deberia dormir para despertar justo en el inicio de la ventana de un frame
			rest = RATE - fmod(behind, RATE);

			//la cantidad de frames que me saltie y que por ende, deberia dormir
			float lost = behind + rest;
			t1 += lost;
			i += (int )(lost / RATE);
		}
		t1 += RATE; //le sume lo perdido y la rate asique esta actualizado

		i++;
		SDL_Delay(rest);


	}
}
