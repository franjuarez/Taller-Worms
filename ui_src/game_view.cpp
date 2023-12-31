#include "game_view.h"
#include "../game_src/constants_game.h"
#include "../game_src/commands/move.h"
#include "../game_src/commands/jump.h"
#include "../game_src/commands/launch_bazooka.h"
#include "../game_src/commands/remote_operated.h"
#include "../game_src/commands/hit_upclose.h"
#include "../game_src/commands/throw_grenade.h"
#include "../game_src/commands/drop_dynamite.h"

#include "../game_src/commands/cheats.h"
#include "../shared_src/constants.h"

#define WINDOW_NAME "Worms 2"

#define FPS 60.0f
#define RATE (1000.f / FPS)
#define AIM_SIZE 0.5
#define MAX_THROWING_POWER 120
#define PLAY_IN_LOOP -1

#define BASE_PATH "/var/TPworms/resources/"

#define MUSIC_PATH BASE_PATH "music/AdhesiveWombat_Night Shade.mp3"
#define THROW_SFX_PATH BASE_PATH  "music/throw_sfx.mp3"
#define EXPLOSION_SFX_PATH BASE_PATH "music/explosion_2_sfx.mp3"
#define EQUIP_SFX_PATH BASE_PATH "music/equip_sfx.mp3"
#define TP_SFX_PATH BASE_PATH "music/tp_3_sfx.mp3"
#define DYNAMITE_SFX_PATH BASE_PATH "music/dynamite_2_sfx.mp3"
#define LAUNCH_SFX_PATH BASE_PATH "music/launch_sfx.mp3"
#define DRAW_AXE_SFX_PATH BASE_PATH "music/draw_axe_sfx.mp3"
#define USE_AXE_SFX_PATH BASE_PATH "music/use_axe_sfx.mp3"
#define FALL_SFX_PATH BASE_PATH "music/fall_sfx.mp3"
#define HEAL_SFX_PATH BASE_PATH "music/heal_sfx.mp3"
#define SG_SFX_PATH BASE_PATH "music/sg_sfx.mp3"


#define WORM_LIFE_FONT_PATH BASE_PATH  "fonts/lazy.ttf"
#define HUD_FONT_PATH BASE_PATH  "fonts/arcadeclassic/ARCADECLASSIC.TTF"
#define BIG_FONT_PATH BASE_PATH  "fonts/higher-jump/higher-jump.ttf"

#define BACKGROUND_PATH BASE_PATH  "images/background.png"
#define WAITING_SCREEN_PATH BASE_PATH  "images/dont_panic.bmp"
#define LOSING_SCREEN_PATH BASE_PATH  "images/Dark_Souls_You_Died_Screen_-_Completely_Black_Screen_0-2_screenshot.png"
#define BEAM_PATH BASE_PATH  "images/grdl8.png"
#define STILL_WORM_PATH BASE_PATH  "images/stillworm.bmp"
#define JUMPING_WORM_PATH BASE_PATH  "images/worm_jump.bmp"
#define WALKING_WORM_PATH BASE_PATH  "images/worm_walk.bmp"
#define SURRENDING_WORM_PATH BASE_PATH  "images/worm_surrender.bmp"
#define TP_WORM_PATH BASE_PATH  "images/worm_tp.bmp"
#define WORM_HITTING_PATH BASE_PATH  "images/worm_hitting.bmp"
#define WORM_DRAWING_AXE_PATH BASE_PATH  "images/draw_axe.bmp"
#define WORM_HOLDING_AXE_PATH BASE_PATH  "images/hold_axe.bmp"
#define WORM_DRAWING_BAZOKA_PATH BASE_PATH  "images/draw_bazoka.bmp"
#define WORM_HOLDING_BAZOKA_PATH BASE_PATH  "images/hold_bazoka.bmp"
#define WORM_DRAWING_RG_PATH BASE_PATH  "images/draw_rg.bmp"
#define WORM_HOLDING_RG_PATH BASE_PATH "images/hold_rg.bmp"
#define WORM_DRAWING_BANANA_PATH BASE_PATH  "images/draw_banana.bmp"
#define WORM_HOLDING_BANANA_PATH BASE_PATH  "images/hold_banana.bmp"
#define WORM_DRAWING_GG_PATH BASE_PATH  "images/draw_gg.bmp"
#define WORM_HOLDING_GG_PATH BASE_PATH  "images/hold_gg.bmp"
#define WORM_DRAWING_MORTAR_PATH BASE_PATH  "images/draw_mortar.bmp"
#define WORM_HOLDING_MORTAR_PATH BASE_PATH  "images/holding_mortar.bmp"
#define WORM_DRAWING_TP_PATH BASE_PATH  "images/drawing_tp.bmp"
#define WORM_HOLDING_TP_PATH BASE_PATH  "images/holding_tp.bmp"
#define WORM_HOLDING_DYNAMITE_PATH BASE_PATH "images/draw_dynamite.bmp" //ajustar con frames
#define WORM_DRAWING_DYNAMITE_PATH BASE_PATH "images/draw_dynamite.bmp"
#define WORM_HOLDING_AIRSTRIKE_PATH BASE_PATH "images/call_airstrike.bmp"
#define WORM_DRAWING_AIRSTRIKE_PATH BASE_PATH "images/drawing_airstrike.bmp"
#define WORM_HOLDING_HG_PATH BASE_PATH "images/holding_hg.bmp"
#define WORM_DRAWING_HG_PATH BASE_PATH "images/drawing_hg.bmp"
#define WWINER_ANIMATION_PATH BASE_PATH  "images/wwinner.bmp"
#define WORM_FLY_ANIMATION_PATH BASE_PATH  "images/worm_fly.bmp"
#define WORM_BACKFLIP_PATH BASE_PATH "images/worm_backflip.bmp"


#define GRAVE_PATH BASE_PATH  "images/grave1.bmp"
#define WATER_PATH_00 BASE_PATH "images/water/blue00.bmp"
#define WATER_PATH_01 BASE_PATH "images/water/blue01.bmp"
#define WATER_PATH_02 BASE_PATH "images/water/blue02.bmp"
#define WATER_PATH_03 BASE_PATH "images/water/blue03.bmp"
#define WATER_PATH_04 BASE_PATH "images/water/blue04.bmp"
#define WATER_PATH_05 BASE_PATH "images/water/blue05.bmp"
#define WATER_PATH_06 BASE_PATH "images/water/blue06.bmp"
#define WATER_PATH_07 BASE_PATH "images/water/blue07.bmp"
#define WATER_PATH_08 BASE_PATH "images/water/blue08.bmp"
#define WATER_PATH_09 BASE_PATH "images/water/blue09.bmp"
#define WATER_PATH_10 BASE_PATH "images/water/blue10.bmp"
#define WATER_PATH_11 BASE_PATH "images/water/blue11.bmp"

#define CURR_WORM_PATH BASE_PATH "images/currentWormIndicator.bmp"
#define BAZOOKA_ICON_PATH BASE_PATH "images/icons/rocket.bmp"
#define GGRENADE_ICON_PATH BASE_PATH  "images/icons/gg.bmp"
#define BAT_ICON_PATH BASE_PATH  "images/icons/axe.bmp"
#define TP_ICON_PATH BASE_PATH  "images/icons/tp.bmp"
#define MORTAR_ICON_PATH BASE_PATH "images/icons/mortar.bmp"
#define RGRENADE_ICON_PATH BASE_PATH  "images/icons/rg.bmp"
#define BANANA_ICON_PATH BASE_PATH  "images/icons/banana.bmp"
#define SAINT_GRANADE_ICON_PATH BASE_PATH  "images/icons/hg.bmp"
#define DYNAMITE_ICON_PATH BASE_PATH  "images/icons/dynamite.bmp"
#define AIR_STRIKE_ICON_PATH BASE_PATH  "images/icons/airstrike.bmp"




#define CLOCK_PATH BASE_PATH  "images/clockSpriteSheet.png"
#define AIM_PATH BASE_PATH  "images/aim_cursor.bmp"


#define BACKGROUND_00_PATH  BASE_PATH  "images/scenarios/scenario0.png"
#define BACKGROUND_01_PATH  BASE_PATH  "images/scenarios/scenario1.png"
#define BACKGROUND_02_PATH  BASE_PATH  "images/scenarios/scenario2.png"
#define BACKGROUND_03_PATH  BASE_PATH  "images/scenarios/scenario3.png"
#define BACKGROUND_04_PATH  BASE_PATH  "images/scenarios/scenario4.png"
#define BACKGROUND_05_PATH  BASE_PATH "images/scenarios/scenario5.png"

#define ROCKET_PATH BASE_PATH  "images/rocket.bmp"
#define EXPLOSION_PATH BASE_PATH  "images/explosion3.bmp"

#define MORTAR_PROJECTILE_PATH BASE_PATH "images/morter_projectile.bmp"
#define PERDIGON_PROJECTILE_PATH BASE_PATH "images/perdigon.bmp"
#define AIRSTRIKE_PROJECTILE_PATH BASE_PATH "images/airstrike_projectile.bmp"
#define DYNAMITE_PROJECTILE_PATH BASE_PATH "images/dynamite_projectile.bmp"
#define HG_PROJECTILE_PATH BASE_PATH "images/hgrenade.bmp"
#define FALLING_BOX_PATH BASE_PATH  "images/boxSprites/falling_box.bmp"
#define GLOWING_BOX_PATH BASE_PATH "images/boxSprites/glowing_box.bmp"
#define BOX_OPENING_PATH BASE_PATH "images/explosion.bmp"

#include "../client_src/client_error.h"

GameView::GameView(std::shared_ptr<InfoStruct> infoStruct) :
		client(infoStruct),
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
		wormsFont(HUD_FONT_PATH, 26), hudFont(HUD_FONT_PATH, 42), toolBarFont(WORM_LIFE_FONT_PATH, 11), messageFont(BIG_FONT_PATH, 60),
		waitingScreen(renderer, Surface(WAITING_SCREEN_PATH).SetColorKey(true,0)),
		losingScreen(renderer, LOSING_SCREEN_PATH),
		beamSprite(renderer, BEAM_PATH),
		currentWorm(-1, 0, 0, 100, 0.0, 0.0, 1, STANDING, Position(0,0), {}), //-1 para que se sepa que en realidad no hay alguien con turno
		camX(0), camY(0), mouseX(0), mouseY(0), mouseHandler(camX, camY) {

	this->not_closed = true;
	this->rocketAngle = 45.0f;
	sound.SetVolume(MUSIC_VOLUME);

	client.start();
	std::shared_ptr<GameMap> gameMap = std::dynamic_pointer_cast<GameMap>(client.getGameStatus());

	this->team = gameMap->getTeam();
	this->nteams = gameMap->getNumberTeams();

	//rocketSPrites.push_back(/*textura de la explosion*/);
	
	recievedWorms = gameMap->getWorms();
	//loadWorms(recievedWorms);
	
	std::vector<BeamDTO> beams = gameMap->getBeams();
	loadBeams(beams);


	rocketSprites.push_back(Texture(renderer, Surface(ROCKET_PATH).SetColorKey(true,0)));
		rocketSprites.push_back(Texture(renderer, Surface(EXPLOSION_PATH).SetColorKey(true,0)));
		//le paso algo que pueda ser transparente si se agarra la porcion correcta para que se pueda hacer que desaparezca
		rocketSprites.push_back(Texture(renderer, Surface(EXPLOSION_PATH).SetColorKey(true,0)));
		rocketSprites.push_back(Texture(renderer, Surface(RGRENADE_ICON_PATH).SetColorKey(true,0)));
		rocketSprites.push_back(Texture(renderer, Surface(BANANA_ICON_PATH).SetColorKey(true,0)));
		rocketSprites.push_back(Texture(renderer, Surface(MORTAR_PROJECTILE_PATH).SetColorKey(true,0)));
		rocketSprites.push_back(Texture(renderer, Surface(GGRENADE_ICON_PATH).SetColorKey(true,0)));
		rocketSprites.push_back(Texture(renderer, Surface(PERDIGON_PROJECTILE_PATH).SetColorKey(true,0)));
		rocketSprites.push_back(Texture(renderer, Surface(DYNAMITE_PROJECTILE_PATH).SetColorKey(true,0)));
		rocketSprites.push_back(Texture(renderer, Surface(AIRSTRIKE_PROJECTILE_PATH).SetColorKey(true,0)));
		rocketSprites.push_back(Texture(renderer, Surface(HG_PROJECTILE_PATH).SetColorKey(true,0)));


	boxSprites.push_back(Texture(renderer, Surface(FALLING_BOX_PATH).SetColorKey(true,0)));
		boxSprites.push_back(Texture(renderer, Surface(GLOWING_BOX_PATH).SetColorKey(true,0)));
		boxSprites.push_back(Texture(renderer, Surface(GLOWING_BOX_PATH).SetColorKey(true,0)));//para cuando no muestra
		boxSprites.push_back(Texture(renderer, Surface(EXPLOSION_PATH).SetColorKey(true,0)));
		boxSprites.push_back(Texture(renderer, Surface(BOX_OPENING_PATH).SetColorKey(true,0)));


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
		dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_DRAWING_BANANA_PATH).SetColorKey(true, 0)));
		dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_HOLDING_BANANA_PATH).SetColorKey(true, 0)));
		dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_DRAWING_GG_PATH).SetColorKey(true, 0)));
		dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_HOLDING_GG_PATH).SetColorKey(true, 0)));
		dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_DRAWING_MORTAR_PATH).SetColorKey(true, 0)));
		dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_HOLDING_MORTAR_PATH).SetColorKey(true, 0)));
		dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_DRAWING_TP_PATH).SetColorKey(true, 0)));
		dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_HOLDING_TP_PATH).SetColorKey(true, 0)));
		dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_DRAWING_DYNAMITE_PATH).SetColorKey(true, 0)));
		dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_HOLDING_DYNAMITE_PATH).SetColorKey(true, 0)));
		dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_DRAWING_AIRSTRIKE_PATH).SetColorKey(true, 0)));
		dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_HOLDING_AIRSTRIKE_PATH).SetColorKey(true, 0)));
		dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_DRAWING_HG_PATH).SetColorKey(true, 0)));
		dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_HOLDING_HG_PATH).SetColorKey(true, 0)));
		dynamicSpriteSheets.push_back(Texture(renderer, Surface(WWINER_ANIMATION_PATH).SetColorKey(true, 0)));
		dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_FLY_ANIMATION_PATH).SetColorKey(true, 0)));
		dynamicSpriteSheets.push_back(Texture(renderer, Surface(WORM_BACKFLIP_PATH).SetColorKey(true, 0)));

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
		hudTextures.push_back(Texture(renderer, Surface(DYNAMITE_ICON_PATH).SetColorKey(true, 0)));
		hudTextures.push_back(Texture(renderer, Surface(AIR_STRIKE_ICON_PATH).SetColorKey(true, 0)));
		hudTextures.push_back(Texture(renderer, Surface(SAINT_GRANADE_ICON_PATH).SetColorKey(true, 0)));
		hudTextures.push_back(Texture(renderer, Surface(CLOCK_PATH).SetColorKey(true, 0)));
		hudTextures.push_back(Texture(renderer, Surface(AIM_PATH).SetColorKey(true, 0)));

	sfx.push_back(Chunk(THROW_SFX_PATH));
		sfx.push_back(Chunk(EXPLOSION_SFX_PATH));
		sfx.push_back(Chunk(EQUIP_SFX_PATH));
		sfx.push_back(Chunk(TP_SFX_PATH));
		sfx.push_back(Chunk(DYNAMITE_SFX_PATH));
		sfx.push_back(Chunk(LAUNCH_SFX_PATH));
		sfx.push_back(Chunk(DRAW_AXE_SFX_PATH));
		sfx.push_back(Chunk(USE_AXE_SFX_PATH));
		sfx.push_back(Chunk(FALL_SFX_PATH));
		sfx.push_back(Chunk(HEAL_SFX_PATH));
		sfx.push_back(Chunk(SG_SFX_PATH));



	std::string currentMatchBackgroundPath;
	std::string mapName = gameMap->getMapName();

	if (mapName == "dust2"){
		currentMatchBackgroundPath = BACKGROUND_00_PATH;
	} else if (mapName == "medium") {
		currentMatchBackgroundPath = BACKGROUND_01_PATH;
	} else if (mapName == "small") {
		currentMatchBackgroundPath = BACKGROUND_02_PATH;
	} else if (mapName == "test") {
		currentMatchBackgroundPath = BACKGROUND_03_PATH;
	} else if (mapName == "subsuelo de fiuba") {
		currentMatchBackgroundPath = BACKGROUND_04_PATH;
	} else  {
		currentMatchBackgroundPath = BACKGROUND_05_PATH;
	}

	//linea solo para poder sacar las fotos

	backgroundSprites.push_back(Texture(renderer, currentMatchBackgroundPath));


	this->currentWormId = -1;
	this->bombTimer = 5;
	this->inputState = 0;
	this->winnerTeam = -1;
	this->throwPower = 10;
	this->buttonPressing = false;
	volumeOn = true;
}

void GameView::loadBeams(std::vector<BeamDTO>& beams) {
	for (auto &beam: beams) {
		// this->beamViews.push_back(BeamView(beam, beamSprite));
		this->beamViews.emplace_back(beam, beamSprite);
	}
}



void GameView::stop() {
	this->not_closed = false;
}

void GameView::playSound(int sound_id/*, bool playAlways*/) {
	if (sound_id == -1)
		return;
	try {
		int channel = mixer.PlayChannel(-1, sfx[sound_id], 0);
		mixer.SetVolume(channel, SFX_VOLUME * volumeOn);
	} catch (SDL2pp::Exception &e) {
	/*cuando sdl arregle su funcion 
	yo voy a arreglar mi catch*/
	}
}


void GameView::updateEntities(int i) {

	this->currentGameStatus = *std::dynamic_pointer_cast<GameDynamic>(client.getGameStatus());
	
	int oldid = this->currentWormId;

	this->recievedWorms = currentGameStatus.getWorms();

	this->currentWormId = currentGameStatus.getWormPlayingID();
	if (oldid != currentWormId) {
		inputState = 0;
		buttonPressing = false;
		throwPower = 10;
		//SDL_ShowCursor(SDL_ENABLE);
		if (oldid != -1) { //si se termino el turno
			wormViews.at(oldid).toDefault(0);
		}
	}


	bool anyAlive = false;
	for (auto it = recievedWorms.begin(); it != recievedWorms.end(); it++) {
		anyAlive |= (it->second.isAlive());

		if (it->second.getY() < 1.5 && it->second.getVelY() < -0.1)
			playSound(FALL_SFX);

		if (it->second.getId() == this->currentWormId)
			this->currentWorm = it->second;
		if (wormViews.find(it->first) != wormViews.end())
			continue;
		wormViews.emplace(it->second.getId(),
			WormView(it->second, dynamicSpriteSheets, wormsFont));
	}
	//bool anyAlive = false;
	//for (auto &worm : recievedWorms) {
	//	this->wormViews.at(worm.getId()).update(worm, i);
	//	if (worm.getId() == this->currentWormId) {
	//		this->currentWorm = worm;
	//	}
	//	if (worm.isAlive())
	//		anyAlive = true;
	//}

	if (oldid != currentWormId && currentWormId != -1) {
		camX = currentWorm.getX() * m_to_pix_x - WINDOW_WIDTH / 2;
		camY = currentWorm.getY() * m_to_pix_y + WINDOW_HEIGHT - WINDOW_HEIGHT / 2;
	} else {
		focusCam();
	}

	this->winnerTeam = currentGameStatus.getWinnerTeam();
	if (not anyAlive)
		winnerTeam = -3;

	/*
	aca deberia por cada box/cohete recibido, verificar si esta en mis cohetes, si esta
	no hago nada porque ya voy a actualizar en draw, si no esta lo agrego asi empiezo
	a dibujarlo, no tengo que preocuparme por los que se sacaron esto tambien lo miro
	a medida que actualizo
	*/
	
	this->recievedProjectiles = currentGameStatus.getExplosives();
	for (auto it = recievedProjectiles.begin(); it != recievedProjectiles.end(); it++) {
		if (projectileViews.find(it->first) != projectileViews.end())
			continue;
		projectileViews.emplace(
			it->second.getID(),
			ProjectileView(it->second, rocketSprites)
		);
		int type = it->second.getType();
		if (type == GREEN_GRENADE || type == RED_GRENADE || type == BANANA || type == HOLY_GRENADE)
			playSound(THROW_SFX);
		else if (type == DYNAMITE)
			playSound(DYNAMITE_SFX);
		else if (type == BAZOOKA || type == MORTAR || type == AIR_ATTACK)
			playSound(LAUNCH_SFX);

	}

	this->recievedBoxes = currentGameStatus.getSupplyBox();
	for (auto it = recievedBoxes.begin(); it != recievedBoxes.end(); it++) {
		if (boxViews.find(it->first) != boxViews.end())
			continue;
		boxViews.emplace(
			it->second.getID(),
			SupplyBoxView(it->second, boxSprites)
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
	//for (auto it = wormViews.begin(); it != wormViews.end(); it++) {
	//	//confirmar que esto esta trabajando inplace y no hace copia
	//	it->second.display(i, this->renderer, camX, camY, mouseX, mouseY);
	//}

	for (auto it = wormViews.begin(); it != wormViews.end(); it++) {
		if (recievedWorms.find(it->first) != recievedWorms.end()) {
			it->second.update(recievedWorms.at(it->first), i);
		} else {
			it->second.die();
		}
		it->second.display(i, renderer, camX, camY, mouseX, mouseY);
	}
}

void GameView::drawProjectiles(int i) {
	/*
	por cada wormView busco si esta en los recibidos. si esta lo actualizo usando justamente
	su nueva intancia. si no esta es porque choco y por ende tengo que indicarle que explote
	*/
	
	for (auto it = projectileViews.begin(); it != projectileViews.end();) {
		if (recievedProjectiles.find(it->first) != recievedProjectiles.end()) {
			it->second.update(recievedProjectiles.at(it->first), i);
		} else {
			playSound(it->second.explode(i));

		}
		it->second.display(i, renderer, camX, camY);
		if (not it->second.isOver()) {
			it++;
		} else {
			it = projectileViews.erase(it);
		}
	}


}

void GameView::drawBoxes(int i) {
	for (auto it = boxViews.begin(); it != boxViews.end();) {
		if (recievedBoxes.find(it->first) != recievedBoxes.end()) {
			it->second.update(recievedBoxes.at(it->first), i);
		} else {
			playSound(it->second.open(i));

		}
		it->second.display(i, renderer, camX, camY);

		if (not it->second.isOver()) {
			it++;
		} else {
			it = boxViews.erase(it);
		}
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

	SDL_Color color{255, 5, 5};

	//vida total de los equipos
	int totalHp = currentGameStatus.getTeamHealth(this->team);

	Texture totalHpText(renderer,
		hudFont.RenderText_Solid("HP " + std::__cxx11::to_string(totalHp),
		color));

	Rect TotalHpPosition(
		WINDOW_WIDTH - 100, WINDOW_HEIGHT - 85, 100, 100);

	renderer.Copy(totalHpText, NullOpt, TotalHpPosition);

	//equipo actual
	std::string teamIndicatorText("team   ");
	teamIndicatorText += ::std::__cxx11::to_string(this->team);

	SDL_Color teamIndicatorcolor;
	switch (team) {
	case 0:
		teamIndicatorcolor = TEAM_COLOR_1;
		break;
	case 1:
		teamIndicatorcolor = TEAM_COLOR_2;
		break;
	case 2:
		teamIndicatorcolor = TEAM_COLOR_3;
		break;
	case 3:
		teamIndicatorcolor = TEAM_COLOR_4;
		break;
	}

	Texture teamIndicator(renderer,
		hudFont.RenderText_Solid(teamIndicatorText,
		teamIndicatorcolor));
	Rect teamIndicatorPosition(WINDOW_WIDTH - 250, WINDOW_HEIGHT - 85 ,130,100);
	renderer.SetDrawColor(0,0,0,150);
	renderer.FillRect(teamIndicatorPosition);
	renderer.Copy(teamIndicator, NullOpt,teamIndicatorPosition);
	
	//lo que este abajo de esto no se grafica entre turnos. bueno para cosas especificos de cada worm
	if (this->currentWormId == -1) {
		return;
	}



	renderer.Copy(
		hudTextures[CURRENT_WORM_INDICATOR_TEXTURE],
		Rect(21, 60 * ((i/4) % 30) + 16, 19, 33),
		Rect(
			this->currentWorm.getX() * m_to_pix_x - camX,
			((this->currentWorm.getY() + 2.5) * m_to_pix_y) + WINDOW_HEIGHT - camY,
			20, 20
			)
		);

	//toolbar
	std::vector<int> weapons = this->currentWorm.getWeapons();
	int verticalMargin = 2;
	int toolBarH = 70;
	int toolBarCellWidth = 70;
	int toolBarCellMargin = 4;

	float keyHintRelativeSize = 0.2;
	float ammoHintRelativeSize = 0.3;

	renderer.SetDrawColor(3,3,3, 255);
	renderer.FillRect(0, 0, 
		2*toolBarCellMargin + (toolBarCellWidth + toolBarCellMargin)*weapons.size(),
		toolBarH + 2 * verticalMargin);

	renderer.SetDrawColor(15,15,15,175);
	std::vector<Texture> keybindingsTexts;

	keybindingsTexts.push_back(Texture(renderer, toolBarFont.RenderText_Solid("R", {255, 255, 255})));
	keybindingsTexts.push_back(Texture(renderer, toolBarFont.RenderText_Solid("T", {255, 255, 255})));
	keybindingsTexts.push_back(Texture(renderer, toolBarFont.RenderText_Solid("Y", {255, 255, 255})));
	keybindingsTexts.push_back(Texture(renderer, toolBarFont.RenderText_Solid("U", {255, 255, 255})));
	keybindingsTexts.push_back(Texture(renderer, toolBarFont.RenderText_Solid("I", {255, 255, 255})));
	keybindingsTexts.push_back(Texture(renderer, toolBarFont.RenderText_Solid("O", {255, 255, 255})));
	keybindingsTexts.push_back(Texture(renderer, toolBarFont.RenderText_Solid("P", {255, 255, 255})));
	keybindingsTexts.push_back(Texture(renderer, toolBarFont.RenderText_Solid("F", {255, 255, 255})));
	keybindingsTexts.push_back(Texture(renderer, toolBarFont.RenderText_Solid("G", {255, 255, 255})));
	keybindingsTexts.push_back(Texture(renderer, toolBarFont.RenderText_Solid("H", {255, 255, 255})));

	for (int i = 0; i < weapons.size(); i++) {
		Rect to(
			i*(toolBarCellWidth + toolBarCellMargin) + toolBarCellMargin,
			verticalMargin,
			toolBarCellWidth,
			toolBarH);
		renderer.Copy(hudTextures[i+1], NullOpt, to);
		if (weapons[i] == 0)
			renderer.FillRect(to);
		if (inputState != 0 && inputState == (i + 1)) {
			renderer.SetDrawColor(255,255,255,240);
			renderer.DrawRect(to);
			renderer.SetDrawColor(15,15,15,175);
		}
		Rect keyhintPosition(
			i*(toolBarCellWidth + toolBarCellMargin) + toolBarCellMargin + (toolBarCellWidth * (1-keyHintRelativeSize)),
			verticalMargin + (toolBarH * (1-keyHintRelativeSize)),
			toolBarCellWidth * keyHintRelativeSize,
			toolBarH * keyHintRelativeSize);

		renderer.Copy(keybindingsTexts[i], NullOpt, keyhintPosition);

		//if (weapons[i] <= 0)
		//	break
		Rect ammoPosition(
			i*(toolBarCellWidth + toolBarCellMargin) + toolBarCellMargin + (toolBarCellWidth * (1-ammoHintRelativeSize)),
			verticalMargin + (verticalMargin),
			toolBarCellWidth * ammoHintRelativeSize,
			toolBarH * ammoHintRelativeSize
		);
		std::string ammoText(weapons[i] <= 0 ? " " : ::std::__cxx11::to_string(weapons[i]));

		Texture ammoIndicator(renderer, hudFont.RenderText_Solid(ammoText, {255,255,255}));
		renderer.Copy(ammoIndicator, NullOpt, ammoPosition);



	}


	renderer.Copy(hudTextures[CLOCK_ICON], Rect(1,1,126,148), Rect(0,WINDOW_HEIGHT-100,100,100));


	SDL_Color timeColor{255, 255, 255};

	Texture timerText(renderer,
		hudFont.RenderText_Solid(std::__cxx11::to_string(bombTimer) + "   sec", timeColor));


	Texture timeLeftText(renderer,
		hudFont.RenderText_Solid(std::__cxx11::to_string(CONFIG.getTurnTime() - currentGameStatus.getTimer()), timeColor));


	renderer.Copy(timerText, NullOpt, Rect(100,WINDOW_HEIGHT-50,50,50));
	renderer.Copy(timeLeftText, NullOpt, Rect(100,WINDOW_HEIGHT- 50 - 50,50,50));


	int aimSize = AIM_SIZE * m_to_pix_x;
	if (inputState == 0) {
		SDL_ShowCursor(SDL_ENABLE);
		return;
	}

	
	SDL_ShowCursor(SDL_DISABLE);
	renderer.Copy(
		hudTextures[AIM_ICON],
		Rect(0,0,39,39),
		Rect(mouseX - (aimSize / 2) , mouseY - (aimSize / 2), aimSize,aimSize)
		);

	//power indicator
	if (inputState != TP_CODE && inputState != AIR_STRIKE_CODE && inputState != BAT_CODE) {
		renderer.SetDrawColor(255,5,5,255);

		int squares_size = 20;
		int separation = 5;
		for (int i = 0; i * (MAX_THROWING_POWER / 10) < throwPower; i ++) {
			renderer.SetDrawColor(i * 255 / 10, (10-i) * 255 / 10, 5, 250);
			renderer.FillRect(Rect(
				WINDOW_WIDTH - (i * (squares_size + separation)) + separation,
				0, squares_size, squares_size
			));
		}
	}
	
	

}

void GameView::drawWinningScreen(int i) {
	renderer.Clear();

	mouseHandler.updateCam();

	renderer.Copy(backgroundSprites[0], NullOpt, NullOpt);

	drawBeams(i);

	for (auto it = wormViews.begin(); it != wormViews.end(); it++) {
		//confirmar que esto esta trabajando inplace y no hace copia
		it->second.notifyWinner(winnerTeam);
		it->second.display(i, this->renderer, camX, camY, mouseX, mouseY);
	}

	drawWater(i);

	Texture msg(renderer,
		hudFont.RenderText_Solid("YOU WON!!",
		{0,0,0}));

	Rect textPosition(
		Point(WINDOW_WIDTH/2, WINDOW_HEIGHT/2) - Point(msg.GetSize() / 2),
		Point(WINDOW_WIDTH/2, WINDOW_HEIGHT/2) + (msg.GetSize() / 2));

	renderer.Copy(msg, NullOpt, textPosition);


	renderer.Present();


}

void GameView::drawLosingScreen(int i) {
	renderer.Clear();
	renderer.SetDrawColor(0,0,0);
	renderer.FillRect(Rect(0,0, WINDOW_WIDTH, WINDOW_HEIGHT));

	std::string msg1;

	if (winnerTeam == -3) {
		msg1 = "Everyone died";
	} else  {
		msg1 = "You Lose. Winner is team " +  std::__cxx11::to_string(winnerTeam);
	}

	Texture msg1Texture(renderer,
		hudFont.RenderText_Solid(msg1,	{255,0,0}));

	Rect textPosition(
		Point(WINDOW_WIDTH/3, WINDOW_HEIGHT*2/3 + 30),
		msg1Texture.GetSize());

	renderer.Copy(msg1Texture, NullOpt, textPosition);

	renderer.Present();
}

void GameView::drawWaitingScreen(int i) {
	renderer.Clear();
	renderer.Copy(waitingScreen, NullOpt, NullOpt);


	Texture dontPanicText(renderer,
	hudFont.RenderText_Solid("dont panic  Waiting for players" ,{255,255,255}));

	Rect textPosition(
		Point(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2) - (dontPanicText.GetSize()/2) , dontPanicText.GetSize());

	renderer.Copy(dontPanicText, NullOpt, textPosition);
	renderer.Present();
}

void GameView::draw(int i) {
	updateEntities(i); 
	if (this->currentGameStatus.getStatus() == WAITING) {
		drawWaitingScreen(i);
		return;
	}

	if (this->winnerTeam == -1 || (nteams == 1 && winnerTeam != -3)) {
		drawGame(i);
		return;
	}

	if ((this->winnerTeam  >= 0 && this->team == this->winnerTeam)) {
		drawWinningScreen(i);
		return;
	}

	drawLosingScreen(i);
}


void GameView::_focusCam(float x, float y) {
	this->camX = x * m_to_pix_x - WINDOW_WIDTH / 2;
	this->camY = y * m_to_pix_y + WINDOW_HEIGHT - WINDOW_HEIGHT / 2;
}

void GameView::focusCam() {
	float x,y;
	if ((currentGameStatus.getExplosives().size() >= 1) && (currentGameStatus.getExplosives().begin()->second.getType() != FRAGMENT)) {
		x = currentGameStatus.getExplosives().begin()->second.getX();
		y = currentGameStatus.getExplosives().begin()->second.getY();
		return _focusCam(x,y);
	}

	for (auto it = recievedBoxes.begin(); it != recievedBoxes.end(); it++)  {
		if (it->second.isFalling()) {
			x = it->second.getX();
			y = it->second.getY();
			return _focusCam(x,y);
		}
	}


	for (auto &worm : recievedWorms) {
		if (worm.second.getVelX() == 0 && worm.second.getVelY() == 0)
			continue;
		x = worm.second.getX();
		y = worm.second.getY();
		return _focusCam(x,y);
	}

}


void GameView::drawGame(int i) {

	if (buttonPressing) {
		this->throwPower++;
		throwPower %= MAX_THROWING_POWER;
	}
	mouseHandler.updateCam();
	//focusCam();

	renderer.Clear();
	renderer.Copy(backgroundSprites[0], NullOpt, NullOpt);
	drawBeams(i);
	drawWorms(i);
	drawProjectiles(i);
	drawBoxes(i);
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
    if (inputState != 0)
    	if (inputState != BAT_CODE)
    		playSound(EQUIP_SFX);
    	else playSound(DRAW_AXE_SFX);

    this->inputState = 0;
}

void GameView::backspaceKeyCase(int i) {
	this->client.execute(std::make_shared<Jump>(Jump(currentWormId, 3)));
	this->wormViews.at(this->currentWormId).backflip(i);

}


void GameView::clickCase(int i, int mouseX, int mouseY) {

	int angle = wormViews.at(currentWormId).shoot(i);
	int dir = (((mouseX + camX) / m_to_pix_x) < this->currentWorm.getX()) ? LEFT_DIR : RIGHT_DIR;
	//tp
	Position pos((mouseX + camX) / m_to_pix_x, ((mouseY + camY) - WINDOW_HEIGHT) / m_to_pix_y);

	if (this->currentWorm.getWeapons()[inputState - 1] == 0) {
		return;
	}
	this->wormViews.at(this->currentWormId).toDefault(i);
	switch (inputState) {
	case BAZOOKA_CODE:
		
		this->client.execute(std::make_shared<LaunchRocket>(LaunchRocket(BAZOOKA, currentWormId, dir, angle, throwPower)));
		return;
	case GGRENADE_CODE:
		this->client.execute(std::make_shared<ThrowGrenade>(ThrowGrenade(GREEN_GRENADE,
			this->currentWormId,
			dir, angle, throwPower, bombTimer)));
		return;
	case BAT_CODE:
		this->wormViews.at(this->currentWormId).hit(i);
		this->client.execute(std::make_shared<HitUpclose>(HitUpclose(this->currentWormId, dir)));
		return;
	case TP_CODE:
		this->wormViews.at(this->currentWormId).tp(i);
		this->client.execute(std::make_shared<RemoteOperated>(RemoteOperated(currentWormId, REMOTE_OPERATED, pos)));		
		playSound(TP_SFX);
		return;
	case MORTAR_CODE:
		this->client.execute(std::make_shared<LaunchRocket>(LaunchRocket(MORTAR, currentWormId, dir, angle, throwPower)));
		return;
	case RGRENADE_CODE:
		this->client.execute(std::make_shared<ThrowGrenade>(ThrowGrenade(RED_GRENADE,
			this->currentWormId,
			dir, angle, throwPower, bombTimer)));
			return;
	case BANANA_CODE:
		this->client.execute(std::make_shared<ThrowGrenade>(ThrowGrenade(BANANA,
			this->currentWormId,
			dir, angle, throwPower, bombTimer)));
		return;
	case DYNAMITE_CODE:
		this->client.execute(std::make_shared<DropDynamite>(DropDynamite(this->currentWormId, dir, bombTimer)));
		return;
	case AIR_STRIKE_CODE:
		this->client.execute(std::make_shared<RemoteOperated>(RemoteOperated(currentWormId, AIR_ATTACK, pos)));		
		return;
	case SAINT_GRENADE_CODE:
		this->client.execute(std::make_shared<ThrowGrenade>(ThrowGrenade(HOLY_GRENADE, this->currentWormId,
			dir, angle, throwPower, bombTimer)));
		return;

	default:
		return;
	}

}

void GameView::processInput(SDL_Event event, int i) {
	if (this->currentWormId == -1 || this->currentWorm.getTeam() != this->team) {
	// if (this->currentWormId == -1) {
		return;
	}
	if (event.type != SDL_MOUSEMOTION && event.type != SDL_MOUSEBUTTONDOWN && event.type != SDL_MOUSEBUTTONUP && event.type != SDL_KEYMAPCHANGED) {
		camX = currentWorm.getX() * m_to_pix_x - WINDOW_WIDTH / 2;
		camY = currentWorm.getY() * m_to_pix_y + WINDOW_HEIGHT- WINDOW_HEIGHT / 2;

	}
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (inputState == 0)
			return;
		buttonPressing = true;

	}

	if (event.type == SDL_MOUSEBUTTONUP) {
		buttonPressing = false;
		clickCase(i, mouseX, mouseY);
		throwPower = 10;
	}
	if (event.type == SDL_MOUSEWHEEL){
		if (event.wheel.y > 0) {
			inputState = (inputState + 1) % 11;
			playSound((inputState != BAT_CODE) ? EQUIP_SFX : DRAW_AXE_SFX);
		} else if( event.wheel.y < 0) {
			inputState--;
			playSound((inputState != BAT_CODE) ? EQUIP_SFX : DRAW_AXE_SFX);
			if (inputState < 0) {
				inputState = 10;
			}
		}
			
		switch (inputState) {
	case 0:
		this->wormViews.at(currentWormId).toDefault(i);
		return;
	case BAZOOKA_CODE:
		this->wormViews.at(currentWormId).drawBazoka(i);
		return;
	case GGRENADE_CODE:
		this->wormViews.at(currentWormId).drawGreenGrenade(i);
		return;
	case BAT_CODE:
		wormViews.at(currentWormId).drawAxe(i);
		return;
	case TP_CODE:
		wormViews.at(currentWormId).drawTp(i);
		return;
	case MORTAR_CODE:
		this->wormViews.at(currentWormId).drawMortar(i);
		return;
	case RGRENADE_CODE:
		this->wormViews.at(currentWormId).drawRedGrenade(i);
		return;
	case BANANA_CODE:
		this->wormViews.at(currentWormId).drawBanana(i);
		return;

	case DYNAMITE_CODE:
		this->wormViews.at(currentWormId).drawDynamite(i);
		return;

	case AIR_STRIKE_CODE:
		this->wormViews.at(currentWormId).drawAirstrike(i);
		return;

	case SAINT_GRENADE_CODE:
		this->wormViews.at(currentWormId).drawSg(i);
		return;

	default:
		return;
	}


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

		case SDLK_0:
			bombTimer = 0;
			break; //no es un bug, es una feature
		case SDLK_1:
			bombTimer = 1;
			break;
		case SDLK_2:
			bombTimer = 2;
			break;
		case SDLK_3:
			bombTimer = 3;
			break;
		case SDLK_4:
			bombTimer = 4;
			break;
		case SDLK_5:
			bombTimer = 5;
			break;

		case SDLK_e:
			this->wormViews.at(currentWormId).toDefault(i);
			inputState = 0;
			break;
		case SDLK_r: //podria ser un mapa pero seria igual de feo en el constructor
			inputState = BAZOOKA_CODE;
			playSound(EQUIP_SFX);
			this->wormViews.at(currentWormId).drawBazoka(i);
			break;
		case SDLK_t:
			inputState = GGRENADE_CODE;
			playSound(EQUIP_SFX);

			this->wormViews.at(currentWormId).drawGreenGrenade(i);
			break;
		case SDLK_y:
			if (this->currentWorm.getWeapons()[BAT_CODE] == 0)
				return;
			inputState = BAT_CODE;
			playSound(DRAW_AXE_SFX);

			wormViews.at(currentWormId).drawAxe(i);
			break;
		case SDLK_u:
			inputState = TP_CODE;
			playSound(EQUIP_SFX);

			wormViews.at(currentWormId).drawTp(i);
			break;
		case SDLK_i:
			inputState = MORTAR_CODE;
			playSound(EQUIP_SFX);

			this->wormViews.at(currentWormId).drawMortar(i);
			break;
		case SDLK_o:
			inputState = RGRENADE_CODE;
			playSound(EQUIP_SFX);

			this->wormViews.at(currentWormId).drawRedGrenade(i);
			break;
		case SDLK_p:
			inputState = BANANA_CODE;
			playSound(EQUIP_SFX);

			this->wormViews.at(currentWormId).drawBanana(i);
			break;

		case SDLK_f:
			inputState = DYNAMITE_CODE;
			playSound(EQUIP_SFX);

			this->wormViews.at(currentWormId).drawDynamite(i);

			break;
		case SDLK_g:
			inputState = AIR_STRIKE_CODE;
			playSound(EQUIP_SFX);
			this->wormViews.at(currentWormId).drawAirstrike(i);

			break;
		case SDLK_h:
			inputState = SAINT_GRENADE_CODE;
			playSound(EQUIP_SFX);
			this->wormViews.at(currentWormId).drawSg(i);
			break;



		case SDLK_z:
			this->client.execute(std::make_shared<Cheats>(Cheats(this->currentWormId, ADD_HEALTH)));
			break;

		case SDLK_x:
			this->client.execute(std::make_shared<Cheats>(Cheats(this->currentWormId, ALL_WEAPONS)));
			break;

		case SDLK_c:
			this->client.execute(std::make_shared<Cheats>(Cheats(this->currentWormId, ALL_INVINCIBLE)));
			break;

		case SDLK_v:
			this->client.execute(std::make_shared<Cheats>(Cheats(this->currentWormId, STOP_TURN)));
			break;

		case SDLK_b:
			this->client.execute(std::make_shared<Cheats>(Cheats(this->currentWormId, RENEW_TURN)));
			break;

		}
	}
}

void GameView::start() {
	mixer.PlayChannel(-1, sound, PLAY_IN_LOOP);

	int i = 0;
	int t1 = SDL_GetTicks();
	//float durationInSeconds;
	try {
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

				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m) {
					this->volumeOn = !(this->volumeOn);
					Mix_Volume(-1, MUSIC_VOLUME * volumeOn);
				}

						 

				processInput(event, i);
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
	} catch (const ClientClosed& e) {
		return;
	} catch (...) {
		std::cout << "Error in smth: " << "unknown" << std::endl;
	}
}

void GameView::join() {
	this->client.kill();
}

GameView::~GameView() {}
