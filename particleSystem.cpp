#pragma warning(disable : 4786)

#include "particleSystem.h"


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <limits.h>

const float g = 9.8;
const float airDrag = -0.1293;

/***************
 * Constructors
 ***************/

ParticleSystem::ParticleSystem() 
{
	this->bake_fps = 30;
	this->bake_start_time = 0;
	this->bake_end_time = 0;
	this->dirty = false;
	this->simulate = false;
	this->points.clear();
	this->pointsToAdd.clear();
	this->lastTime = -1;
}





/*************
 * Destructor
 *************/

ParticleSystem::~ParticleSystem() 
{
	// TODO
	points.clear();
}


/******************
 * Simulation fxns
 ******************/

/** Start the simulation */
void ParticleSystem::startSimulation(float t)
{
	printf("start\n");
	// TODO
	clearBaked();
	bake_start_time = t;

	// These values are used by the UI ...
	// -ve bake_end_time indicates that simulation
	// is still progressing, and allows the
	// indicator window above the time slider
	// to correctly show the "baked" region
	// in grey.
	bake_end_time = -1;
	simulate = true;
	dirty = true;

}

/** Stop the simulation */
void ParticleSystem::stopSimulation(float t)
{
	printf("stop\n");
	// TODO
	bake_end_time = t;

	// These values are used by the UI
	simulate = false;
	dirty = true;

}

/** Reset the simulation */
void ParticleSystem::resetSimulation(float t)
{
    
	// TODO
	bake_start_time = bake_end_time = 0;
	lastTime = -1;

	// These values are used by the UI
	simulate = false;
	dirty = true;

}

/** Compute forces and update particles **/
void ParticleSystem::computeForcesAndUpdateParticles(float t)
{
	if (!simulate){
		return;
	}

	// Get previous points.
	vector<Particle> cur;
	if (!points.empty() && lastTime != -1) {
		cur = points[lastTime];
	}


	// Add points.
	for (int i = 0; i < pointsToAdd.size(); i++) {
		cur.push_back(pointsToAdd[i]);
	}
	pointsToAdd.clear();

	// Decrease life
	for (int i = 0; i < cur.size(); i++) {
		cur[i].decreaseLife(1 / bake_fps);
		if (cur[i].isDead()) {
			cur.erase(cur.begin() + i);
		}
	}

	// Calculate force and update pos and velocity
	for (int i = 0; i < cur.size(); i++) {
		Vec3f curForce;
		Vec3f gravity(0, - cur[i].mass * g, 0);
		Vec3f airResist(cur[i].velocity * airDrag);
		curForce += gravity;
		curForce += airResist;
		cur[i].force = curForce;
	}

	double timeQuantum = 1/bake_fps;
	for (int i = 0; i < cur.size(); i++) {
		Vec3f acceleration;
		acceleration = cur[i].force / cur[i].mass;
		Vec3f nextVel(cur[i].velocity);
		nextVel += acceleration * timeQuantum;
		Vec3f nextPos(cur[i].pos);
		nextPos += cur[i].velocity * timeQuantum;
		cur[i].pos = nextPos;
		cur[i].velocity = nextVel;
	}
	// Put cur into the map.
	lastTime = t;
	points[t] = cur;
}


/** Render particles */
void ParticleSystem::drawParticles(float t)
{
	if (points.empty()) {
		return;
	}
	map<double, vector<Particle>>::iterator it = points.find(t);
	if (!(t > bake_start_time && t < bake_end_time) && bake_end_time != -1) {
		return;
	}
	printf("enter draw\n");
	if (it == points.end()) {
		map<double, vector<Particle>>::iterator iter = points.begin();
		// Not exist.
		if (iter->first >= t) {
			return;
		}
		bool found = false;
		for (; iter != points.end(); iter++) {
			if (iter->first >= t) {
				t = iter->first;
				found = true;
				break;
			}
		}
		if (!found) {
			return;
		}
	}
	const vector<Particle>& cur = points[t];
	for (int i = 0; i < cur.size(); i++) {
		glPushMatrix();

		setAmbientColor(.1f, .1f, .1f);
		setDiffuseColor(0.596, 1, 0.596);

		glTranslatef(cur[i].pos[0], cur[i].pos[1], cur[i].pos[2]);
		drawSphere(0.1);

		glPopMatrix();
	}
}


void ParticleSystem::addPoint(Particle p) {
	pointsToAdd.push_back(p);
}

void ParticleSystem::clearBuffer() {
	pointsToAdd.clear();
}

/** Adds the current configuration of particles to
  * your data structure for storing baked particles **/
void ParticleSystem::bakeParticles(float t) 
{

	// TODO
}

/** Clears out your data structure of baked particles */
void ParticleSystem::clearBaked()
{
	points.clear();
	bake_start_time = lastTime;
	lastTime = -1;
}





