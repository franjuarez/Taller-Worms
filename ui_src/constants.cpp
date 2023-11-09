#include "constants.h"

namespace uiConstants {

const int STILL_FRAMES = 0;
const int JUMPING_FRAMES = 1;
const int DEFAULT_FRAMES = STILL_FRAMES;

const int WINDOW_WIDTH = 840;
const int WINDOW_HEIGHT = 840;
const int VIEWFIELD_X = 25;
const int VIEWFIELD_Y = 25;
const float m_to_pix_x = (WINDOW_WIDTH / VIEWFIELD_X);
const float m_to_pix_y = (- WINDOW_WIDTH / VIEWFIELD_Y); //dejo height para que no se estire
const int TEAM_1 = 1;
const int TEAM_2 = 2;

}


