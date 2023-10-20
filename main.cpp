#include "screen.h"
#include <box2d/box2d.h>
#include <SDL2pp/SDL2pp.hh>

#include <chrono>
#include <iostream>

int main() {
	Screen screen;

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

		screen.clear();
		screen.createSquare(i,i%100,100,100);
		screen.createSquare(i*20,i*20%100,100,100);
		screen.present();
		std::chrono::seconds(1/12);
		i++;
	}

	return 0;
};
