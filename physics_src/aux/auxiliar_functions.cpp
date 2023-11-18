#include "auxiliar_functions.h"

const b2Vec2 GRAVITY = b2Vec2(CONFIG.getWorldGravityX(), CONFIG.getWorldGravityY());

float calculateVerticalVelocityForHeight(float desiredHeight){
    if (desiredHeight <= 0)
        return 0;

    b2Vec2 stepGravity = TIME_STEP * TIME_STEP * GRAVITY;

    float a = 0.5f / stepGravity.y;
    float b = 0.5f;
    float c = desiredHeight;
    
    float quadraticSolution1 = ( -b - b2Sqrt( b*b - 4*a*c ) ) / (2*a);
    float quadraticSolution2 = ( -b + b2Sqrt( b*b - 4*a*c ) ) / (2*a);

    float v = quadraticSolution1 > 0 ? quadraticSolution1 : quadraticSolution2;

    return v * 60.0f;
}

float getTimestepsToTop(b2Vec2& startingVelocity){
    b2Vec2 stepVelocity = TIME_STEP * startingVelocity;
    b2Vec2 stepGravity = TIME_STEP * TIME_STEP * GRAVITY;

    float n = -stepVelocity.y / stepGravity.y - 1;
    return n;
}

b2Vec2 calculateInitialVelocityForMaxHeight(float maxHeight, float distance){
    float verticalVelocity = calculateVerticalVelocityForHeight(maxHeight);
    b2Vec2 velStep = b2Vec2(0, verticalVelocity);
    float timeToTop = getTimestepsToTop(velStep);
    float horizontalVelocity = distance / timeToTop * CONFIG.getFps() /2;
    velStep.x = horizontalVelocity;
    return velStep;
}

float calculateFallHeightFromVelocity(b2Vec2 velocity){
    float fallVel = abs(velocity.y);
    float gravityModule = abs(GRAVITY.y);
    
    float n = (fallVel - (gravityModule * TIME_STEP)) / (gravityModule * TIME_STEP);
    float height = 0.5f * gravityModule * pow(TIME_STEP, 2) * pow(n, 2);
    return height;
}

b2Vec2 calculatVelocityOfProjectile(float maxSpeed, float angle, float direction, float power){
    float velX = CONFIG.getProjectileMaxSpeed() * (power / 100.0f);
    float velY = CONFIG.getProjectileMaxSpeed() * (power / 100.0f);
    int sign = (direction == LEFT) ? -1 : 1;
    velX = cos(angle * b2_pi / 180.0f) * velX * sign;
    velY = sin(angle * b2_pi / 180.0f) * velY;
    return b2Vec2(velX, velY);
}

