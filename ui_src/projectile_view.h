#ifndef PROJECTILE_VIEW_H
#define PROJECTILE_VIEW_H

#include <SDL2pp/SDL2pp.hh>
#include "constants.h"
#include "../game_src/explosives_dto.h"

using namespace SDL2pp;
using namespace uiConstants;

class ProjectileView {
private:
	ExplosivesDTO rocket;
	std::vector<Texture>& projectileSpriteSheets;
	std::vector<std::vector<Rect>> frames;
	int startingPoint;
	int currentFramesIndex;
	int defaultFramesIndex;


public:

	
	ProjectileView(ExplosivesDTO projectile, std::vector<Texture>& projectileSpriteSheets);
	~ProjectileView();
	bool isOver();
	void explode(int i);
	void display(int i, Renderer& renderer, int camX, int camY);
	void update(ExplosivesDTO other, int i);

};

#endif
