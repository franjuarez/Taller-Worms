#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2pp/SDL2pp.hh>
#include <chrono>
#include <vector>


using namespace SDL2pp;

typedef struct beam {
	int x;
	int y;
	double angle;
} beam_t;

class Screen {
private:

	SDL sdl;
	Window window;
	Renderer renderer;
	std::vector<beam_t> beams;
	Texture backgroundSprite;
	Texture beamSprite;

	void draw();
	void processInput();

public:
	Screen();

	~Screen();

	void start();




};

#endif
