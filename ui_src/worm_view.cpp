#include "worm_view.h"
#include <SDL2pp/SDL2pp.hh>



WormView::WormView(WormDTO& worm, std::vector<Texture>& dynamicSpriteSheets) : 
	worm(worm),
	dynamicSpriteSheets(dynamicSpriteSheets),
	frames{{},{}} {
	currentFramesIndex = DEFAULT_FRAMES;
	startingPoint = 0;
	int x, y, w, h;
	

	for (int i = 0; i < 35; i++) {
		x = 19;
		w = 22;
		y = i*(60) + 16;
		h = 26;
		//stillWormFrames.emplace_back(x,y,w,h);
		frames[STILL_FRAMES].push_back(Rect(x,y,w,h));
	}

	for (int i = 0; i < 10; i++) {
		x = 19;
		y = i*(60) + 12;
		w = 22;
		h = 36;
		frames[JUMPING_FRAMES].push_back(Rect(x,y,w,h));
		//jumpingWormFrames.emplace_back(x,y,w,h);
	}

	//std::cout << "=====prueba en constructor=====" << std::endl;
	//std::cout << this->frames[STILL_FRAMES].at(0) << std::endl;
	////std::cout << this->stillWormFrames.at(0) << std::endl;
	////std::cout << this->currentFrames->at(0) << std::endl;
	//std::cout << "===fin prueba en constructor===" << std::endl;
}

//void WormView::testearAcceso() {
//	std::cout << "=======prueba en funcion=======" << std::endl;
//	std::cout << this->frames[STILL_FRAMES].at(0) << std::endl;
//	std::cout << this->frames[currentFramesIndex].at(0) << std::endl;
//	//std::cout << this->stillWormFrames.at(0) << std::endl;
//	//std::cout << this->currentFrames->at(0) << std::endl;
//	std::cout << "=====fin prueba en funcion=====" << std::endl;
//}

void WormView::jump(int i) {
	this->currentFramesIndex = JUMPING_FRAMES;
	this->startingPoint = i;
}


void WormView::display(int i, Renderer& renderer, int camX, int camY) {
	//testearAcceso();
	size_t currentFrame = (i - startingPoint) / 4;

	if (currentFrame >= this->frames[currentFramesIndex].size()) {
		startingPoint = i;
		currentFramesIndex = DEFAULT_FRAMES;
		currentFrame = 0;
	}

	//std::cout << this->frames[this->currentFramesIndex][currentFrame] << std::endl;
	renderer.Copy(
		this->dynamicSpriteSheets[currentFramesIndex], 
		this->frames[currentFramesIndex][currentFrame], 
		Rect(
			(worm.getPosition().getX() * m_to_pix_x) - camX,
			(worm.getPosition().getY() * m_to_pix_y + WINDOW_HEIGHT) - camY,
			1.5*m_to_pix_x, -1.5*m_to_pix_y
			)
	);
}

void WormView::update(WormDTO other) {
	this->worm = other;
}

WormView::~WormView() {}