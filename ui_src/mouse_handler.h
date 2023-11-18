#ifndef MOUSE_HANDLER_H
#define MOUSE_HANDLER_H

#include "constants.h"

class MouseHandler {
private:
	int& camX;
	int& camY;
	int mousePosX;
	int mousePosY;
	bool moving;

public:
	MouseHandler(int& camX, int& camY);

	//la idea es refactorizar para que reciva el evento directamente
	//pero no quiero pelear ahora con temas de dependencias
	void handleMovement(int mouseX, int mouseY);

	void updateCam();
};

#endif