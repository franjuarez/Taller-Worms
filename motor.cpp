#include "motor.h"
#include <iostream>

// Para que el bicho frene smooooth
#define SMOOTH_BRAKING 0.3

Motor::Motor() :  
    world(b2Vec2(GRAVITY_X, GRAVITY_Y)), dir_bananero(FRONT){
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 0.0f);
    b2Body* groundBody = this->world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(GROUND_WIDTH, GROUND_HEIGHT);
    groundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef bananeroDef;
    bananeroDef.position.Set(BANANERO_STARTING_X, BANANERO_STARTING_Y);
    bananeroDef.type = b2_dynamicBody;
    this->bananero= this->world.CreateBody(&bananeroDef);
    
    b2PolygonShape bananeroBox;
    bananeroBox.SetAsBox(BANANERO_WIDTH, BANANERO_HEIGHT);

    b2FixtureDef bananeroFixture;
    bananeroFixture.shape = &bananeroBox;
    bananeroFixture.density = BANANERO_DENSITY;
    bananeroFixture.friction = BANANERO_FRICTION;

    this->bananero->CreateFixture(&bananeroFixture);
}

std::vector<entity_t> Motor::step(){
    float timeStep = 1.0f / 30.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
    this->world.Step(timeStep, velocityIterations, positionIterations);

	std::vector<entity_t> vectorEnt;
	
	entity_t ent_bananero;

	ent_bananero.type = BANANERO;
	if (abs(this->bananero->GetLinearVelocity().x) <= SMOOTH_BRAKING) {
		ent_bananero.dir = FRONT;
	} else {
		ent_bananero.dir = dir_bananero;
	}
	
	ent_bananero.x = (this->bananero->GetPosition().x + BANANERO_WIDTH) * m_to_pix_x;
	ent_bananero.y = ((this->bananero->GetPosition().y + BANANERO_HEIGHT) * m_to_pix_y) - (WORLD_HEIGHT * m_to_pix_y);
	ent_bananero.angle = this->bananero->GetAngle();

	vectorEnt.push_back(ent_bananero);

	for (size_t i = 0; i < bananas.size(); i++) {
		b2Vec2 pos = bananas.at(i)->GetPosition();
		entity_t entBanana;
		entBanana.type = BANANA;
		entBanana.dir = dir_bananero == FRONT ? RIGHT : dir_bananero;
		entBanana.x = (pos.x + BANANA_WIDTH) * m_to_pix_x;
		entBanana.y = ((pos.y + BANANA_HEIGHT) * m_to_pix_y) - (WORLD_HEIGHT * m_to_pix_y);
		vectorEnt.push_back(entBanana);
	}
	return vectorEnt;
}

void Motor::move(int dir) {
	dir_bananero = dir;
	this->bananero->SetLinearVelocity(b2Vec2(MOVE_VELOCITY*dir,0));
}

void Motor::jump() {
	if (this->bananero->GetLinearVelocity().y != 0)
		return;
	this->bananero->SetLinearVelocity(b2Vec2(0.0f, JUMP_STRENGH) + this->bananero->GetLinearVelocity());
}

b2Body* Motor::createBanana(){

    b2BodyDef bananaDef;
	b2Vec2 pos = this->bananero->GetPosition();
    bananaDef.position.Set(pos.x, pos.y);
    bananaDef.type = b2_dynamicBody;
    b2Body* banana = this->world.CreateBody(&bananaDef);
    
    b2PolygonShape bananaBox;
    bananaBox.SetAsBox(BANANA_WIDTH, BANANA_HEIGHT);

    b2FixtureDef bananaFixture;
    bananaFixture.shape = &bananaBox;
    bananaFixture.density = BANANA_DENSITY;

    banana->CreateFixture(&bananaFixture);
	return banana;
}

void Motor::throwBanana(){
	b2Body* banana  = createBanana();
	// std::cout << "banana x: " << banana->GetPosition().x << "     " << "banana y: " << banana->GetPosition().y << std::endl;
	// banana->ApplyForceToCenter(b2Vec2(5.0f,5.0f), true);
	banana->SetLinearVelocity(b2Vec2(BANANA_SPLIT_X, BANANA_SPLIT_Y) + this->bananero->GetLinearVelocity());
	bananas.push_back(banana);
}
