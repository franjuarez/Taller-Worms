#include "supply_box_view.h"
#include "../game_src/constants_game.h"
#include <SDL2pp/SDL2pp.hh>

SupplyBoxView::SupplyBoxView(SupplyBoxDTO box, std::vector<Texture>& boxSpriteSheets) :
		box(box), boxSpriteSheets(boxSpriteSheets), frames{3} {
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


	frames[NOT_SHOWING_BOX_FRAMES].push_back(Rect(0,0,2,2));

}


void SupplyBoxView::display(int i, Renderer& renderer, int camX, int camY) {

	int frame = (i / 2) - startingPoint;
	if (frame >= this->frames[currentFramesIndex].size()) {
		startingPoint = i;
		currentFramesIndex = defaultFramesIndex;
		frame = 0;
	}


	renderer.Copy(
		boxSpriteSheets[currentFramesIndex],
		frames[currentFramesIndex][frame],
		Rect(
			(box.getX() - 1.5 / 2) * m_to_pix_x - camX,
			(box.getY() + 1.5 / 2)* m_to_pix_y + WINDOW_HEIGHT - camY,
			1.5 * m_to_pix_x,
			1.5 * -m_to_pix_y
		)
	);
}


void SupplyBoxView::open(int i) {
	currentFramesIndex = defaultFramesIndex = NOT_SHOWING_BOX_FRAMES;
	return;
}


void  SupplyBoxView::update(SupplyBoxDTO other, int i) {
	this->box = other;
}

SupplyBoxView::~SupplyBoxView() {}