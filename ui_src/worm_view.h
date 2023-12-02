#ifndef WORM_VIEW_H
#define WORM_VIEW_H

#include <vector>
#include <iostream>
#include <SDL2pp/SDL2pp.hh>
#include "constants.h"
#include "../game_src/worm_dto.h"
#include <cmath>

using namespace SDL2pp;
using namespace uiConstants;

class WormView  {
private:
	WormDTO worm;
	std::vector<Texture>& dynamicSpriteSheets;
	std::vector<std::vector<Rect>> frames;
	Font& wormsFont;
	int startingPoint;
	int currentFramesIndex; //indica la tira(fila) de frames que se tiene que usar ahora mismo
	int defaultFramesIndex;
	int angle;

public:
	WormView(WormDTO& worm, std::vector<Texture>& dynamicSpriteSheets, Font& font);
	~WormView();

	//funcion de prueba para testear que no aparezca el segfault
	int shoot(int i);
	void toDefault(int i);
	void drawTp(int i);
	void drawBanana(int i);
	void drawGreenGrenade(int i);
	void drawRedGrenade(int i);
	void drawMortar(int i);
	void drawBazoka(int i);
	void drawAxe(int i);
	void drawDynamite(int i);
	void drawAirstrike(int i);
	void drawSg(int i);
	void jump(int i);
	void move(int i);
	void hit(int i);
	void tp(int i);
	void notifyWinner(int i);

	void surrend();
	void die();
	
	void display(int i, Renderer& renderer, int camX, int camY, int mouseX, int mouseY);
	void update(WormDTO other, int i);
};

#endif
