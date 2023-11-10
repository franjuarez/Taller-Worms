#ifndef GAME_VIEW_H
#define  GAME_VIEW_H


#include <unordered_map>
#include <math.h>
#include <cmath>
#include "worm_view.h"
#include "mouse_handler.h"
#include "../game_src/game_dynamic.h"
#include "../client_src/client.h"
#include "beam_view.h"

using namespace uiConstants;
using namespace SDL2pp;

class GameView {
private:
	//Client stuff
	Client client;

	//basic SDL stuff
	SDL sdl;
	Window window;
	Mixer mixer;
	Renderer renderer;

	

	//recursos
	Chunk sound;
	Texture backgroundSprite;
	Texture beamSprite;
	Texture rocketSprite;
	
	std::vector<Texture> dynamicSpriteSheets;
	std::vector<BeamView> beamViews;
	std::unordered_map<int, WormView> wormViews;
	

	int camX;
	int camY;
	MouseHandler mouseHandler;
	std::vector<ProjectileDTO> proy;
	int currentWormId;
	int lookingDir;

	void updateEntities();
	void loadWorms(std::vector<WormDTO>& recievedWorms);
	void loadBeams(std::vector<BeamDTO>& beams);
	void draw(int i);
	void returnKeyCase(int i);
	void moveCase(int i);
	void mouseMovementCase(int x, int y);

public:
	GameView(const std::string& hostname, const std::string& servname);
	~GameView();

	void start();
	void join();
};


#endif
