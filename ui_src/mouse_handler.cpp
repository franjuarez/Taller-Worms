#include "mouse_handler.h"

#define MOUSE_SPEED 0

#include "constants.h"
using namespace uiConstants;

//	int& camX;
//	int& camY;
//	bool moving;


MouseHandler::MouseHandler(int& camX, int& camY) : camX(camX), camY(camY) {
	moving = false;
	mousePosX = WINDOW_WIDTH / 2;
	mousePosY = WINDOW_HEIGHT / 2;
}

void MouseHandler::handleMovement(int mouseX, int mouseY) {
	//en el movimiento actualizo la posicion de mouse
	mousePosX = mouseX;
	mousePosY = mouseY;
}

void MouseHandler::updateCam() {
	//independientemente de si hay un evento tengo que mover la camara si el 
	//mouse esta en las zonas de movimiento
	
	if (this->mousePosX > WINDOW_WIDTH * 0.9) {
		this->camX += MOUSE_SPEED;
	} else if (this->mousePosX < WINDOW_WIDTH * 0.1) {
		this->camX -= MOUSE_SPEED;
	}

	if (this->mousePosY > WINDOW_HEIGHT * 0.9) {
		this->camY += MOUSE_SPEED;
	} else if (this->mousePosY < WINDOW_HEIGHT * 0.1) {
		this->camY -= MOUSE_SPEED;
	}

}
