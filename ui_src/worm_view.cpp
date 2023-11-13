#include "worm_view.h"
#include <SDL2pp/SDL2pp.hh>



WormView::WormView(WormDTO& worm, std::vector<Texture>& dynamicSpriteSheets, Font& wormsFont) : 
	worm(worm),
	dynamicSpriteSheets(dynamicSpriteSheets),
	frames{{},{},{},{},{}},
	wormsFont(wormsFont) {
	defaultFramesIndex = STILL_FRAMES;
	currentFramesIndex = STILL_FRAMES;
	startingPoint = 0;
	//looping = true;
	float x, y, w, h;
	
	//frames for still animation
	for (int i = 0; i < 35; i++) {
		x = 19;
		w = 22;
		y = i*(60) + 16;
		h = 26;
		frames[STILL_FRAMES].push_back(Rect(x,y,w,h));
	}


	//frames for jumping animation
	for (int i = 0; i < 10; i++) {
		x = 19;
		w = 22;
		y = i*(60) + 12;
		h = 36;
		frames[JUMPING_FRAMES].push_back(Rect(x,y,w,h));
	}

	//frames for walking animation
	for (int i = 0; i < 15; i++) {
		x = 11;
		w = 28;
		y = i*(60) + 14;
		h = 29;
		frames[WALKING_FRAMES].push_back(Rect((int)x,y,w,h));
	}

	//frames for surrending animation
	for (int i = 0; i < 16; i++) {
		x = 19;
		w = 29;
		y = i * 60 + 7;
		h = 36;
		frames[SURRENDING_FRAMES].push_back(Rect(x,y,w,h));
	}
	

	//frames for dying animation
	for (int i = 0; i < 20; i++) {
		x = 18;
		w = 23;
		y = 60*i + 4;
		h = 29;
		frames[POSTMORTEM_FRAMES].push_back(Rect(x,y,w,h));
	}


	//frames for backflip animation
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

void WormView::surrend() {
	this->defaultFramesIndex = SURRENDING_FRAMES;
}

void WormView::die() {
	if (currentFramesIndex == POSTMORTEM_FRAMES)
		return;
	this->currentFramesIndex = POSTMORTEM_FRAMES;
	this->defaultFramesIndex = POSTMORTEM_FRAMES;
}


void WormView::display(int i, Renderer& renderer, int camX, int camY) {
	size_t currentFrame = (i - startingPoint) / 4;

	if (currentFrame >= this->frames[currentFramesIndex].size()) {
		startingPoint = i;
		currentFramesIndex = defaultFramesIndex;
		currentFrame = 0;
	}
	
	int x = ((worm.getX() - 0.5)  * m_to_pix_x) - camX;
	int y = ((worm.getY() + 0.5) * m_to_pix_y + WINDOW_HEIGHT) - camY;
	renderer.Copy(
		this->dynamicSpriteSheets[currentFramesIndex],
		this->frames[currentFramesIndex][currentFrame],
		Rect(x, y,1*m_to_pix_x, -1*m_to_pix_y),
		0, NullOpt, worm.getDir()
	);

	//grafico la vida
	Texture hp(renderer,
		wormsFont.RenderText_Solid(std::__cxx11::to_string(this->worm.getHealth()),
		SDL_Color{0,0,0}));
	renderer.Copy(
		hp,
		NullOpt,
		Rect(Point(x + 0.5*m_to_pix_x ,y - (.5 * - m_to_pix_y)), hp.GetSize())
	);

}

void WormView::update(WormDTO other, int i) {
	this->worm = other;

	if (!(this->worm.isAlive())) {
		die();
	}

	if (this->worm.getHealth() <= 10)
		surrend();
}

WormView::~WormView() {}