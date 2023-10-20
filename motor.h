#ifndef MOTOR_H
#define MOTOR_H

#include <box2d/box2d.h>

class Motor {
    b2World world;
    b2Body* groundBody;



public:
    b2Body* block1;
    b2Body* block2;
    Motor(float ax, float ay);
    void step(float time_step, int32 velocity_iterations, int32 position_iterations);
};
#endif
