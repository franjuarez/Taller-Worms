#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2pp/SDL2pp.hh>
#include <vector>
#include "motor.h"
using namespace SDL2pp;

class Screen {
	
private:
	SDL sdl;
	Window window;
	Renderer renderer;
	Motor motor;
	std::vector<entity_t> entities;
	
public:
	Screen();

	void run();

	void draw(unsigned int frame_ticks);

	void clear();

	void present();

	void parseKey(SDL_Keycode key);

	~Screen();
};

#endif
