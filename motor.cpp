#include "motor.h"
/*
100    G1
|
|      
|
|
|
|
|
|______________________________________________________
|                                                      |
|                                                      |
|                        EL PISO                       |
|                                                      |
+------------------------------------------------------|
|                                                      |
|                                                      |
|                                                      |
|______________________________________________________|
|
|
*/
Motor::Motor(float ax, float ay) :  
        world(b2Vec2(ax, ay)){
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, 0.0f);
    this->groundBody = this->world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    b2BodyDef block1Def;
    block1Def.position.Set(10, 100);
    block1Def.type = b2_dynamicBody;
    this->block1 = this->world.CreateBody(&block1Def);
    
    b2PolygonShape block1Box;
    block1Box.SetAsBox(2.5f, 2.5f);

    b2FixtureDef block1Fixture;
    block1Fixture.shape = &block1Box;
    block1Fixture.density = 10.0f;
    block1Fixture.friction = 0.3f;

    this->block1->CreateFixture(&block1Fixture);

    b2BodyDef block2Def;
    block2Def.position.Set(14, 20);
    block2Def.type = b2_dynamicBody;
    this->block2 = this->world.CreateBody(&block2Def);
    
    b2PolygonShape block2Box;
    block2Box.SetAsBox(2.5f, 2.5f);

    b2FixtureDef block2Fixture;
    block2Fixture.shape = &block2Box;
    block2Fixture.density = 10.0f;
    block2Fixture.friction = 0.3f;

    this->block2->CreateFixture(&block2Fixture);
}

void Motor::step(float time_step, int32 velocity_iterations, int32 position_iterations){
    
    this->world.Step(time_step, velocity_iterations, position_iterations);
}

/*int main(int argc, char const *argv[]) {
	//todo comienza asi, definimos la matrix
	b2Vec2 gravity(7.0f, -19.7f);
	b2World world(gravity);


	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 10.0f);
	//le asigna la hitbox ¿?
	groundBody->CreateFixture(&groundBox, 0.0f);


	//hasta ahora hicimos el piso ahora hacemos CR
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 30.0f);	
	b2Body* body = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(2.0f, 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction= 0.3f ;

	body->CreateFixture(&fixtureDef);

	//arrancamos a preparar la simulacion
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	b2Vec2 position = body->GetPosition();
	float angle = body->GetAngle();

	// This is our little game loop.
	for (int32 i = 0; i < 130 ; ++i)
	{
		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world.Step(timeStep, velocityIterations, positionIterations);

		// Now print the position and angle of the body.
		position = body->GetPosition();
		angle = body->GetAngle();

		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	}

	return 0;
}
*/