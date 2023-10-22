#ifndef GAME_H
#define GAME_H

#include <box2d/box2d.h>
#include <vector>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 512

typedef enum {BANANERO = 0, BANANA} EntityType;

typedef struct _entities {
    EntityType type;
    float x;
    float y;
    float angle;
    int dir;
    
} entities_t;

class Game {
private:
    
    b2World world;
    int bananero_dir;
    b2Body* bananero;
    b2Body* bananero2;
    b2Body* groundBody;
    //std::vector<b2Body*> bananas;

public:
    Game();

    ~Game();
  
    std::vector<entities_t> step();
    void moveRight();
    void moveLeft();
    void throwBanana();
};

#endif
