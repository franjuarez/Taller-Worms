
#include <box2d/box2d.h>
#include <SDL2pp/SDL2pp.hh>

#include <iostream>

using namespace SDL2pp;
int main() {
	// Initialize SDL library
	SDL sdl(SDL_INIT_VIDEO);

	// Create main window: 640x480 dimensions, resizable, "SDL2pp demo" title
	Window window("SDL2pp demo",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			1000, 880,
			SDL_WINDOW_RESIZABLE);

	// Create accelerated video renderer with default driver
	Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

	// Load sprites image as a new texture
	Texture sprites(renderer, DATA_PATH "/M484SpaceSoldier.png");

	// Clear screen
	renderer.Clear();

	// Render our image, stretching it to the whole window
	renderer.Copy(sprites);

	// Show rendered frame
	renderer.Present();

	// 5 second delay
	SDL_Delay(5000);
	return 0;
}