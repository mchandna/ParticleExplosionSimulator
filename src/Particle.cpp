/*
 * Particle.cpp
 *
 *  Created on: 2015-12-05
 *      Author: mitali
 */

#include "Particle.h"
#include <Math.h>
#include <stdlib.h>

namespace ParticleSimulator {

Particle::Particle() {

	init();
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

void Particle::init() {
	m_x = 0;
	m_y = 0;
	m_direction = (2 *  M_PI * rand())/RAND_MAX;
	m_speed = (0.06 * rand())/RAND_MAX;

	m_speed *= m_speed;
}

void Particle::update(int interval) {

	m_direction += (interval*0.0003);
	double xspeed = m_speed * cos(m_direction);
	double yspeed = m_speed * sin(m_direction);
	m_x += xspeed * interval;
	m_y += yspeed * interval;

	if(m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1) {
		init();
	}

	if(rand() < RAND_MAX/100) {
		init();
	}
}

} /* namespace ParticleSimulator */
