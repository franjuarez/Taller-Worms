#ifndef AUXILIAR_PHYSICS_FUNCTIONS_H
#define AUXILIAR_PHYSICS_FUNCTIONS_H

#include <box2d/box2d.h>
#include <unordered_set>
#include "../physics_constants.h"
#include "../entities/worm.h"
#include "../query_handlers/explosion_handler.h"

// Calculates the vertical velocity needed to reach a certain height
float calculateVerticalVelocityForHeight(float desiredHeight);

// Calculates the number of timesteps needed to reach the top of a jump
float getTimestepsToTop(b2Vec2& startingVelocity);

// Calculates the initial velocity needed to reach a certain height and distance
b2Vec2 calculateInitialVelocityForMaxHeight(float maxHeight, float distance);

// Calculates the height of a fall given a velocity
float calculateFallHeightFromVelocity(b2Vec2 velocity);

// Calculates the velocity of a projectile given its max speed, angle, direction and power
b2Vec2 calculatVelocityOfProjectile(float maxSpeed, float angle, float direction, float power);

// Explodes an explosive
void explosiveExplode(b2Body* projectile, float explosiveDamage, float explosiveRadius);

#endif