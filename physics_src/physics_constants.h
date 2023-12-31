#ifndef PHYSICS_CONSTANTS_H
#define PHYSICS_CONSTANTS_H

#include "../shared_src/constants.h"

#define CONFIG ConfigLoader::getInstance()

//World constants
#define TIME_STEP 1.0f / CONFIG.getFps()
#define VELOCITY_ITERATIONS 8
#define POSITION_ITERATIONS 3 

#define INFINITE_DAMPING 1000.0f
#define STANDARD_DAMPING 0.5f

//beam
#define BEAM_HEIGHT 0.8f

#define WORM_HEIGHT 0.8f
#define WORM_WIDTH 0.6f
#define WORM_DENSITY 1.0f
#define WORM_FRICTION 0.3f

#define VELOCITY_SMOOTH_BREAK CONFIG.getWormMoveVelocity() * 0.7f

//supply box constants
#define SUPPLY_BOX_WIDTH 1.0f
#define SUPPLY_BOX_HEIGHT 1.0f

//Bazooka constants
#define BAZOOKA_WIDTH 0.25f
#define BAZOOKA_HEIGHT 0.25f

//Mortar constants
#define MORTAR_WIDTH 0.25f 
#define MORTAR_HEIGHT 0.25f 

//Projectile fragments constants
#define FRAGMENT_WIDTH 0.125f 
#define FRAGMENT_HEIGHT 0.125f

//Red grenade constants
#define RED_GRENADE_WIDTH 0.25f
#define RED_GRENADE_HEIGHT 0.25f

//green grenade constants
#define GREEN_GRENADE_WIDTH 0.25f
#define GREEN_GRENADE_HEIGHT 0.25f

//Banana constants
#define BANANA_WIDTH 0.25f
#define BANANA_HEIGHT 0.25f

//Dynamite constants
#define DYNAMITE_WIDTH 0.25f
#define DYNAMITE_HEIGHT 0.25f

//Air attack missile constants
#define AIR_ATTACK_MISSILE_WIDTH 0.25f
#define AIR_ATTACK_MISSILE_HEIGHT 0.25f
#define AIR_ATTACK_MISSILE_AMOUNT 6

//Holy grenade constants
#define HOLY_GRENADE_WIDTH 0.25f
#define HOLY_GRENADE_HEIGHT 0.25f

//Bat constants
#define BAT_HEIGHT 0.8f
#define BAT_WIDTH 1.3f

#endif