#include "projectile_view.h"
#include "../game_src/constants_game.h"
#include <SDL2pp/SDL2pp.hh>

ProjectileView::ProjectileView(ExplosivesDTO rocket, std::vector<Texture>& projectileSpriteSheet) :
rocket(rocket), projectileSpriteSheets(projectileSpriteSheet), frames{11} {
	startingPoint = 0;


	switch(rocket.getType()) {
	case BAZOOKA:
		currentFramesIndex = defaultFramesIndex = ROCKET_FRAMES;
		break;
	case RED_GRENADE:
		currentFramesIndex = defaultFramesIndex = RED_GRENADE_FRAMES;
		break;
	case BANANA:
		currentFramesIndex = defaultFramesIndex = BANANA_FRAMES;
		break;
	case MORTAR:
		currentFramesIndex = defaultFramesIndex = MORTAR_FRAMES;
		break;
	case GREEN_GRENADE:
		currentFramesIndex = defaultFramesIndex = GREEN_GRENADE_FRAMES;
		break;
	case AIR_ATTACK:
		currentFramesIndex = defaultFramesIndex = AIR_STRIKE_FRAMES;
		break;
	case DYNAMITE:
		currentFramesIndex = defaultFramesIndex = DYNAMITE_FRAMES;
		break;
	case HOLY_GRENADE:
		currentFramesIndex = defaultFramesIndex = HG_FRAMES;
		break;

	default:
		currentFramesIndex = defaultFramesIndex = PERDIGON_FRAMES;
		break;
	}



	frames[ROCKET_FRAMES].push_back(Rect(19,13,22,34));

	int x = 19;
	int y;
	int w = 21;
	int h = 27;
	//for explosion3.bmp
	for (int i = 0; i < 30; i++) {
		y = 60 * i + 17;
		frames[EXPLOSION_FRAMES].push_back(Rect(x,y,w,h));
	}
	frames[POST_EXPLOSION_FRAMES].push_back(Rect(0,0,1,1));

	frames[RED_GRENADE_FRAMES].push_back(Rect(7,4,14,24));

	frames[BANANA_FRAMES].push_back(Rect(7,4,14,24));

	frames[MORTAR_FRAMES].push_back(Rect(23,17,14,24));

	frames[GREEN_GRENADE_FRAMES].push_back(Rect(7,4,14,24));	

	frames[PERDIGON_FRAMES].push_back(Rect(23,16,13,25));

	frames[DYNAMITE_FRAMES].push_back(Rect(15,14,27,25));

	frames[AIR_STRIKE_FRAMES].push_back(Rect(15,17,25,24));

	frames[HG_FRAMES].push_back(Rect(19,12,20,28));

}

ProjectileView::~ProjectileView() {}

bool ProjectileView::isOver() {
	return currentFramesIndex == POST_EXPLOSION_FRAMES;
}

void ProjectileView::explode(int i) {
	if (currentFramesIndex != ROCKET_FRAMES && currentFramesIndex < RED_GRENADE_FRAMES)
		return;
	this->startingPoint = i;
	this->currentFramesIndex = EXPLOSION_FRAMES;
	this->defaultFramesIndex = POST_EXPLOSION_FRAMES;
}

void ProjectileView::display(int i, Renderer& renderer, int camX, int camY) {
	size_t currentFrame = (i - startingPoint) / 4;
	if (currentFrame >= this->frames[currentFramesIndex].size()) {
		startingPoint = i;
		currentFramesIndex = defaultFramesIndex;
		currentFrame = 0;
	}


	float rocketSize = currentFramesIndex == EXPLOSION_FRAMES ? 4 : 0.5;

	int x = ((rocket.getX() - rocketSize/2)  * m_to_pix_x) - camX;
	int y = ((rocket.getY() + rocketSize/2) * m_to_pix_y + WINDOW_HEIGHT) - camY;



	double angle = 0;
	if (rocket.getType() == RED_GRENADE ||	rocket.getType() == GREEN_GRENADE) {

		angle = i % 180;

	}else if (rocket.getType() == BANANA || rocket.getType() == HOLY_GRENADE) {
		angle = i*6 % 360;
	} else if (rocket.getType() == DYNAMITE) {
		angle = 0;

	} else /*if (rocket.getType() == BAZOOKA)*/ {
		angle = -(atan(rocket.getVelY() / rocket.getVelX()) * (180.0 / M_PI)); 
		angle += (rocket.getVelX() < 0) ? -90 : 90;
	}

	if ((abs(this->rocket.getVelX()) < 0.1 && abs(this->rocket.getVelY()) < 0.1)  || currentFramesIndex == EXPLOSION_FRAMES) {
		angle = 0;
	}
	

	Texture& texture(this->projectileSpriteSheets[currentFramesIndex]);
	//si esto es distinto de 0 rompe aca
	Rect origin(this->frames.at(currentFramesIndex).at(currentFrame));
	Rect destiny(x, y,rocketSize*m_to_pix_x, -rocketSize*m_to_pix_y);


	renderer.Copy(texture, origin, destiny, angle, Point(destiny.GetW()/2,destiny.GetH()/2), false);
	//renderer.Copy(
	//	this->projectileSpriteSheets[currentFramesIndex],
	//	this->frames[currentFramesIndex][currentFrame], 
	//	Rect(x, y,0.5*m_to_pix_x, 0.5*m_to_pix_y),
	//	angle, Point(0, 0), false
	//);
}

void ProjectileView::update(ExplosivesDTO other, int i) {
	this->rocket = other;

}



