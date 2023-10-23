#ifndef MOTOR_H
#define MOTOR_H

#include <box2d/box2d.h>
#include <vector>
#include <ostream>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 512

#define GRAVITY_X 0.0f
#define GRAVITY_Y -30.0f

#define WORLD_WIDTH 50.0f
#define WORLD_HEIGHT 40.0f

#define GROUND_WIDTH WORLD_WIDTH
#define GROUND_HEIGHT 10

#define BANANERO_HEIGHT 2.5f
#define BANANERO_WIDTH 2.5f

#define BANANERO_DENSITY 20.0f
#define BANANERO_FRICTION 2.0f
	
#define BANANERO_STARTING_X (GROUND_WIDTH / 2)
#define BANANERO_STARTING_Y (GROUND_HEIGHT + BANANERO_HEIGHT + 10)

#define BANANA_HEIGHT 0.7f
#define BANANA_WIDTH 0.3f
#define BANANA_DENSITY 5.0f

#define m_to_pix_x (SCREEN_WIDTH / WORLD_WIDTH)
#define m_to_pix_y (-1 * SCREEN_HEIGHT / WORLD_HEIGHT)

#define MOVE_VELOCITY 10
#define JUMP_STRENGH 10

#define LEFT -1
#define RIGHT 1
#define FRONT 0

typedef enum {BANANERO = 0, BANANA} EntityType;

typedef struct _entities {
    EntityType type;
    float x;
    float y;
    float angle;
    int dir;
    
} entity_t;
class Motor {
private:
    b2World world;
    int dir_bananero;
    b2Body* bananero;
    std::vector<b2Body*> bananas;
    
    void createBanana();

public:
    Motor();
    void move(int dir);
    void jump();
    void throwBanana();
    std::vector<entity_t> step();
};
#endif
