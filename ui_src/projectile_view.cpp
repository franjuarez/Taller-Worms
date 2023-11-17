#include "projectile_view.h"
#include <SDL2pp/SDL2pp.hh>

ProjectileView::ProjectileView(ExplosivesDTO rocket, std::vector<Texture>& projectileSpriteSheet) :
rocket(rocket), projectileSpriteSheets(projectileSpriteSheet), frames{{},{},{}} {
	startingPoint = 0;
	currentFramesIndex = defaultFramesIndex = ROCKET_FRAMES;
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


}

ProjectileView::~ProjectileView() {}

void ProjectileView::explode(int i) {
	if (currentFramesIndex != ROCKET_FRAMES)
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

	float rocketSize = currentFramesIndex == EXPLOSION_FRAMES ? 2 : 0.5;

	int x = ((rocket.getX() - rocketSize/2)  * m_to_pix_x) - camX;
	int y = ((rocket.getY() + rocketSize/2) * m_to_pix_y + WINDOW_HEIGHT) - camY;



	double angle;
	angle = -(atan(rocket.getVelY() / rocket.getVelX()) * (180.0 / M_PI)); 
	angle += (rocket.getVelX() < 0) ? -90 : 90;


	if (currentFramesIndex == EXPLOSION_FRAMES) {
		angle = 0;
	}
	
	Texture& texture(this->projectileSpriteSheets[currentFramesIndex]);
	//si esto es distinto de 0 rompe aca
	Rect origin(this->frames.at(currentFramesIndex).at(currentFrame));
	Rect destiny(x, y,rocketSize*m_to_pix_x, -rocketSize*m_to_pix_y);


	renderer.Copy(texture, origin, destiny, angle, Point(0,0), false);
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



