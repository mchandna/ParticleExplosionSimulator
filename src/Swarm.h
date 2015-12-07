/*
 * Swarm.h
 *
 *  Created on: 2015-12-05
 *      Author: mitali
 */

#ifndef SWARM_H_
#define SWARM_H_

#include "Particle.h"

namespace ParticleSimulator {

class Swarm {
private:
	Particle *m_pParticles;
	int lastTime;
public:
	static const int NPARTICLES = 7000;
	Swarm();
	const Particle * const getParticles() { return m_pParticles; };
	void update(int elapsed);
	virtual ~Swarm();
};

} /* namespace ParticleSimulator */

#endif /* SWARM_H_ */
