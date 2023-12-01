#include "worm_view.h"
#include <SDL2pp/SDL2pp.hh>
#include "../game_src/constants_game.h"
#define SDL_BLACK_COLOR SDL_Color{0,0,0}



WormView::WormView(WormDTO& worm, std::vector<Texture>& dynamicSpriteSheets, Font& wormsFont) : 
	worm(worm),
	dynamicSpriteSheets(dynamicSpriteSheets),
	frames{22},
	wormsFont(wormsFont) {
	defaultFramesIndex = STILL_FRAMES;
	currentFramesIndex = STILL_FRAMES;
	startingPoint = 0;
	angle = 0;
	//looping = true;
	float x, y, w, h;
	
	//frames for still animation
	for (int i = 0; i < 35; i++) {
		x = 19;
		w = 22;
		y = i*(60) + 16;
		h = 26;
		frames[STILL_FRAMES].push_back(Rect(x,y,w,h));
	}


	//frames for jumping animation
	for (int i = 0; i < 10; i++) {
		x = 19;
		w = 22;
		y = i*(60) + 12;
		h = 36;
		frames[JUMPING_FRAMES].push_back(Rect(x,y,w,h));
	}

	//frames for walking animation
	for (int i = 0; i < 15; i++) {
		x = 11 - (i/2);
		w = 28;
		y = i*(60) + 14;
		h = 29;
		frames[WALKING_FRAMES].push_back(Rect((int)x,y,w,h));
	}

	//frames for surrending animation
	for (int i = 0; i < 16; i++) {
		x = 19;
		w = 29;
		y = i * 60 + 7;
		h = 36;
		frames[SURRENDING_FRAMES].push_back(Rect(x,y,w,h));
	}
	

	//frames for dying/grave animation
	for (int i = 0; i < 20; i++) {
		x = 18;
		w = 23;
		y = 60*i + 4;
		h = 29;
		frames[POSTMORTEM_FRAMES].push_back(Rect(x,y,w,h));
	}

	//frames for teleporting
	frames[TPING_FRAMES].push_back(Rect(18, 16, 17, 32));
	frames[TPING_FRAMES].push_back(Rect(0, 0, 59, 54));
	frames[TPING_FRAMES].push_back(Rect(0, 60, 59, 59));


	//frames for hitting animation
	for (int i = 0; i < 4; i++) {
		x = 0;
		y = i * 104 + 16;
		w = 85;
		h = 82;
		frames[HITTING_FRAMES].push_back(Rect(x,y,w,h));
	}

	//frames for drawing the axe
	for (int i = 0; i < 15; i++) {
		x = 10;
		y = i * 104 + 20;
		w = 73;
		h = 78;
		frames[DRAWING_AXE_FRAMES].push_back(Rect(x,y,w,h));	
	}

	//frames for holding the axe still
	for (int i = 0; i < 18; i++) {
		x = 10;
		y = i * 104 + 20;
		w = 73;
		h = 78;
		frames[HOLDING_AXE_FRAMES].push_back(Rect(x,y,w,h));
	}
	

	//frames for drawing bazoka
	for (int i = 0; i < 7; i++) {
		x = 13;
		y = i*60 + 15;
		w = 34;
		h = 28;
		frames[DRAWING_BAZOKA_FRAMES].push_back(Rect(x,y,w,h));
	}

	//frames for holding bazoka
	for (int i = 0; i < 32; i++) {
		x = 13;
		y = i*60  + 17;
		w = 34;
		h = 25;
		frames[HOLDING_BAZOKA_FRAMES].push_back(Rect(x,y,w,h));
	}


	//frames for drawing red grenade
	for (int i = 0; i < 10; i++)  {
		x = 18;
		y = 60*i + 16;
		w = 29;
		h = 27;
		frames[DRAWING_RG_FRAMES].push_back(Rect(x,y,w,h));
	}

	//frames for holding red grenade
	for (int i = 0; i < 32; i++) {
		x = 13;
		y = i * 60 + 12;
		w = 34;
		h = 31;
		frames[HOLDING_RG_FRAMES].push_back(Rect(x,y,w,h));
	}

	//drawing banana
	for (int i = 0; i < 10; i++) {
		x = 20;
		w = 32;
		y = 60 * i + 15;
		h = 27;
		frames[DRAWING_BANANA_FRAMES].push_back(Rect(x,y,w,h));
	}
	//holding banana
	for (int i = 0; i < 32; i++) {
		x = 13;
		y = i*60 + 15;
		w = 34;
		h = 27;
		frames[HOLDING_BANANA_FRAMES].push_back(Rect(x,y,w,h));
	}
	//frames for drawing  green grenademortar
	for (int i = 0; i < 10; i++)  {
		x = 18;
		y = 60*i + 16;
		w = 29;
		h = 27;
		frames[DRAWING_GG_FRAMES].push_back(Rect(x,y,w,h));
	}

	//frames for holding green grenade
	for (int i = 0; i < 32; i++) {
		x = 13;
		y = i * 60 + 12;
		w = 34;
		h = 31;
		frames[HOLDING_GG_FRAMES].push_back(Rect(x,y,w,h));
	}


		//frames for drawing mortar
	for (int i = 0; i < 7; i++) {
		x = 13;
		y = i*60 + 15;
		w = 34;
		h = 28;
		frames[DRAWING_MORTAR_FRAMES].push_back(Rect(x,y,w,h));
	}

	//frames for holding mortar
	for (int i = 0; i < 32; i++) {
		x = 13;
		y = i*60  + 17;
		w = 34;
		h = 25;
		frames[HOLDING_MORTAR_FRAMES].push_back(Rect(x,y,w,h));
	}

	//frames for drawing tp
	for (int i = 0; i < 10; i++) {
		x = 13;
		y = i*60 + 15;
		w = 28;
		h = 28;
		frames[DRAWING_TP_FRAMES].push_back(Rect(x,y,w,h));
	}

	//frames for holding tp
	for (int i = 4; i < 45; i += 2) {
		x = 13;
		y = i * 60 + 12;
		w = 29;
		h = 31;
		frames[HOLDING_TP_FRAMES].push_back(Rect(x,y,w,h));
	}

	for (int i = 44; i >= 4; i -= 2) {
		x = 13;
		y = i * 60 + 12;
		w = 29;
		h = 31;
		frames[HOLDING_TP_FRAMES].push_back(Rect(x,y,w,h));
	}

	//frames for when the worm's team won
	for (int i = 0; i < 14; i++) {
		x = 7;
		y = i * 60;
		w = 45;
		h = 45;
		frames[WWINNER_FRAMES].push_back(Rect(x,y,w,h));
	}


}

int WormView::shoot(int i) {
	int aux = angle;
	//toDefault(i);
	return aux;
}


void WormView::toDefault(int i) {
	if (currentFramesIndex == HOLDING_AXE_FRAMES ||
		currentFramesIndex == HOLDING_BAZOKA_FRAMES ||
		currentFramesIndex == HOLDING_RG_FRAMES ||
		currentFramesIndex == HOLDING_BANANA_FRAMES ||
		currentFramesIndex == HOLDING_GG_FRAMES ||
		currentFramesIndex == HOLDING_MORTAR_FRAMES || 
		currentFramesIndex == HOLDING_TP_FRAMES) {

		currentFramesIndex = STILL_FRAMES;
		this->startingPoint = i;
	}

	this->defaultFramesIndex = STILL_FRAMES;
}

void WormView::drawGreenGrenade(int i) {
	if (currentFramesIndex == DRAWING_GG_FRAMES ||
		currentFramesIndex == HOLDING_GG_FRAMES)
		return;
	this->startingPoint = i;
	this->currentFramesIndex = DRAWING_GG_FRAMES;
	this->defaultFramesIndex = HOLDING_GG_FRAMES;
}

void WormView::drawTp(int i) {
	if (currentFramesIndex == DRAWING_TP_FRAMES ||
		currentFramesIndex == HOLDING_TP_FRAMES)
		return;
	this->startingPoint = i;
	this->currentFramesIndex = DRAWING_TP_FRAMES;
	this->defaultFramesIndex = HOLDING_TP_FRAMES;
}

void WormView::drawBanana(int i) {
	if (currentFramesIndex == DRAWING_BANANA_FRAMES ||
		currentFramesIndex == HOLDING_BANANA_FRAMES)
		return;
	this->startingPoint = i;
	this->currentFramesIndex = DRAWING_BANANA_FRAMES;
	this->defaultFramesIndex = HOLDING_BANANA_FRAMES;
}

void WormView::drawRedGrenade(int i) {
	if (currentFramesIndex == DRAWING_RG_FRAMES ||
		currentFramesIndex == HOLDING_RG_FRAMES)
		return;
	this->startingPoint = i;
	this->currentFramesIndex = DRAWING_RG_FRAMES;
	this->defaultFramesIndex = HOLDING_RG_FRAMES;
}

void WormView::drawMortar(int i) {
	if (currentFramesIndex == DRAWING_MORTAR_FRAMES || 
		currentFramesIndex == HOLDING_MORTAR_FRAMES)
		return;
	this->startingPoint = i;
	this->currentFramesIndex = DRAWING_MORTAR_FRAMES;
	this->defaultFramesIndex = HOLDING_MORTAR_FRAMES;
}

void WormView::drawBazoka(int i) {
	if (currentFramesIndex == DRAWING_BAZOKA_FRAMES || 
		currentFramesIndex == HOLDING_BAZOKA_FRAMES)
		return;
	this->startingPoint = i;
	this->currentFramesIndex = DRAWING_BAZOKA_FRAMES;
	this->defaultFramesIndex = HOLDING_BAZOKA_FRAMES;
}

void WormView::drawAxe(int i) {
	if (currentFramesIndex == DRAWING_AXE_FRAMES ||
		currentFramesIndex == HOLDING_AXE_FRAMES)
		return;
	this->startingPoint = i;
	this->currentFramesIndex = DRAWING_AXE_FRAMES;
	this->defaultFramesIndex = HOLDING_AXE_FRAMES;
}

void WormView::jump(int i) {
	if (currentFramesIndex == JUMPING_FRAMES)
		return;
	this->startingPoint = i;
	this->currentFramesIndex = JUMPING_FRAMES;
}

void WormView::move(int i) {
	//if (currentFramesIndex != WALKING_FRAMES)
	//	return;
	if (currentFramesIndex != WALKING_FRAMES)
		this->startingPoint = i;
	this->currentFramesIndex = WALKING_FRAMES;
	this->defaultFramesIndex = WALKING_FRAMES;
}

void WormView::hit(int i) {
	if (currentFramesIndex == HITTING_FRAMES) 
		return;
	this->startingPoint = i;
	this->currentFramesIndex = HITTING_FRAMES;
	this->defaultFramesIndex = STILL_FRAMES;
}

void WormView::tp(int i) {
	if (currentFramesIndex == TPING_FRAMES)
		return;
	this->startingPoint = i;
	this->currentFramesIndex = TPING_FRAMES;
	this->defaultFramesIndex = STILL_FRAMES;
}

void WormView::surrend() {
	if (defaultFramesIndex == HOLDING_AXE_FRAMES ||
		defaultFramesIndex == HOLDING_BAZOKA_FRAMES ||
		defaultFramesIndex == HOLDING_RG_FRAMES ||
		defaultFramesIndex == HOLDING_BANANA_FRAMES ||
		defaultFramesIndex == HOLDING_GG_FRAMES ||
		defaultFramesIndex == HOLDING_MORTAR_FRAMES || 
		defaultFramesIndex == HOLDING_TP_FRAMES) {
			return;
		}
	this->defaultFramesIndex = SURRENDING_FRAMES;
}

void WormView::die() {
	if (currentFramesIndex == POSTMORTEM_FRAMES)
		return;
	this->currentFramesIndex = POSTMORTEM_FRAMES;
	this->defaultFramesIndex = POSTMORTEM_FRAMES;
}


void WormView::display(int i, Renderer& renderer, int camX, int camY, int mouseX, int mouseY) {
	size_t currentFrame;
	int flip;

	//si es un arma que estoy sosteniendo tengo que calcular los frames apuntando y la condicion de flip
	if (currentFramesIndex == HOLDING_AXE_FRAMES
		|| currentFramesIndex == HOLDING_BAZOKA_FRAMES
		|| currentFramesIndex == HOLDING_MORTAR_FRAMES
		|| currentFramesIndex == HOLDING_RG_FRAMES
		|| currentFramesIndex == HOLDING_BANANA_FRAMES
		|| currentFramesIndex == HOLDING_GG_FRAMES) {

		float dx = ((mouseX + camX) / m_to_pix_x) - this->worm.getX() ;
		float dy = ((mouseY + camY - WINDOW_HEIGHT) / m_to_pix_y) - this->worm.getY();

		flip = dx > 0 ? RIGHT_DIR : LEFT_DIR;

		if (dx == 0) {
			angle = 0;
		} else {
			angle = atan(dy / dx) * (180 / M_PI);
		}
		if (dx < 0) angle *= -1;
		
		/*
		ahora esta entre -90 y 90. tengo que mapear para ajustar al largo del frame de vectores actual.
		el cual tiene -90 en las primeras posiciones y 90 en las ultimas		
		*/

		currentFrame = (((angle + 90.0f) / 180.0f) * (this->frames[currentFramesIndex].size()));
	} else { //si es una animacion calculo en base al frame en el que estoy
		flip = worm.getDir();
		int animationSpeed = (currentFramesIndex == HOLDING_TP_FRAMES) ? 2 : 4;
		currentFrame = (i - startingPoint) / animationSpeed;

		if (currentFrame >= this->frames[currentFramesIndex].size()) {
			startingPoint = i;
			currentFramesIndex = defaultFramesIndex;
			currentFrame = 0;
		}
	}

	int x,y,w,h;
	if (currentFramesIndex != HITTING_FRAMES && 
		currentFramesIndex != DRAWING_AXE_FRAMES &&
		currentFramesIndex != HOLDING_AXE_FRAMES) {
		x = ((worm.getX() - 0.5)  * m_to_pix_x) - camX;
		y = ((worm.getY() + 0.5) * m_to_pix_y + WINDOW_HEIGHT) - camY;
		w = 1*m_to_pix_x;
		h = -1*m_to_pix_y;
	} else {
		x = (worm.getX() * m_to_pix_x - camX) - (this->frames[currentFramesIndex][currentFrame].GetW())/2;
		y = (worm.getY() * m_to_pix_y + WINDOW_HEIGHT - camY) - (this->frames[currentFramesIndex][currentFrame].GetH()/2);
		w = 3*m_to_pix_x;
		h = -3*m_to_pix_y;
	}
	Rect destiny(x,y,w,h);
		
	
	renderer.Copy(
		this->dynamicSpriteSheets[currentFramesIndex],
		this->frames[currentFramesIndex][currentFrame],
		destiny,
		0, NullOpt, flip
	);


	if (!this->worm.isAlive() || this->currentFramesIndex == WWINNER_FRAMES)
		return;

	//grafico la vida
	int team = this->worm.getTeam();
	uint8_t r, g, b;
	g = (team == 2) || (team == 4) ? 255 : 0;
	r = (team == 1) || (team == 4) ? 255 : 0;
	b = team == 3 ? 255 : 0;


	Texture hpContrast(renderer,
		wormsFont.RenderText_Solid(std::__cxx11::to_string(this->worm.getHealth()),
		SDL_BLACK_COLOR));	

	SDL_Color color{r,g,b};
	Texture hp(renderer,
		wormsFont.RenderText_Solid(std::__cxx11::to_string(this->worm.getHealth()),
		color));

	renderer.Copy(
		hpContrast,
		NullOpt,
		Rect(Point(x + 0.5*m_to_pix_x ,y - (.5 * - m_to_pix_y)) - Point(2,2), hp.GetSize() + Point(4,4))
	);

	renderer.Copy(
		hp,
		NullOpt,
		Rect(Point(x + 0.5*m_to_pix_x ,y - (.5 * - m_to_pix_y)), hp.GetSize())
	);

}

void WormView::update(WormDTO other, int i) {
	this->worm = other;

	if (worm.getVelX() == 0 && this->defaultFramesIndex == WALKING_FRAMES) {
		this->defaultFramesIndex = STILL_FRAMES;
		this->currentFramesIndex;
	}

	if (!(this->worm.isAlive())) {
		die();
	}

	if (this->worm.getHealth() <= 10)
		surrend();


}

void WormView::notifyWinner(int winnerTeam) {
	if (this->worm.getTeam() == winnerTeam && (defaultFramesIndex != WWINNER_FRAMES)) {
		currentFramesIndex = WWINNER_FRAMES;
		defaultFramesIndex = WWINNER_FRAMES;
	}
}


WormView::~WormView() {}