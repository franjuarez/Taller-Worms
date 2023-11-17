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
#define TP_WORM_PATH "../resources/images/worm_tp.bmp"
#define WORM_HITTING_PATH "../resources/images/worm_hitting.bmp"

#define GRAVE_PATH "../resources/images/grave1.bmp"
#define WATER_PATH_00 "../resources/images/water/blue00.bmp"
#define WATER_PATH_01 "../resources/images/water/blue01.bmp"
#define WATER_PATH_02 "../resources/images/water/blue02.bmp"
#define WATER_PATH_03 "../resources/images/water/blue03.bmp"
#define WATER_PATH_04 "../resources/images/water/blue04.bmp"
#define WATER_PATH_05 "../resources/images/water/blue05.bmp"
#define WATER_PATH_06 "../resources/images/water/blue06.bmp"
#define WATER_PATH_07 "../resources/images/water/blue07.bmp"
#define WATER_PATH_08 "../resources/images/water/blue08.bmp"
#define WATER_PATH_09 "../resources/images/water/blue09.bmp"
#define WATER_PATH_10 "../resources/images/water/blue10.bmp"
#define WATER_PATH_11 "../resources/images/water/blue11.bmp"

#define CURR_WORM_PATH "../resources/images/currentWormIndicator.bmp"
#define WEAPONS_BAR_TEXTURE "../resources/images/water/blue11.bmp"

#define CURRENT_WORM_INDICATOR_TEXTURE 0

#define ROCKET_PATH "../resources/images/rocket.bmp"
#define EXPLOSION_PATH "../resources/images/explosion.bmp"


#include "../game_src/constants_game.h"
#include "../game_src/commands/move.h"
#include "../game_src/commands/jump.h"
#include "../game_src/commands/launch_bazooka.h"
#include "../game_src/commands/teleport.h"
#include "../game_src/commands/hit_upclose.h"


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
		currentWorm(-1, 0, 0, 100, Position(0,0), {}), //-1 para que se sepa que en realidad no hay alguien con turno
		camX(0), camY(0), mouseHandler(camX, camY) {

	this->not_closed = true;
	this->rocketAngle = 45.0f;
	sound.SetVolume(MUSIC_VOLUME);

	client.start();
	GameMap* gs = dynamic_cast<GameMap*>(client.getGameStatus());

	//rocketSPrites.push_back(/*textura de la explosion*/);
	
	std::vector<WormDTO> recievedWorms = gs->getWorms();
	loadWorms(recievedWorms);
	
	std::vector<BeamDTO> beams = gs->getBeams();
	loadBeams(beams);


	rocketSprites.push_back(Texture(renderer, Surface(ROCKET_PATH).SetColorKey(true,0)));
	rocketSprites.push_back(Texture(renderer, Surface(EXPLOSION_PATH).SetColorKey(true,0)));
	//le paso algo que pueda ser transparente si se agarra la porcion correcta para que se pueda hacer que desaparezca
	rocketSprites.push_back(Texture(renderer, Surface(EXPLOSION_PATH).SetColorKey(true,0)));

	dynamicSpriteSheets.push_back(Texture(renderer,Surface(STILL_WORM_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer,Surface(JUMPING_WORM_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer,Surface(WALKING_WORM_PATH).SetColorKey(true,0)));
	dynamicSpriteSheets.push_back(Texture(renderer,Surface(SURRENDING_WORM_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer,Surface(GRAVE_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer,Surface(TP_WORM_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_HITTING_PATH).SetColorKey(true, 0)));

	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_00).SetColorKey(true, 0)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_01).SetColorKey(true, 0)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_02).SetColorKey(true, 0)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_03).SetColorKey(true, 0)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_04).SetColorKey(true, 0)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_05).SetColorKey(true, 0)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_06).SetColorKey(true, 0)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_07).SetColorKey(true, 0)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_08).SetColorKey(true, 0)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_09).SetColorKey(true, 0)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_10).SetColorKey(true, 0)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_11).SetColorKey(true, 0)));


	hudTextures.push_back(Texture(renderer, Surface(CURR_WORM_PATH).SetColorKey(true, 0)));
	//hudTextures.insert(std::make_pair(
	//	"weaponsBar",
	//	Texture(renderer, Surface(WEAPONS_BAR_TEXTURE).SetColorKey(true,0)))
	//);


	this->lookingDir = 0;
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

void GameView::stop() {
	this->not_closed = false;
}

void GameView::updateEntities(int i) {
	GameDynamic* gs = dynamic_cast<GameDynamic*>(client.getGameStatus());

	std::vector<WormDTO> recievedWorms = gs->getWorms();
	this->currentWormId = gs->getWormPlayingID();
	
	for (auto &worm : recievedWorms) {
		this->wormViews.at(worm.getId()).update(worm, i);
		if (worm.getId() == this->currentWormId) {
			this->currentWorm = worm;
		}
	}

	/*
	aca deberia por cada cohete recibido, verificar si esta en mis cohetes, si esta
	no hago nada porque ya voy a actualizar en draw, si no esta lo agrego asi empiezo
	a dibujarlo, no tengo que preocuparme por los que se sacaron esto tambien lo miro
	a medida que actualizo
	*/
	
	this->recievedProjectiles = gs->getExplosives();
	for (auto it = recievedProjectiles.begin(); it != recievedProjectiles.end(); it++) {
		if (projectileViews.find(it->first) != projectileViews.end())
			continue;
		projectileViews.emplace(
			it->second.getID(),
			ProjectileView(it->second, rocketSprites)
		);
	}

	
}

void GameView::drawBeams(int i) {
	for (auto it = beamViews.begin(); it != beamViews.end(); it++) {
		//confirmar que esto esta trabajando inplace y no hace copia
		it->display(this->renderer, camX, camY);
	}
}

void GameView::drawWorms(int i) {
	for (auto it = wormViews.begin(); it != wormViews.end(); it++) {
		//confirmar que esto esta trabajando inplace y no hace copia
		it->second.display(i, this->renderer, camX, camY);
	}
}


void GameView::drawProjectiles(int i) {
/*
	for (auto it = this->proy.begin(); it != proy.end(); it++) {
		double angle = -(atan(it->second.getVelY() / it->second.getVelX()) * (180.0 / M_PI)); //angula de vel respecto de horizontal

		angle += 90;//quiero que si es 0 tenga una rotacion de 90 grados
		//std::cout << angle << std::endl;
		if (it->second.getVelX() < 0) angle -= 180;
		renderer.Copy(
			rocketSprite,
			Rect(19, 13, 22, 34),
			Rect((it->second.getX()  * m_to_pix_x) - camX,
				(it->second.getY() * m_to_pix_y + WINDOW_HEIGHT) - camY,
				20, 20),
			angle, Point(0, 0), 0 //
			);
	}
*/
	/*
	por cada wormView busco si esta en los recibidos. si esta lo actualizo usando justamente
	su nueva intancia. si no esta es porque choco y por ende tengo que indicarle que explote
	*/
	
	for (auto it = projectileViews.begin(); it != projectileViews.end(); it++) {
		if (recievedProjectiles.find(it->first) != recievedProjectiles.end()) {
			it->second.update(recievedProjectiles.at(it->first), i);
		} else {
			it->second.explode(i);
		}
		it->second.display(i, renderer, camX, camY);

	}
}

void GameView::drawWater(int i) {
	renderer.SetDrawColor(0, 0, 40);
	renderer.FillRect(
		0,
		-0.5 * m_to_pix_y + WINDOW_HEIGHT - camY,
		WINDOW_WIDTH, WINDOW_HEIGHT * 2
	);

	renderer.Copy(
		waterSprites[(i / 4) % waterSprites.size()],
		NullOpt,
		Rect(0, 1.5 * m_to_pix_y + WINDOW_HEIGHT - camY, WINDOW_WIDTH, 100)
	);
}

void GameView::drawUi(int i) {
	if (this->currentWorm.getId() == -1) {
		//si no hay nadie jugando no dibujo esto.
		return;
	}
	renderer.Copy(
		hudTextures[CURRENT_WORM_INDICATOR_TEXTURE],
		Rect(21, 60 * ((i/4) % 30) + 16, 19, 33),
		Rect(
			this->currentWorm.getX() * m_to_pix_x - camX,
			((this->currentWorm.getY() + 1.5) * m_to_pix_y) + WINDOW_HEIGHT - camY,
			20, 20
			)
		);
}

void GameView::draw(int i) {

	updateEntities(i); 
	mouseHandler.updateCam();

	renderer.Clear();
	renderer.Copy(backgroundSprite, NullOpt, NullOpt);
	drawBeams(i);
	drawWorms(i);
	drawProjectiles(i);
	drawWater(i);
	drawUi(i);

	/*
	aca deberia por cada cohete que tengo, verificar si esta en el map recibido
		* si esta actualizo
		* si no esta le indico que explote
		*lo dibujo
		*chequeo si su animacion de explotar termino en cuyo caso lo remuevo
	*/

	//muestro la nueva pantalla
	renderer.Present();
}

void GameView::returnKeyCase(int i) {
	this->client.execute(new Jump(currentWormId, 2));
	this->wormViews.at(this->currentWormId).jump(i);
}

void GameView::moveCase(int i, int dir) {
	this->lookingDir = dir;
	this->client.execute(new Move(currentWormId, dir));
    this->wormViews.at(this->currentWormId).move(i);
}

void GameView::backspaceKeyCase(int i) {
	this->client.execute(new Jump(currentWormId, 3));
}

void GameView::clickCase(int i, int x, int y) {
	this->wormViews.at(this->currentWormId).tp(i);
	Position pos((x + camX) / m_to_pix_x, ((y + camY) - WINDOW_HEIGHT) / m_to_pix_y);
	this->client.execute(new Teleport(currentWormId, pos));
}

void GameView::bCase(int i) {
	this->wormViews.at(this->currentWormId).hit(i);
	this->client.execute(new HitUpclose(this->currentWormId));
}

void GameView::start() {
	// mixer.PlayChannel(-1, sound);

	int i = 0;
	int t1 = SDL_GetTicks();
	//float durationInSeconds;
	while(not_closed) {
		SDL_Event event;
        //unsigned int frame_ticks = SDL_GetTicks();
		while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
				return;
			}
			int x,y;
			SDL_GetMouseState( &x, &y );
			mouseHandler.handleMovement(x,y);
            if (event.type == SDL_KEYDOWN) {
				//aca deberia llamar al  handler
                if(event.key.keysym.sym == SDLK_q)
                    return;

                else if(event.key.keysym.sym == SDLK_RETURN)
                	returnKeyCase(i);
                
				else if(event.key.keysym.sym == SDLK_BACKSPACE) 
                	backspaceKeyCase(i);
                
                else if (event.key.keysym.sym == SDLK_LEFT)
                    moveCase(i, LEFT_DIR);

                else if (event.key.keysym.sym == SDLK_RIGHT) 
                    moveCase(i, RIGHT_DIR);

                else if (event.key.keysym.sym == SDLK_SPACE)
					this->client.execute(new LaunchRocket(currentWormId, this->lookingDir, this->rocketAngle, 40.0f));

				else if (event.key.keysym.sym == SDLK_UP)
					this->rocketAngle += 5;
				else if (event.key.keysym.sym == SDLK_DOWN)
					this->rocketAngle -= 5;
				else if (event.key.keysym.sym == SDLK_b)
					bCase(i);
					
            } else if(event.type == SDL_MOUSEBUTTONDOWN) {
				clickCase(i, x, y);
			}

		}
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