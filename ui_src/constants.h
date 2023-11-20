#ifndef UI_CONSTANTS_H
#define UI_CONSTANTS_H

// #include "../shared_src/constants.h"
#include "../shared_src/config_loader.h"

namespace uiConstants {

#define CONFIG ConfigLoader::getInstance()

//worm animation constants
enum FrameType {
	STILL_FRAMES = 0,
	JUMPING_FRAMES = 1,
	WALKING_FRAMES = 2,
	SURRENDING_FRAMES = 3,
	POSTMORTEM_FRAMES = 4,
	TPING_FRAMES = 5,
	HITTING_FRAMES = 6,
	DRAWING_AXE_FRAMES = 7,
	HOLDING_AXE_FRAMES = 8,
	DRAWING_BAZOKA_FRAMES = 9,
	HOLDING_BAZOKA_FRAMES = 10,
	DRAWING_RG_FRAMES = 11,
	HOLDING_RG_FRAMES = 12,
	DRAWING_BANANA_FRAMES = 13,
	HOLDING_BANANA_FRAMES = 14
};

enum hudSprites {
	CURRENT_WORM_INDICATOR_TEXTURE = 0,
	BAZOOKA_ICON,
	GGRENADE_ICON,
	BAT_ICON,
	TP_ICON,
	MORTAR_ICON,
	RGRENADE_ICON,
	BANANA_ICON
};

enum commands {
	BAZOOKA_CODE = 1,
	GGRENADE_CODE,
	BAT_CODE,
	TP_CODE,
	MORTAR_CODE,
	RGRENADE_CODE,
	BANANA_CODE
};

//rocket animation constants
enum projectileType {
	ROCKET_FRAMES = 0,
	EXPLOSION_FRAMES,
	POST_EXPLOSION_FRAMES,
	RED_GRENADE_FRAMES

};

extern const int MUSIC_VOLUME;

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern const float m_to_pix_x;
extern const float m_to_pix_y;
extern const int TEAM_1;
extern const int TEAM_2;

}
#endif

