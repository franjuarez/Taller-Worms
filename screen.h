#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;

class Screen {
	
private:
	SDL sdl;
	Window window;
	Renderer renderer;
	
public:
	Screen();

	void createSquare(int x, int y, int width, int height, int angle);

	void clear();

	void present();

	~Screen();
};
#endif
