#include "mouse_handler.h"

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
	
	if (this->mousePosX > WINDOW_WIDTH * 0.8 && this->mousePosX < WINDOW_WIDTH - 10) {
		this->camX += CONFIG.getCameraSpeed();
	} else if (this->mousePosX < WINDOW_WIDTH * 0.1 && this->mousePosX > 0) {
		this->camX -= CONFIG.getCameraSpeed();
	}

	if (this->mousePosY > WINDOW_HEIGHT * 0.8 && this->mousePosY < WINDOW_HEIGHT - 10) {
		this->camY += CONFIG.getCameraSpeed();
	} else if (this->mousePosY < WINDOW_HEIGHT * 0.1 && this->mousePosY > 0) {
		this->camY -= CONFIG.getCameraSpeed();
	}

}
