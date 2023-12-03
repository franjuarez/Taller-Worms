#include "constants.h"
#include <iostream>
namespace uiConstants {

//const int DEFAULT_FRAMES = STILL_FRAMES;



const int MUSIC_VOLUME = CONFIG.getMusicVolume();
const int SFX_VOLUME = CONFIG.getSfxVolume();

const int WINDOW_WIDTH = 812;
const int WINDOW_HEIGHT = 812;
const float m_to_pix_x = (WINDOW_WIDTH / CONFIG.getViewfieldX());
const float m_to_pix_y = (- WINDOW_WIDTH / CONFIG.getViewfieldY()); //dejo height para que no se estire
const int TEAM_1 = 1;
const int TEAM_2 = 2;

}
