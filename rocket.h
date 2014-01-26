#ifndef ROCKET_H
#define ROCKET_H 1

#include "graphicsmath0/graphicsmath.h"
#include "vector"

class part;

class rocket {
	vec3 pos, up, vel;
	bool firing;
	float thrustforce, mass, emptymass;
	float time;
	std::vector<part*> parts;
public:
	mat3 orientation;
	rocket(const vec3&, float, float, float);
	void print();

	void update();
	void calcmass();
	void gravity();
	void collision();
	void drag();
		float dragcoef(float);
		float crosssection();
	
	void accel(const vec3&);
	void force(const vec3&);

	float altitude();

	void fire(bool);
	void addpart(part*);
};

#endif