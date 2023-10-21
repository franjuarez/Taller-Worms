#include "screen.h"
#include "motor.h"

#include <box2d/box2d.h>
#include <SDL2pp/SDL2pp.hh>

#include <chrono>
#include <iostream>

int main() {
	Screen screen;
	Motor motor(0.0f, -9.8f);
	
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;


	int i = 0;
	while(1) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return 0;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE: case SDLK_q:
					return 0;
				}
			}
		}
		motor.step(timeStep, velocityIterations, positionIterations);
		if (i % 10 != 0) {
			continue;
		}
		

		screen.clear();

		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		

		// Now print the position and angle of the body.
		b2Vec2 position1 = motor.block1->GetPosition();
		b2Vec2 position2 = motor.block2->GetPosition();

		int q1,j1,k1;
		q1 = position1.x * 20.45;
		j1 = (-5.12) * position1.y + 512;
		k1 = motor.block1->GetAngle();

		int q2,j2,k2;
		q2 = position2.x * 20.45;
		j2 = (-5.12) * position2.y + 512;
		k2 = motor.block1->GetAngle();

		screen.createSquare(q1, j1, 100, 100, k1);
		screen.createSquare(q2, j2, 100, 100, k2);		

		screen.present();
		std::chrono::seconds(1/12);
		i++;
	}

	return 0;
}

// int main(){
// 	Motor motor(0.0f, -9.8f);
	
// 	float timeStep = 1.0f / 60.0f;
// 	int32 velocityIterations = 6;
// 	int32 positionIterations = 2;
	
// 	for (int32 i = 0; i < 280 ; ++i){
// 		// Instruct the world to perform a single step of simulation.
// 		// It is generally best to keep the time step and iterations fixed.
// 		motor.step(timeStep, velocityIterations, positionIterations);

// 		// Now print the position and angle of the body.
// 		b2Vec2 position1 = motor.block1->GetPosition();
// /*
// b2d:
// |
// |
// |________

// sdl:_________
// |
// |
// |
// */

// 		float q,j,k;
// 		q = position1.x * 20.45;
// 		j = (-5.12) * position1.y + 512;
// 		k = motor.block1->GetAngle();
// 		if ((i % 10) == 0) {
// 			printf(
// 				"%f %f (%f) \n",
// 				q,
// 				j,
// 				k
// 			);
// 		}
// 	}
// }
