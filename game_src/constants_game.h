#ifndef CONSTANTS_GAME_H
#define CONSTANTS_GAME_H


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
    TELEPORT,
    MORTAR,
    RED_GRENADE,
    BANANA,
    FRAGMENT,
};

enum /* CHEATS */ {
    ADD_HEALTH = 0,
    ALL_WEAPONS,
    ALL_INVINCIBLE,
    STOP_TURN,
    RENEW_TURN,
};

#define WAITING 0
#define STARTED 1

#define PLAYING -1
#define ALL_LOST -2

#define AMOUNT_OF_WEAPONS 7
#define INFINITE_AMUNITION -1

#endif
