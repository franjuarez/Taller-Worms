#ifndef BEAM_VIEW_H
#define BEAM_VIEW_H


#include <SDL2pp/SDL2pp.hh>
#include "../game_src/beam_dto.h"
#include "constants.h"

using namespace SDL2pp;
using namespace uiConstants;

class BeamView {
private:
    BeamDTO beam;
    Texture& beamSprite;

public:
    BeamView(BeamDTO& beam, Texture& beamSprite);
    ~BeamView();
   	void display(Renderer& renderer, int camX, int camY);
};

#endif
