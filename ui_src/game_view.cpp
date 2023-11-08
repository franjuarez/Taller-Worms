#include "game_view.h"

#define WINDOW_NAME "Worms 2"

#define FPS 30.0f
#define RATE (1000.f / FPS)

#define BACKGROUND_PATH "resources/images/background.png"
#define BEAM_PATH "resources/images/grdl8.png"
#define STILL_WORM_PATH "resources/images/worm_still.png"
//#define STILL_WORM_PATH "../resources/images/waccuse.png"
#define JUMPING_WORM_PATH "resources/images/worm_jump.png"

#include "../game_src/constants_game.h"
#include "../game_src/move.h"

GameView::GameView(const std::string& hostname, const std::string& servname) :
		client(hostname, servname),
		sdl(SDL_INIT_VIDEO/*, SDL_INIT_AUDIO*/),
		window(WINDOW_NAME,
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WINDOW_WIDTH, WINDOW_HEIGHT,
			SDL_WINDOW_SHOWN),
		//no usar vsync porque no voy a poder comprobar si mi loop de fps's funciona
		renderer(window, -1 /*any driver*/, SDL_RENDERER_ACCELERATED),
		backgroundSprite(renderer, BACKGROUND_PATH),
		camX(0), camY(0), mouseHandler(camX, camY) {

	client.start();
	GameDynamic* gs = dynamic_cast<GameDynamic*>(client.getGameStatus());
	std::vector<WormDTO> recievedWorms = gs->getWorms();
	loadWorms(recievedWorms);

	//camX = 0;
	//camY = 0;

	dynamicSpriteSheets.push_back(Texture(renderer,Surface(STILL_WORM_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer,Surface(JUMPING_WORM_PATH).SetColorKey(true, 0)));


	this->currentWormId = 1;
	//en la version final esto es algo que recibo en cada vuelta y capaz cuando me crean

	//this->recievedWorms.push_back(Worm(1, TEAM_1, 100, Position(7, 5 + 1.5)));
	//this->recievedWorms.push_back(Worm(2, TEAM_2, 100, Position(9, 5 + 1.5)));
	
}

void GameView::loadWorms(std::vector<WormDTO>& recievedWorms) {
	for (auto &worm : recievedWorms) {
		wormViews.emplace(
			worm.getId(),
			WormView(worm, dynamicSpriteSheets)
		);
	}
}

void GameView::updateWorms() {
	// std::cout << "pideclientes" << std::endl;
	GameDynamic* gs = dynamic_cast<GameDynamic*>(client.getGameStatus());
	std::cout << "+" << gs << std::endl;
	// std::cout << "termino de pedir al cliente" << std::endl;
	std::vector<WormDTO> recievedWorms = gs->getWorms();
	// std::cout << "pidio worms" << std::endl;
	for (auto &worm : recievedWorms) {
		this->wormViews.at(worm.getId()).update(worm);
	}
	// std::cout << "termino de parsear" << std::endl;
}

void GameView::draw(int i) {
	//limpio la pantalla
	renderer.Clear();

	//armo la nueva pantalla
	renderer.Copy(backgroundSprite, NullOpt, NullOpt);

	for (auto it = wormViews.begin(); it != wormViews.end(); it++) {
		//confirmar que esto esta trabajando inplace y no hace copia
		it->second.display(i, this->renderer, camX, camY);
	}

	//muestro la nueva pantalla
	renderer.Present();
}

void GameView::returnKeyCase(int i) {
	this->wormViews.at(this->currentWormId).jump(i);
}

void GameView::mouseMovementCase(int x, int y) {
	mouseHandler.handleMovement(x, y);
}

void GameView::start() {

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
			int x,y;
			SDL_GetMouseState( &x, &y );
			mouseMovementCase(x,y);
            if (event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_q) {
                    return;
                }
                if(event.key.keysym.sym == SDLK_RETURN) {
                	returnKeyCase(i);
                }
                if (event.key.keysym.sym == SDLK_LEFT) {
					std::cout << "se entro a SDLK_LEFT\n";
                	this->client.execute(new Move(0, LEFT_DIR));
                }
				if (event.key.keysym.sym == SDLK_RIGHT) {
					std::cout << "se entro a SDLK_RIGHT\n";
                	this->client.execute(new Move(0, RIGHT_DIR));
                }
                
                //if ( event.type == SDL_MOUSEMOTION) {
                //	std::cout << "mouse movement" << std::endl;
                //	int x,y;
				//	SDL_GetMouseState( &x, &y );
				//	mouseMovementCase(x,y);
                //}
            }
		}
		// ← aca deberia actualizar Game y conseguir los gusanos actuales y guardarlos
		//en recievedWorms

		//opcion 1: pedirle a client
		updateWorms(); 
		mouseHandler.updateCam();
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















void GameView::join() {
	this->client.kill();
}

GameView::~GameView() {}