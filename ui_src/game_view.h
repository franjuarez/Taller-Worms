#ifndef GAME_VIEW_H
#define  GAME_VIEW_H


#include <unordered_map>
#include <math.h>
#include <cmath>
#include "worm_view.h"
#include "projectile_view.h"
#include "supply_box_view.h"
#include "mouse_handler.h"
#include "../game_src/game_dynamic.h"
#include "../client_src/client.h"
#include "../shared_src/protocol.h"
#include "beam_view.h"

using namespace uiConstants;
using namespace SDL2pp;

class GameView {
private:
	//Client stuff
	Client client;
	GameDynamic currentGameStatus;

	//basic SDL stuff
	SDL sdl;
	Window window;
	SDLTTF sdlttf;
	Mixer mixer;
	Renderer renderer;
	
	//recursos
	Font wormsFont;
	Font hudFont;
	Font toolBarFont;
	Font messageFont;
	Chunk sound;
	std::vector<Chunk> sfx;
	std::vector<Texture> backgroundSprites;
	Texture waitingScreen;
	Texture beamSprite;
	Texture losingScreen;
	std::vector<Texture> rocketSprites;
	std::vector<Texture> boxSprites;	
	std::vector<Texture> dynamicSpriteSheets;
	std::vector<Texture> waterSprites;
	std::vector<BeamView> beamViews;
	WormDTO currentWorm;
	std::vector<Texture> hudTextures;
	int team;
	float rocketAngle;
	bool not_closed;
	int camX;
	int camY;
	int mouseX;
	int mouseY;
	bool volumeOn;
	MouseHandler mouseHandler;

	std::unordered_map<int, WormView> wormViews;
	std::unordered_map<int, ProjectileView> projectileViews;
	std::unordered_map<int, SupplyBoxView> boxViews;
	std::unordered_map<int, ExplosivesDTO> recievedProjectiles;
	std::unordered_map<int, SupplyBoxDTO> recievedBoxes;
	std::unordered_map<int, WormDTO> recievedWorms;

	

	int currentWormId;

	int inputState;
	int bombTimer;
	int winnerTeam;
	int nteams;
	int throwPower;
	bool buttonPressing;

	void playSound(int sound_id);
	void updateEntities(int i);
	//void loadWorms(std::vector<WormDTO>& recievedWorms);
	void loadBeams(std::vector<BeamDTO>& beams);
	void draw(int i);
	void drawWaitingScreen(int i);
	void drawWinningScreen(int i);
	void drawLosingScreen(int i);
	void drawGame(int i);
	void drawBeams(int i);
	void drawWorms(int i);
	void drawProjectiles(int i);
	void drawBoxes(int i);
	void drawWater(int i);
	void drawHud(int i);
	void returnKeyCase(int i);
	void moveCase(int i, int dir);
	void backspaceKeyCase(int i);
	void clickCase(int i, int x, int y);

	void processInput(SDL_Event event, int i);
	void _focusCam(float x, float y);
	void focusCam();

public:
	GameView(std::shared_ptr<InfoStruct> infoStruct);
	~GameView();

	void start();
	void stop();
	void join();
};


#endif
