#ifndef BOOSTER_H
#define BOOSTER_H 1

#include "part.h"
#include "rocket.h"

class booster : public part {
private:
	float fuel;
	float thrust;
	bool firing;
	vec3 localup;
public:
	booster(rocket*, float, float);
	virtual void update();
	virtual float mass();
	virtual void print();
};

#endif