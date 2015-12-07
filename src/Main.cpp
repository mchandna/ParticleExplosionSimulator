//============================================================================
// Name        : Main.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
//============================================================================

#include <iostream>
#include <SDL2/SDL.h>
#include "Screen.h"
#include <Math.h>
#include <stdlib.h>
#include <time.h>
#include "Swarm.h"

using namespace ParticleSimulator;
using namespace std;

int main() {

	srand(time(NULL));
	static bool quit = false;

	Screen screen;

	if(screen.init() == false) {
		cout << "Error" << endl;
		return 1;
	}

	Swarm swarm;

    while(!quit) {
    	//Update particles
    	//Draw particles
    	//Listens for events
    	//Process event que

    	int timeElapsed = SDL_GetTicks();

    	swarm.update(timeElapsed);

    	unsigned char red = (unsigned char) ((1 + sin(timeElapsed * 0.0005)) * 128);
    	unsigned char green = (unsigned char) ((1 + sin(timeElapsed * 0.0010)) * 128);
    	unsigned char blue = (unsigned char) ((1 + sin(timeElapsed * 0.0015)) * 128);

    	const Particle * const pParticles = swarm.getParticles();

    	for(int i = 0; i < Swarm::NPARTICLES; i++) {
    		Particle particle = pParticles[i];

    		int x = (particle.m_x + 1)*(Screen::SCREEN_WIDTH/2);
    		int y = particle.m_y * Screen::SCREEN_WIDTH/2 + Screen::SCREEN_HEIGHT/2;

    		screen.setPixel(x, y, red, green, blue);
    	}

    	screen.boxBlur();

    	screen.update();

    	quit = screen.processEvents();
    }

    screen.close();

    return 0;
}
