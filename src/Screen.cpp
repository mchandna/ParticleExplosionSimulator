/*
 * Screen.cpp
 *
 *  Created on: 2015-12-04
 *      Author: mitali
 */

#include "Screen.h"

namespace ParticleSimulator {

Screen::Screen() { //Won't do initializations because can't return from constructor
	m_window = NULL;
	m_renderer = NULL;
	m_texture = NULL;
	m_buffer1 = NULL;
	m_buffer2 = NULL;
}

bool Screen::init() {
	//SDL_Init initializes and returns 0
	    if(SDL_Init(SDL_INIT_VIDEO) < 0 ) { //Try  to initialize screen
	    	return false;
	    }

	    //Creating SDL Window
	    //Param: Window title, x position of window, y position of window, width of window, height of window, display of window
	    m_window = SDL_CreateWindow("Particle Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	    //If window null just stop the program after clean up and outputting the error
	    if(m_window == NULL) {
	    	SDL_Quit(); //Cleanup
	    	return false;
	    }

	    //Create Renderer to render images on screen
	    //Param: window title to attach to renderer, index of renderer to initialize, synchronized with refresh rate of screen
	    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);

	    //If renderer is null just stop program after destroying window, cleanup and outputting error
	    if(m_renderer == NULL) {
	    		SDL_DestroyWindow(m_window);
	    		SDL_Quit();
	        	return false;
	        }

	    //Create Texturer to generate images to send to renderer
	    //Param: renderer name, format of declaration of pixels, rarely changing, width of pixels, height of pixels
	    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	    //If texturer is null just stop program after destroying renderer, window, cleanup and outputting error
	    if(m_renderer == NULL) {
	    		SDL_DestroyRenderer(m_renderer);
	    		SDL_DestroyWindow(m_window);
	        	SDL_Quit();
	        	return false;
	        }

	    //Array of Uint32 called buffer
	    //Each pixel is an element in the array
	    m_buffer1 = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];
	    m_buffer2 = new Uint32[SCREEN_WIDTH*SCREEN_HEIGHT];

	    //Setting memory for the pixels
	    //Param: memory for buffer
	    memset(m_buffer1, 0, sizeof(Uint32)*SCREEN_WIDTH*SCREEN_HEIGHT);
	    memset(m_buffer2, 0, sizeof(Uint32)*SCREEN_WIDTH*SCREEN_HEIGHT);

	    //Acts like memset but doing it pixel by pixel
//	    for(int i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++) {
//	    	if(i%2 == 0) {
//	    		m_buffer[i] = 0x00; //Acts same as memset but pixel by pixel
//	    	}
//	    }

	return true;
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

	if(x < 0 || x >= Screen::SCREEN_WIDTH || y < 0 || y >= Screen::SCREEN_HEIGHT) {
		return;
	}

	Uint32 color = 0;
	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xFF; //Alpha opaque

	//Set colour of pixel
	m_buffer1[(y * SCREEN_WIDTH) + x] = color; //rows then columns
}

void Screen::update() {
    SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH*sizeof(Uint32));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);
}

void Screen::boxBlur() {
	//Swap buffers
	Uint32 *temp = m_buffer1;
	m_buffer1 = m_buffer2;
	m_buffer2 = temp;

	for(int y = 0; y < SCREEN_HEIGHT; y++) {
		for(int x = 0; x < SCREEN_WIDTH; x++) {

			/*
			* 0 0 0
			* 0 1 0
			* 0 0 0
			*/

			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			for(int row = -1; row <= 1; row++) {
				for(int col = -1; col <= 1; col++) {
					int currentx = x + col;
					int currenty = y + row;

					if(currentx >= 0 && currentx < SCREEN_WIDTH && currenty >= 0 && currenty < SCREEN_HEIGHT) {
						Uint32 colour = m_buffer2[currenty*SCREEN_WIDTH + currentx];

						Uint8 red = colour >> 24;
						Uint8 green = colour >> 16;
						Uint8 blue = colour >> 8;

						redTotal += red;
						greenTotal += green;
						blueTotal += blue;
					}
				}
			}

			Uint8 red = redTotal/9;
			Uint8 green = greenTotal/9;
			Uint8 blue = blueTotal/9;

			setPixel(x, y, red, green, blue);
		}
	}
}

bool Screen::processEvents() {
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			return true;
		}
		return false;
	}
}

void Screen::close() {
	//Deallocate memory
		    delete[] m_buffer1;
		    delete[] m_buffer2 ;

		    //Destroy texturer
		    SDL_DestroyTexture(m_texture);

		    //Destroy renderer
		    SDL_DestroyRenderer(m_renderer);

		    //Destroy window
		    SDL_DestroyWindow(m_window);

		    //Cleanup
		    SDL_Quit();
}

Screen::~Screen() {
	// TODO Auto-generated destructor stub
}

} /* namespace ParticleSimulator */
