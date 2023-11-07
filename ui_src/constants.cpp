#include "constants.h"

namespace uiConstants {

const int STILL_FRAMES = 0;
const int JUMPING_FRAMES = 1;
const int DEFAULT_FRAMES = STILL_FRAMES;

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 512;
const int VIEWFIELD_X = 15;
const int VIEWFIELD_Y = 15;
const float m_to_pix_x = (WINDOW_HEIGHT / VIEWFIELD_X);
const float m_to_pix_y = (- WINDOW_HEIGHT / VIEWFIELD_Y); //dejo height para que no se estire
const int TEAM_1 = 1;
const int TEAM_2 = 2;

}


