#include "game_view.h"

#define WINDOW_NAME "Worms 2"

#define FPS 60.0f
#define RATE (1000.f / FPS)

#define MUSIC_PATH "../resources/music/AdhesiveWombat_Night Shade.mp3"

#define WORM_LIFE_FONT_PATH "../resources/fonts/lazy.ttf"

#define BACKGROUND_PATH "../resources/images/background.png"
#define BEAM_PATH "../resources/images/grdl8.png"	
#define STILL_WORM_PATH "../resources/images/stillworm.bmp"
#define JUMPING_WORM_PATH "../resources/images/worm_jump.bmp"
#define WALKING_WORM_PATH "../resources/images/worm_walk.bmp"
#define SURRENDING_WORM_PATH "../resources/images/worm_surrender.bmp"
#define GRAVE_PATH "../resources/images/grave1.bmp"


#define ROCKET_PATH "../resources/images/rocket.bmp"


#include "../game_src/constants_game.h"
#include "../game_src/move.h"
#include "../game_src/jump.h"
#include "../game_src/attack.h"


GameView::GameView(const std::string& hostname, const std::string& servname) :
		client(hostname, servname),
		sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO),
		sdlttf(),
		window(WINDOW_NAME,
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WINDOW_WIDTH, WINDOW_HEIGHT,
			SDL_WINDOW_SHOWN),
		//no usar vsync porque no voy a poder comprobar si mi loop de fps's funciona
		renderer(window, -1 /*any driver*/, SDL_RENDERER_ACCELERATED),
		mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096),
		sound(MUSIC_PATH), // OGG sound file
		wormsFont(WORM_LIFE_FONT_PATH, 18),
		backgroundSprite(renderer, BACKGROUND_PATH),
		beamSprite(renderer, BEAM_PATH),
		rocketSprite(renderer, Surface(ROCKET_PATH).SetColorKey(true,0)),
		camX(0), camY(0), mouseHandler(camX, camY) {

	sound.SetVolume(MUSIC_VOLUME);

	client.start();
	GameMap* gs = dynamic_cast<GameMap*>(client.getGameStatus());
	
	std::vector<WormDTO> recievedWorms = gs->getWorms();
	loadWorms(recievedWorms);
	
	std::vector<BeamDTO> beams = gs->getBeams();
	loadBeams(beams);

	dynamicSpriteSheets.push_back(Texture(renderer,Surface(STILL_WORM_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer,Surface(JUMPING_WORM_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer,Surface(WALKING_WORM_PATH).SetColorKey(true,0)));
	dynamicSpriteSheets.push_back(Texture(renderer,Surface(SURRENDING_WORM_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer,Surface(GRAVE_PATH).SetColorKey(true, 0)));

	this->lookingDir = 0;
	this->currentWormId = 1;
}

void GameView::loadBeams(std::vector<BeamDTO>& beams) {
	for (auto &beam: beams) {
		// this->beamViews.push_back(BeamView(beam, beamSprite));
		this->beamViews.emplace_back(beam, beamSprite);
	}
}

void GameView::loadWorms(std::vector<WormDTO>& recievedWorms) {
	for (auto &worm : recievedWorms) {
		wormViews.emplace(
			worm.getId(),
			WormView(worm, dynamicSpriteSheets, wormsFont)
		);
	}
}

void GameView::updateEntities(int i) {
	// std::cout << "pide clientes" << std::endl;
	GameDynamic* gs = dynamic_cast<GameDynamic*>(client.getGameStatus());
	// std::cout << "termino de pedir al cliente" << std::endl;
	std::vector<WormDTO> recievedWorms = gs->getWorms();
	this->currentWormId = gs->getWormPlayingID();
	// std::cout << "pidio worms" << std::endl;
	for (auto &worm : recievedWorms) {
		this->wormViews.at(worm.getId()).update(worm, i);
	}

	this->proy = gs->getProjectiles();
	// std::cout << "termino de parsear" << std::endl;
}

void GameView::draw(int i) {
	//limpio la pantalla
	renderer.Clear();

	//armo la nueva pantalla
	renderer.Copy(backgroundSprite, NullOpt, NullOpt);

	for (auto it = beamViews.begin(); it != beamViews.end(); it++) {
		//confirmar que esto esta trabajando inplace y no hace copia
		it->display(this->renderer, camX, camY);
	}

	for (auto it = wormViews.begin(); it != wormViews.end(); it++) {
		//confirmar que esto esta trabajando inplace y no hace copia
		it->second.display(i, this->renderer, camX, camY);
	}

	for (auto &p : this->proy) {
		double angle = -(atan(p.getVelY() / p.getVelX()) * (180.0 / M_PI)); //angula de vel respecto de horizontal
		angle += 90;//quiero que si es 0 tenga una rotacion de 90 grados
		//std::cout << angle << std::endl;
		renderer.Copy(
			rocketSprite,
			Rect(19, 13, 22, 34),
			Rect((p.getX()  * m_to_pix_x) - camX,
				(p.getY() * m_to_pix_y + WINDOW_HEIGHT) - camY,
				20, 20),
			angle, Point(0, 0), 0 //
			);
	}

	//muestro la nueva pantalla
	renderer.Present();
}

void GameView::returnKeyCase(int i) {
	this->client.execute(new Jump(currentWormId, 2));
	this->wormViews.at(this->currentWormId).jump(i);
}

void GameView::moveCase(int i) {
    this->wormViews.at(this->currentWormId).move(i);
}

void GameView::mouseMovementCase(int x, int y) {
	mouseHandler.handleMovement(x, y);
}

void GameView::start() {
	mixer.PlayChannel(-1, sound);

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
                else if(event.key.keysym.sym == SDLK_RETURN) {
                	returnKeyCase(i);
                }

				else if(event.key.keysym.sym == SDLK_BACKSPACE) {
					this->client.execute(new Jump(currentWormId, 3));
                	returnKeyCase(i);
                }
				
                else if (event.key.keysym.sym == SDLK_LEFT) {
					this->lookingDir = 1;
                    this->client.execute(new Move(currentWormId, LEFT_DIR));
                    moveCase(i);

                } else if (event.key.keysym.sym == SDLK_RIGHT) {
					this->lookingDir = 0;
                    this->client.execute(new Move(currentWormId, RIGHT_DIR));
                    moveCase(i);

                } else if (event.key.keysym.sym == SDLK_SPACE) {
					this->client.execute(new Attack(currentWormId, 1, 30.0f, 15.0f));
				}
            }
		}
		// ← aca deberia actualizar Game y conseguir los gusanos actuales y guardarlos
		//en recievedWorms

		//opcion 1: pedirle a client
		updateEntities(i); 
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