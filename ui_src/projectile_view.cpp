#include "projectile_view.h"
#include <SDL2pp/SDL2pp.hh>

ProjectileView::ProjectileView(WeaponDTO& rocket, std::vector<Texture>& projectileSpriteSheet) :
rocket(rocket), projectileSpriteSheets(projectileSpriteSheet), frames{{},{},{}} {
	startingPoint = 0;

	frames[ROCKET_FRAMES].push_back(Rect(19,13,22,34));

	int x = 19;
	int y;
	int w = 21;
	int h = 26;
	for (int i = 0; i < 21; i++) {
		y = 60 * i + 18;
		frames[EXPLOSION_FRAMES].push_back(Rect(x,y,w,h));
	}

	frames[POST_EXPLOSION_FRAMES].push_back(Rect(0,0,1,1));

}

ProjectileView::~ProjectileView() {}

void ProjectileView::explode(int i) {
	if (currentFramesIndex != ROCKET_FRAMES)
		return;
	this->startingPoint = i
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

	int x = ((rocket.getX())  * m_to_pix_x) - camX;
	int y = ((rocket.getY()) * m_to_pix_y + WINDOW_HEIGHT) - camY;
	double angle = -(atan(rocket.getVelY() / rocket.getVelX()) * (180.0 / M_PI)); 
	angle += 90;

	renderer.Copy(
		this->projectileSpriteSheets[currentFramesIndex],
		this->frames[currentFramesIndex][currentFrame], 
		Rect(x, y,0.5*m_to_pix_x, 0.5*m_to_pix_y),
		angle, Point(0, 0), false
	);
}

void ProjectileView::update(WeaponDTO other, int i) {
	this->rocket = other;
	if (other.getBoomed())
		explode();

}



