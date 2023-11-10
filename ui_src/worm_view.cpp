#include "worm_view.h"
#include <SDL2pp/SDL2pp.hh>



WormView::WormView(WormDTO& worm, std::vector<Texture>& dynamicSpriteSheets) : 
	worm(worm),
	dynamicSpriteSheets(dynamicSpriteSheets),
	frames{{},{},{}} {
	currentFramesIndex = DEFAULT_FRAMES;
	startingPoint = 0;
	float x, y, w, h;
	

	for (int i = 0; i < 35; i++) {
		x = 19;
		w = 22;
		y = i*(60) + 16;
		h = 26;
		frames[STILL_FRAMES].push_back(Rect(x,y,w,h));
	}

	for (int i = 0; i < 10; i++) {
		x = 19;
		w = 22;
		y = i*(60) + 12;
		h = 36;
		frames[JUMPING_FRAMES].push_back(Rect(x,y,w,h));
	}

	for (int i = 0; i < 15; i++) {
		x = 11+0.5;
		w = 28;
		y = i*(60) + 14;
		h = 29;
		frames[WALKING_FRAMES].push_back(Rect((int)x,y,w,h));
	}
}


void WormView::jump(int i) {
	if (currentFramesIndex == JUMPING_FRAMES)
		return;
	this->startingPoint = i;
	this->currentFramesIndex = JUMPING_FRAMES;
}

void WormView::move(int i) {
	if (currentFramesIndex == WALKING_FRAMES)
		return;

	this->startingPoint = i;
	this->currentFramesIndex = WALKING_FRAMES;
}


void WormView::display(int i, Renderer& renderer, int camX, int camY) {

	size_t currentFrame = (i - startingPoint) / 4;

	if (currentFrame >= this->frames[currentFramesIndex].size()) {
		startingPoint = i;
		currentFramesIndex = DEFAULT_FRAMES;
		currentFrame = 0;
	}
	
	//std::cout << "[" << worm.getId() << "] X: " << this->worm.getPosition().getX() << ", Y: " << this->worm.getPosition().getY();
	renderer.Copy(
		this->dynamicSpriteSheets[currentFramesIndex],
		this->frames[currentFramesIndex][currentFrame], 
		Rect(
			((worm.getX() - 0.5)  * m_to_pix_x) - camX,
			((worm.getY() + 0.5) * m_to_pix_y + WINDOW_HEIGHT) - camY,
			1*m_to_pix_x, -1*m_to_pix_y
			),
		0, NullOpt, worm.getDir()
	);
}

void WormView::update(WormDTO other) {
	this->worm = other;
}

WormView::~WormView() {}