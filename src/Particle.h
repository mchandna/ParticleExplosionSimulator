/*
 * Particle.h
 *
 *  Created on: 2015-12-05
 *      Author: mitali
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <stdlib.h>
namespace ParticleSimulator {

struct Particle {
	double m_x;
	double m_y; //By default public
private:
	double m_speed;
	double m_direction;
	void init();
public:
	Particle();
	void update(int interval);
	virtual ~Particle();
};

} /* namespace ParticleSimulator */

#endif /* PARTICLE_H_ */
