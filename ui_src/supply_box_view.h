#ifndef SUPPLY_BOX_VIEW_H
#define SUPPLY_BOX_VIEW_H

#include <SDL2pp/SDL2pp.hh>
#include "constants.h"
#include "../game_src/supply_box_dto.h"

using namespace SDL2pp;
using namespace uiConstants;

class SupplyBoxView {
private:
	SupplyBoxDTO box;
	std::vector<Texture>& boxSpriteSheets;
	std::vector<std::vector<Rect>> frames;
	int startingPoint;
	int currentFramesIndex;
	int defaultFramesIndex;

public:
	SupplyBoxView(SupplyBoxDTO box, std::vector<Texture>& boxSpriteSheets);
	~SupplyBoxView();

	void open(int i);
	void display(int i, Renderer& renderer, int camX, int camY);
	void update(SupplyBoxDTO other, int i);



};

#endif

