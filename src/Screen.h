/*
 * Screen.h
 *
 *  Created on: 2015-12-04
 *      Author: mitali
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL.h>

namespace ParticleSimulator {

class Screen {
private:
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;
	Uint32 *m_buffer1;
	SDL_Event event;
	Uint32 *m_buffer2;

public:
	static const int SCREEN_WIDTH = 800; //Screen width
	static const int SCREEN_HEIGHT = 600; //Screen height
	Screen();
	bool init();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	void boxBlur();
	void update();
	bool processEvents();
	void close();
	virtual ~Screen();
};

} /* namespace ParticleSimulator */

#endif /* SCREEN_H_ */
