#ifndef ROCKET_VIEW_H
#define ROCKET_VIEW_H

#include <SDL2pp/SDL2pp.hh>
#include "constants.h"
#include "../game_src/weapons_dto.h"

using namespace SDL2pp;
using namespace uiConstants;

class RocketView {
private:
	WeaponDTO rocket;
	std::vector<Texture>& dynamicSpriteSheets;
	std::vector<std::vector<Rect>> frames;
	int startingPoint;
	int currentFramesIndex;
	int defaultFramesIndex;

	void explode();

public:
	RocketView(WeaponDTO& rocket, std::vector<Texture>& dynamicSpriteSheets);
	~RocketView();

	void display(int i, Renderer& renderer, int camX, int camY);
	void update(WeaponDTO other, int i);

};

#endif
