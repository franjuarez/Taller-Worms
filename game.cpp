#include "game.h"

#define AC_Y -9.8f
#define AC_X 0.0f

#define WORLD_WIDTH 50.0f
#define WORLD_HEIGHT 40.0f

#define GROUND_HEIGHT 0.2f

#define BANANERO_WIDTH 0.1f
#define BANANERO_HEIGHT 0.3f

#define BANANERO_START_X WORLD_WIDTH / 2.0f
#define BANANERO_START_Y (GROUND_HEIGHT + BANANERO_HEIGHT + 1)

#define BANANERO_DENSITY 10.0f
#define BANANERO_FRICTION 0.8f
#define DERECHA 0
#define IZQUIERDA 1

#define m_to_pix_x (SCREEN_WIDTH / WORLD_WIDTH)
#define m_to_pix_y (-1 * SCREEN_HEIGHT / WORLD_HEIGHT)

// 0.2_______________B__________________
// 
// +- ----------------------------------
//-0.2__________________________________

Game::Game() : world(b2Vec2(AC_X, AC_Y)), bananero_dir(0) {
    /// Ground
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 0.0f);
    b2Body* groundBody = this->world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(WORLD_WIDTH, GROUND_HEIGHT);
    groundBody->CreateFixture(&groundBox, 0.0f);

    /// Bananero 
    b2BodyDef bananeroBodyDef;

    bananeroBodyDef.position.Set(BANANERO_START_X, BANANERO_START_Y);
    bananeroBodyDef.type = b2_dynamicBody;
    this->bananeroBody = this->world.CreateBody(&bananeroBodyDef);
    
    b2PolygonShape bananeroBox;
    bananeroBox.SetAsBox(BANANERO_WIDTH, BANANERO_HEIGHT);
    
    b2FixtureDef bananeroFixture;
    bananeroFixture.shape = &bananeroBox;
    bananeroFixture.density = BANANERO_DENSITY;
    bananeroFixture.friction = BANANERO_FRICTION;
    
    this->bananeroBody->CreateFixture(&bananeroFixture);
}

std::vector<entities_t> Game::step(){
    this->world.Step(1.0f / 30.0f, 6, 2);

    std::vector<entities_t> entities;
    entities_t entity;
    entity.type = BANANERO;
    entity.x = this->bananeroBody->GetPosition().x * m_to_pix_x;
    entity.y = this->bananeroBody->GetPosition().y * m_to_pix_y;
    entity.angle = this->bananeroBody->GetAngle();
    entity.dir = this->bananero_dir;
    entities.push_back(entity);
    return entities;
    // this->world.GetBodyList();
    // for (b2Body* body = this->world.GetBodyList(); body; body = body->GetNext()) {
    //     if(body->GetType() == b2_staticBody) continue;
    //     if(body == this->bananeroBody) continue;
    //     entities_t entity;
    //     entity.type = BANANA;
    //     entity.x = body->GetPosition().x;
    //     entity.y = body->GetPosition().y;
    //     entity.angle = body->GetAngle();
    //     entity.dir = body->GetLinearVelocity().x; //Arreglar
    //     entities.push_back(entity);
    // }
}

void Game::moveRight() {
    this->bananero_dir = DERECHA;
    //  SetLinearVelocity(const b2Vec2& v);
    return;
}

void Game::moveLeft() {
    this->bananero_dir = IZQUIERDA;
}

void Game::throwBanana() {
    return;
}

Game::~Game() {}