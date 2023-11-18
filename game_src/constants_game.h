#ifndef CONSTANTS_GAME_H
#define CONSTANTS_GAME_H

#define NO_TEAM_NEEDED 0

enum /*Direction*/ {
    LEFT_DIR = 0,
    RIGHT_DIR, 
    FORWARD_DIR,
    BACKWARD_DIR,
};

enum /*WEAPON_TYPE*/{
    BAZOOKA = 0,
    GREEN_GRENADE,
    BAT,
    TP,
    MORTAR,
    RED_GRENADE,
    BANANA,
};

#define PLAYING -1
#define ALL_LOST -2

#define AMOUNT_OF_WEAPONS 7
#define INFINITE_AMUNITION -1

#endif
