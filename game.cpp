#include "game.h"
#include <iostream>

#define AC_Y -9.8f
#define AC_X 0.0f

#define WORLD_WIDTH 50.0f
#define WORLD_HEIGHT 40.0f

#define GROUND_HEIGHT 0.2f

#define BANANERO_WIDTH 1.1f
#define BANANERO_HEIGHT 1.3f

#define BANANERO_START_X WORLD_WIDTH / 2.0f
#define BANANERO_START_Y (GROUND_HEIGHT + BANANERO_HEIGHT + 1)


#define BANANERO_DENSITY 100.0f
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
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(WORLD_WIDTH/2, 0.0f);
    this->groundBody = this->world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(WORLD_WIDTH/2, GROUND_HEIGHT);
    groundBody->CreateFixture(&groundBox, 0.0f);

    /// Bananero 
    b2BodyDef bananeroBodyDef;

    bananeroBodyDef.position.Set(BANANERO_START_X, BANANERO_START_Y);
    bananeroBodyDef.type = b2_dynamicBody;
    this->bananero = this->world.CreateBody(&bananeroBodyDef);
    
    b2PolygonShape bananeroBox;
    bananeroBox.SetAsBox(BANANERO_WIDTH, BANANERO_HEIGHT);
    
    b2FixtureDef bananeroFixture;
    bananeroFixture.shape = &bananeroBox;
    bananeroFixture.density = BANANERO_DENSITY;
    bananeroFixture.friction = BANANERO_FRICTION;
    
    this->bananero->CreateFixture(&bananeroFixture);
    // this->bananero->SetBullet(true);
    
    /*
    /// Bananero 2
    b2BodyDef bananero2BodyDef;

    bananero2BodyDef.position.Set(BANANERO_START_X, BANANERO_START_Y + 2.0f);
    bananero2BodyDef.type = b2_dynamicBody;
    b2Body* bananero2 = this->world.CreateBody(&bananero2BodyDef);
    
    b2PolygonShape bananero2Box;
    bananero2Box.SetAsBox(BANANERO_WIDTH, BANANERO_HEIGHT);
    
    b2FixtureDef bananero2Fixture;
    bananero2Fixture.shape = &bananero2Box;
    bananero2Fixture.density = BANANERO_DENSITY + 5.0f;
    bananero2Fixture.friction = BANANERO_FRICTION;
    
    bananero2->CreateFixture(&bananero2Fixture);    
    */
}

/*
b2Fixture* groundFixture = groundBody->CreateFixture(&groundBox, 0.0f);
*/

std::vector<entities_t> Game::step(){
    this->world.Step(1.0f / 30.0f, 6, 2);
    
    this->world.GetBodyList();
    //print the bodies
    for(b2Body* body = this->world.GetBodyList(); body; body = body->GetNext()) {
        if(body->GetType() == b2_staticBody){
            std::cout << "HAY PISO: ";
            std::cout << "x: " << body->GetPosition().x << " y: " << body->GetPosition().y << std::endl;
        }
        if(body == this->bananero) std::cout << "HAY BANANERO\n";
    }
/*
___________
|    |    |
|    |    |
|____|____|
|    |    |
|    |    |
|____|____|




*/
    std::vector<entities_t> entities;
    entities_t entity;
    entity.type = BANANERO;
    entity.x = (this->bananero->GetPosition().x + BANANERO_WIDTH) * m_to_pix_x;
    entity.y = ((this->bananero->GetPosition().y + BANANERO_HEIGHT) * m_to_pix_y) - ((WORLD_HEIGHT - 8) * m_to_pix_y);

    
    std::cout << "x: " << this->bananero->GetPosition().x << " y: " << this->bananero->GetPosition().y << std::endl;
    entity.angle = this->bananero->GetAngle();
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