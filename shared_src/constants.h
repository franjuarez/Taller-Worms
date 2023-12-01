#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_h

#include "config_loader.h"

#define CONFIG ConfigLoader::getInstance()

enum 
{
  READ_MAP = 0,		
  SEND_MAP,	
  SEND_DYNAMIC,	
  SEND_INFO,
  SEND_COMMAND,
  SEND_COMMAND_MOVE,
  SEND_COMMAND_SELECT,
  SEND_COMMAND_JUMP,
  SEND_COMMAND_ROCKET,
  SEND_COMMAND_TELEPORT,
  SEND_COMMAND_HIT_UPCLOSE,
  SEND_COMMAND_GRENADE,
  SEND_COMMAND_CHEAT,
  SEND_COMMAND_MATCH,
  SEND_ALL_OK,
};

#define NO_WORM_PLAYING -1
#define STARTING_TEAM 0

// directions
#define LEFT 0 
#define RIGHT 1

#define STARTING_DIRECTON RIGHT

//all of them
#define STARTING_WEAPONS {CONFIG.getBazookaStartingAmmo(), CONFIG.getGreenGrenadeStartingAmmo(), 0, 0, 0, 0 , 0}
// #define STARTING_WEAPONS {INFINITE_AMUNITION, INFINITE_AMUNITION, 0, 0, 0, 0, 0}


#endif