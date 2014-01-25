#ifndef ROCKET_H
#define ROCKET_H 1

#include "graphicsmath0/vec3.h"

class rocket {
	vec3 pos, up, vel;
	bool firing;
	float thrustforce, fuel, mass, emptymass;
	float time;
public:
	rocket(const vec3&, float, float, float);
	void print();

	void update();
	void calcmass();
	void gravity();
	void collision();
	void thrust();
	void drag();
		float dragcoef(float);
		float crosssection();
	
	void accel(const vec3&);
	void force(const vec3&);

	float altitude();

	void fire(bool);
};

#endif