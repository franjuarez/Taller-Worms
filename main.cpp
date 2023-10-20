#include "screen.h"
#include "motor.h"

#include <box2d/box2d.h>
#include <SDL2pp/SDL2pp.hh>

#include <chrono>
#include <iostream>

// int main() {
// 	Screen screen;

// 	int i = 0;
// 	while(1) {

// 		SDL_Event event;
// 		while (SDL_PollEvent(&event)) {
// 			if (event.type == SDL_QUIT) {
// 				return 0;
// 			} else if (event.type == SDL_KEYDOWN) {
// 				switch (event.key.keysym.sym) {
// 				case SDLK_ESCAPE: case SDLK_q:
// 					return 0;
// 				}
// 			}
// 		}

// 		screen.clear();
// 		screen.createSquare(i,i%100,100,100);
// 		screen.createSquare(i*20,i*20%100,100,100);
// 		screen.present();
// 		std::chrono::seconds(1/12);
// 		i++;
// 	}

// 	return 0;
// };

int main(){
	Motor motor(0.0f, -9.8f);
	
	float timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	
	for (int32 i = 0; i < 280 ; ++i){
		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		motor.step(timeStep, velocityIterations, positionIterations);

		// Now print the position and angle of the body.
		b2Vec2 position1 = motor.block1->GetPosition();
		if ((i % 10) == 0) {
			printf(
				"%f %f (%f) \n",
				position1.x,
				position1.y,
				motor.block1->GetAngle()
			);
		}
	}
}