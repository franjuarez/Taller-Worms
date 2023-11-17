#ifndef PHYSICS_CONSTANTS_H
#define PHYSICS_CONSTANTS_H

//World constants
#define WORLD_WIDTH 100
#define WORLD_HEIGHT 70
#define WORLD_GRAVITY_X 0.0f
#define WORLD_GRAVITY_Y -9.8f
#define TIME_STEP 1/60.0f
#define TIME_HERTZ pow(TIME_STEP, -1)
#define VELOCITY_ITERATIONS 8
#define POSITION_ITERATIONS 3
#define INFINITE_DAMPING 1000.0f
#define STANDARD_DAMPING 0.5f

//directions
#define LEFT 0
#define RIGHT 1

//Beam constants
#define LARGE_BEAM_WIDTH 6
#define SMALL_BEAM_WIDTH 3
#define BEAM_HEIGHT 0.8f
#define BEAM_FRICTION 0.3f
#define MAX_WALKABLE_BEAM_ANGLE 45

//Worm constants
#define WORM_WIDTH 1.0f
#define WORM_HEIGHT 1.0f
#define WORM_DENSITY 1.0f
#define WORM_FRICTION 0.3f
#define WORM_DAMPING 0.3f
#define WORM_INITIAL_HEALTH 100

//Move constants    
#define MOVE_VELOCITY 0.4f
#define VELOCITY_SMOOTH_BREAK MOVE_VELOCITY/2.0f

//Jump constants
#define JUMP_FORWARD_MOVEMENT_X 1.0f
#define JUMP_FORWARD_MOVEMENT_Y 0.5f
#define JUMP_BACKWARDS_MOVEMENT_X 0.2f
#define JUMP_BACKWARDS_MOVEMENT_Y 1.2f

//Height damage constants
#define MIN_HEIGHT_TO_DAMAGE 2.0f
#define MAX_HEIGHT_DAMAGE 25.0f

//Projectile constants
#define PROJECTILE_MAX_SPEED 20.0f

//Bazooka constants
#define BAZOOKA_BLAST_RADIOUS 2.0f
#define BAZOOKA_WIDTH 0.25f
#define BAZOOKA_HEIGHT 0.25f
#define BAZOOKA_DAMAGE 50.0f

//Mortar constants
#define MORTAR_BLAST_RADIOUS 2.0f
#define MORTAR_WIDTH 0.25f
#define MORTAR_HEIGHT 0.25f
#define MORTAR_DAMAGE 50.0f
#define MORTAR_FRAGMENTS 6

//Projectile fragments constants
#define FRAGMENT_BLAST_RADIOUS 2.0f
#define FRAGMENT_WIDTH 0.125f
#define FRAGMENT_HEIGHT 0.125f
#define FRAGMENT_DAMAGE 10.0f

//Red grenade constants
#define RED_GRENADE_BLAST_RADIOUS 2.0f
#define RED_GRENADE_WIDTH 0.25f
#define RED_GRENADE_HEIGHT 0.25f
#define RED_GRENADE_DAMAGE 30.0f
#define RED_GRENADE_FRAGMENTS 6

//green grenade constants
#define GREEN_GRENADE_BLAST_RADIOUS 2.0f
#define GREEN_GRENADE_WIDTH 0.25f
#define GREEN_GRENADE_HEIGHT 0.25f
#define GREEN_GRENADE_DAMAGE 30.0f

//Banana constants
#define BANANA_BLAST_RADIOUS 4.0f
#define BANANA_WIDTH 0.25f
#define BANANA_HEIGHT 0.25f
#define BANANA_DAMAGE 70.0f
#define BANANA_RESTITUTION 0.9f
//taria bueno agregar una constante para ver si la afecta el viento

//Explosion constants
#define EXPLOSION_IMPULSE_FACTOR_X 10.0f
#define EXPLOSION_IMPULSE_FACTOR_Y 4.0f

//Bat constants
#define BAT_HEIGHT 0.4f
#define BAT_WIDTH 1.3f
#define BAT_DAMAGE 10.0f
#define BAT_IMPULSE_FACTOR 0.1f

#endif