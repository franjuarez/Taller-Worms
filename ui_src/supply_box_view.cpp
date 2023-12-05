#include "supply_box_view.h"
#include "../game_src/constants_game.h"
#include <SDL2pp/SDL2pp.hh>

SupplyBoxView::SupplyBoxView(SupplyBoxDTO box, std::vector<Texture>& boxSpriteSheets) :
		box(box), boxSpriteSheets(boxSpriteSheets), frames{5} {
	startingPoint = 0;
	currentFramesIndex = defaultFramesIndex = GLOWING_BOX_FRAMES;

	int x,y,w,h;
	x = 12;
	w = 33;
	h = 26;
	for (int i = 0; i < 14; i++) {
		y = i * 60 + 17;
		frames[GLOWING_BOX_FRAMES].push_back(Rect(x,y,w,h));
	}

	for (int i = 12; i >= 0; i--) {
		y = i * 60 + 17;
		frames[GLOWING_BOX_FRAMES].push_back(Rect(x,y,w,h));
	}


	x = 19;
	w = 21;
	h = 27;
	//for explosion3.bmp
	for (int i = 0; i < 30; i++) {
		y = 60 * i + 17;
		frames[EXPLODING_BOX_FRAMES].push_back(Rect(x,y,w,h));
	}

	x = 0;
	w = 58;
	h = 58;
	for (int i = 0; i < 9; i++) {
		y = 60 * (i/2);
		frames[OPENING_FRAMES].push_back(Rect(x,y,w,h));
	}

	frames[NOT_SHOWING_BOX_FRAMES].push_back(Rect(0,0,2,2));
}


void SupplyBoxView::display(int i, Renderer& renderer, int camX, int camY) {

	int frame = (i - startingPoint)/2;
	if (frame >= this->frames[currentFramesIndex].size()) {
		startingPoint = i;
		currentFramesIndex = defaultFramesIndex;
		frame = 0;
	}

	float drawSize = (currentFramesIndex != EXPLODING_BOX_FRAMES && currentFramesIndex != OPENING_FRAMES) ? 1.5 : 3.5;


	renderer.Copy(
		boxSpriteSheets[currentFramesIndex],
		frames[currentFramesIndex][frame],
		Rect(
			(box.getX() - drawSize / 2) * m_to_pix_x - camX,
			(box.getY() + drawSize / 2) * m_to_pix_y + WINDOW_HEIGHT - camY,
			drawSize * m_to_pix_x,
			drawSize * -m_to_pix_y
		)
	);
}

bool SupplyBoxView::isOver() {
	return this->currentFramesIndex == NOT_SHOWING_BOX_FRAMES;
}

int SupplyBoxView::open(int i) {
	if (currentFramesIndex != GLOWING_BOX_FRAMES)
		return -1;
	if (box.getContent() == TRAP_SUPPLY) {
		startingPoint = i;
		currentFramesIndex = EXPLODING_BOX_FRAMES;
	} else {
		startingPoint = i;
		currentFramesIndex = OPENING_FRAMES;
	}
	
	defaultFramesIndex = NOT_SHOWING_BOX_FRAMES;

	if (this->box.getContent() == TRAP_SUPPLY)
		return EXPLOSION_SFX;
	if (this->box.getContent() == HEALTH_SUPPLY)
		return HEAL_SFX;
	return EQUIP_SFX;

}


void  SupplyBoxView::update(SupplyBoxDTO other, int i) {
	this->box = other;
}

SupplyBoxView::~SupplyBoxView() {}