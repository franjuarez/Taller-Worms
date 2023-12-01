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
#define AMOUNT_OF_WEAPONS 7

enum /*SUPPLY_BOX_TYPE*/{
    HEALTH_SUPPLY = 0,
    MORTAR_SUPPLY,
    RED_GRENADE_SUPPLY,
    BANANA_SUPPLY,
    // HOLY_GRENADE_SUPPLY,
    // AIR_ATTACK_SUPPLY,
    // DYNAMITE_SUPPLY,
    BAT_SUPPLY,
    TELEPORT_SUPPLY,
    TRAP_SUPPLY,
};

enum /* CHEATS */ {
    ADD_HEALTH = 0,
    ALL_WEAPONS,
    ALL_INVINCIBLE,
    STOP_TURN,
    RENEW_TURN,
};


enum /*MATCH TYPE*/{
    NEW_MATCH = 0,
    JOIN,
    REFRESH,
};

enum action {
    STANDING, //0
    MOVING, //1
    JUMPING, //2
    EJECTED, //3
};

#define WAITING 0
#define STARTED 1


#define PLAYING -1
#define ALL_LOST -2

#define INFINITE_AMUNITION -1

#endif
