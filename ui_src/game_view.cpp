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
#define WORM_DRAWING_AXE_PATH "../resources/images/draw_axe.bmp"
#define WORM_HOLDING_AXE_PATH "../resources/images/hold_axe.bmp"
#define WORM_DRAWING_BAZOKA_PATH "../resources/images/draw_bazoka.bmp"
#define WORM_HOLDING_BAZOKA_PATH "../resources/images/hold_bazoka.bmp"
#define WORM_DRAWING_RG_PATH "../resources/images/draw_rg.bmp"
#define WORM_HOLDING_RG_PATH "../resources/images/hold_rg.bmp"


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
#define BAZOOKA_ICON_PATH "../resources/images/icons/rocket.bmp"
#define GGRENADE_ICON_PATH "../resources/images/icons/gg.bmp"
#define BAT_ICON_PATH "../resources/images/icons/axe.bmp"
#define TP_ICON_PATH "../resources/images/icons/tp.bmp"
#define MORTAR_ICON_PATH "../resources/images/icons/mortar.bmp"
#define RGRENADE_ICON_PATH "../resources/images/icons/rg.bmp"
#define BANANA_ICON_PATH "../resources/images/icons/banana.bmp"


#define ROCKET_PATH "../resources/images/rocket.bmp"
#define EXPLOSION_PATH "../resources/images/explosion3.bmp"


#include "../game_src/constants_game.h"
#include "../game_src/commands/move.h"
#include "../game_src/commands/jump.h"
#include "../game_src/commands/launch_bazooka.h"
#include "../game_src/commands/teleport.h"
#include "../game_src/commands/hit_upclose.h"
#include "../game_src/commands/throw_grenade.h"
#include "../game_src/constants_game.h"


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
		camX(0), camY(0), mouseX(0), mouseY(0), mouseHandler(camX, camY) {

	this->not_closed = true;
	this->rocketAngle = 45.0f;
	sound.SetVolume(MUSIC_VOLUME);

	client.start();
	std::shared_ptr<GameMap> gs = std::dynamic_pointer_cast<GameMap>(client.getGameStatus());

	this->team = gs->getTeam();

	//rocketSPrites.push_back(/*textura de la explosion*/);
	
	std::vector<WormDTO> recievedWorms = gs->getWorms();
	loadWorms(recievedWorms);
	
	std::vector<BeamDTO> beams = gs->getBeams();
	loadBeams(beams);


	rocketSprites.push_back(Texture(renderer, Surface(ROCKET_PATH).SetColorKey(true,0)));
	rocketSprites.push_back(Texture(renderer, Surface(EXPLOSION_PATH).SetColorKey(true,0)));
	//le paso algo que pueda ser transparente si se agarra la porcion correcta para que se pueda hacer que desaparezca
	rocketSprites.push_back(Texture(renderer, Surface(EXPLOSION_PATH).SetColorKey(true,0)));
	rocketSprites.push_back(Texture(renderer, Surface(RGRENADE_ICON_PATH).SetColorKey(true,0)));

	//para los gusanos. EXTRAER A SU PROPIA CLASE
	dynamicSpriteSheets.push_back(Texture(renderer,Surface(STILL_WORM_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer,Surface(JUMPING_WORM_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer,Surface(WALKING_WORM_PATH).SetColorKey(true,0)));
	dynamicSpriteSheets.push_back(Texture(renderer,Surface(SURRENDING_WORM_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer,Surface(GRAVE_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer,Surface(TP_WORM_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_HITTING_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_DRAWING_AXE_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_HOLDING_AXE_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_DRAWING_BAZOKA_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_HOLDING_BAZOKA_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_DRAWING_RG_PATH).SetColorKey(true, 0)));
	dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_HOLDING_RG_PATH).SetColorKey(true, 0)));


	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_01).SetColorKey(true, 0).SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(220)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_02).SetColorKey(true, 0).SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(220)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_00).SetColorKey(true, 0).SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(220)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_03).SetColorKey(true, 0).SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(220)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_04).SetColorKey(true, 0).SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(220)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_05).SetColorKey(true, 0).SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(220)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_06).SetColorKey(true, 0).SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(220)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_07).SetColorKey(true, 0).SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(220)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_08).SetColorKey(true, 0).SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(220)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_09).SetColorKey(true, 0).SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(220)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_10).SetColorKey(true, 0).SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(220)));
	waterSprites.push_back(Texture(renderer,Surface(WATER_PATH_11).SetColorKey(true, 0).SetBlendMode(SDL_BLENDMODE_BLEND).SetAlphaMod(220)));


	hudTextures.push_back(Texture(renderer, Surface(CURR_WORM_PATH).SetColorKey(true, 0)));
	hudTextures.push_back(Texture(renderer, Surface(BAZOOKA_ICON_PATH).SetColorKey(true, 0)));
	hudTextures.push_back(Texture(renderer, Surface(GGRENADE_ICON_PATH).SetColorKey(true, 0)));
	hudTextures.push_back(Texture(renderer, Surface(BAT_ICON_PATH).SetColorKey(true, 0)));
	hudTextures.push_back(Texture(renderer, Surface(TP_ICON_PATH).SetColorKey(true, 0)));
	hudTextures.push_back(Texture(renderer, Surface(MORTAR_ICON_PATH).SetColorKey(true, 0)));
	hudTextures.push_back(Texture(renderer, Surface(RGRENADE_ICON_PATH).SetColorKey(true, 0)));
	hudTextures.push_back(Texture(renderer, Surface(BANANA_ICON_PATH).SetColorKey(true, 0)));

	this->currentWormId = -1;

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
	std::shared_ptr<GameDynamic> gs = std::dynamic_pointer_cast<GameDynamic>(client.getGameStatus());
	int oldid = this->currentWormId;

	std::vector<WormDTO> recievedWorms = gs->getWorms();

	this->currentWormId = gs->getWormPlayingID();
	if (oldid != currentWormId) {
		inputState = 0;
		if (oldid != -1) { //si se termino el turno
			wormViews.at(oldid).toDefault(0);
		}
	}

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
		it->second.display(i, this->renderer, camX, camY, mouseX, mouseY);
	}
}

void GameView::drawProjectiles(int i) {
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
	renderer.SetDrawBlendMode(SDL_BLENDMODE_BLEND);
	renderer.SetDrawColor(0, 0, 40, 220);
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

void GameView::drawHud(int i) {
	if (this->currentWormId == -1) {
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

	std::vector<int> weapons = this->currentWorm.getWeapons();
	int verticalMargin = 2;
	int toolBarH = 70;
	int toolBarCellWidth = 70;
	int toolBarCellMargin = 4;

	renderer.SetDrawColor(3,3,3, 255);
	renderer.FillRect(0, 0, 
		2*toolBarCellMargin + (toolBarCellWidth + toolBarCellMargin)*weapons.size(),
		toolBarH + 2 * verticalMargin);

	renderer.SetDrawColor(15,15,15,175);

	for (int i = 0; i < weapons.size(); i++) {
		Rect to(
			i*(toolBarCellWidth + toolBarCellMargin) + toolBarCellMargin,
			verticalMargin,
			toolBarCellWidth,
			toolBarH);
		renderer.Copy(hudTextures[i+1], NullOpt, to);
		if (weapons[i] == 0)
			renderer.FillRect(to);
	}


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
	drawHud(i);

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
	this->client.execute(std::make_shared<Jump>(Jump(currentWormId, 2)));
	this->wormViews.at(this->currentWormId).jump(i);
}

void GameView::moveCase(int i, int dir) {
	this->client.execute(std::make_shared<Move>(Move(currentWormId, dir)));
    this->wormViews.at(this->currentWormId).move(i);
}

void GameView::backspaceKeyCase(int i) {
	this->client.execute(std::make_shared<Jump>(Jump(currentWormId, 3)));
}

void GameView::clickCase(int i, int mouseX, int mouseY) {
	//this->wormViews.at(this->currentWormId).tp(i);
	//Position pos((x + camX) / m_to_pix_x, ((y + camY) - WINDOW_HEIGHT) / m_to_pix_y);
	//this->client.execute(new Teleport(currentWormId, pos));

	//rl
	int angle = wormViews.at(currentWormId).shoot(i);
	int dir = (((mouseX + camX) / m_to_pix_x) < this->currentWorm.getX()) ? LEFT_DIR : RIGHT_DIR ;
	//tp
	Position pos((mouseX + camX) / m_to_pix_x, ((mouseY + camY) - WINDOW_HEIGHT) / m_to_pix_y);


	switch (inputState) {
	case BAZOOKA_CODE:
		this->client.execute(std::make_shared<LaunchRocket>(LaunchRocket(BAZOOKA, currentWormId, dir, angle, 40.0f)));
		return;
	case GGRENADE_CODE:
		return;
	case BAT_CODE:
		this->wormViews.at(this->currentWormId).hit(i);
		this->client.execute(std::make_shared<HitUpclose>(HitUpclose(this->currentWormId)));
		return;
	case TP_CODE:
		this->wormViews.at(this->currentWormId).tp(i);
		this->client.execute(std::make_shared<Teleport>(Teleport(currentWormId, pos)));		
		return;
	case MORTAR_CODE:
		return;
	case RGRENADE_CODE:
		this->client.execute(std::make_shared<ThrowGrenade>(ThrowGrenade(RED_GRENADE,
			this->currentWormId,
			dir, angle, 40.0f, 3)));
	case BANANA_CODE:
		return;

	default:
		return;
	}
}

void GameView::bCase(int i) {
	this->wormViews.at(this->currentWormId).hit(i);
	this->client.execute(std::make_shared<HitUpclose>(HitUpclose(this->currentWormId)));
}

void GameView::processInput(SDL_Event event, int i) {
	//if (this->currentWorm.getTeam() != this->team) { revisar la condicion
	if (this->currentWormId == -1) {
		return;
	}
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (inputState == 0)
			return;

		clickCase(i, mouseX, mouseY);
	}

	if (event.type == SDL_KEYDOWN) {
		switch(event.key.keysym.sym) {
		case SDLK_RETURN:
			returnKeyCase(i);
			break;
		case SDLK_BACKSPACE:
			backspaceKeyCase(i);
			break;
		case SDLK_LEFT:
			moveCase(i, LEFT_DIR);
			break;
		case SDLK_RIGHT:
			moveCase(i, RIGHT_DIR);
			break;
		case SDLK_1: //podria ser un mapa pero seria igual de feo en el constructor
			inputState = BAZOOKA_CODE;
			this->wormViews.at(currentWormId).drawBazoka(i);
			break;
		case SDLK_2:
			inputState = GGRENADE_CODE;
			break;
		case SDLK_3:
			inputState = BAT_CODE;
			wormViews.at(currentWormId).drawAxe(i);
			break;
		case SDLK_4:
			inputState = TP_CODE;
			break;
		case SDLK_5:
			inputState = MORTAR_CODE;
			break;
		case SDLK_6:
			inputState = RGRENADE_CODE;
			this->wormViews.at(currentWormId).drawRedGrenade(i);
			break;
		case SDLK_7:
			inputState = BANANA_CODE;
			break;

		std::cout << inputState << std::endl;
		}

	}
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
			SDL_GetMouseState( &mouseX, &mouseY );
			mouseHandler.handleMovement(mouseX, mouseY);

			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_q) {
				return;
			}

			processInput(event, i);
        	////if (this->currentWormId != this->team) { //<- es la linea que va, uso otra para facilitar testeo

			//if (this->currentWormId == -1){
        	//	//ignoro el input si no es del equipo actual
        	//	continue;
        	//}
            //if (event.type == SDL_KEYDOWN) {
            //    if(event.key.keysym.sym == SDLK_RETURN)
            //    	returnKeyCase(i);
            //    
			//	else if(event.key.keysym.sym == SDLK_BACKSPACE) 
            //    	backspaceKeyCase(i);
            //    
            //    else if (event.key.keysym.sym == SDLK_LEFT)
            //        moveCase(i, LEFT_DIR);
            //    else if (event.key.keysym.sym == SDLK_RIGHT) 
            //        moveCase(i, RIGHT_DIR);
            //    else if (event.key.keysym.sym == SDLK_SPACE)
			//		this->client.execute(new LaunchRocket(BAZOOKA, currentWormId, this->currentWorm.getDir(), this->rocketAngle, 40.0f));
			//	else if (event.key.keysym.sym == SDLK_UP)
			//		this->rocketAngle += 5;
			//	else if (event.key.keysym.sym == SDLK_DOWN)
			//		this->rocketAngle -= 5;
			//	else if (event.key.keysym.sym == SDLK_b)
			//		bCase(i);		
            //} else if(event.type == SDL_MOUSEBUTTONDOWN) {
			//	clickCase(i, mouseX, mouseY);
			//}

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