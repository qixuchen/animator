#ifndef PARTICLE_H
#define PARTICLE_H

#include "vec.h"
#include "mat.h"

class Particle {
public:
	Vec3f pos;
	Vec3f velocity;
	Vec3f force;
	double mass;
	double life;

	Particle(Vec3f pos, Vec3f velocity):pos(pos), velocity(velocity), mass(1), life(1.5) {

	}

	void decreaseLife(double quantum) {
		life -= quantum;
	}

	bool isDead() {
		return (life <= 0);
	}
};

#endif // !PARTICLE_H

