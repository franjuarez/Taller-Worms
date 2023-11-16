#ifndef UI_CONSTANTS_H
#define UI_CONSTANTS_H

namespace uiConstants {

enum FrameType {
	STILL_FRAMES = 0,
	JUMPING_FRAMES = 1,
	WALKING_FRAMES = 2,
	SURRENDING_FRAMES = 3,
	POSTMORTEM_FRAMES = 4,
	TPING_FRAMES = 5,
	HITTING_FRAMES = 6
};

extern const int MUSIC_VOLUME;

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern const int VIEWFIELD_X;
extern const int VIEWFIELD_Y;
extern const float m_to_pix_x;
extern const float m_to_pix_y;
extern const int TEAM_1;
extern const int TEAM_2;

}
#endif

