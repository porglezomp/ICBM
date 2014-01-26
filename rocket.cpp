#include "rocket.h"
#include "constants.h"
#include "vecutil.h"
#include "graphicsmath0/graphicsmath.h"
#include "stdio.h"
#include "stdlib.h"
#include "physics.h"
#include "debug.h"
#include "part.h"

void rocket::update() {
	calcmass();
	for (int i = 0; i < parts.size(); i++) {
		parts[i]->update();
	}
	gravity();
	drag();
	pos += vel * DELTATIME;
	collision();
	time += DELTATIME;
}

void rocket::print() {
	printf("Time: %02i:%02i:%02i:%02i\n", (int)(time/3600), (int)(time/60)%60, (int)(time)%60, (int)(time*60)%60);
	for (int i = 0; i < parts.size(); i++) {
		parts[i]->print();
	}
	printf("	Velocity: %.4f\n", length(vel));
	printf("	Altitude: %.2f\n", altitude());
	printf("	"); printlatlon(pos);
	DEBUG(printf("	Air density: %f\n", airdensity(altitude())));
	DEBUG(printf("	Mass: %f\n", mass));
	DEBUG(float v = length(vel); printf("	Drag: %f\n", v * v * .5 * crosssection() * airdensity(altitude()) * dragcoef(v)));
}

void rocket::collision() {
	if (altitude() < 0) {
		if (length(vel) > 10) {
			print();
			printf("You crashed going really fast. (%f m/s)\n", length(vel));
			exit(1);
		}
		pos = normalize(pos)*R_EARTH;
		vel = 0;
	}
}

void rocket::drag() {
	vec3 dragforce = -vel;
	float v = length(vel);
	dragforce *= .5 * crosssection() * airdensity(altitude()) * dragcoef(v) * v;
	force(dragforce);
}

float rocket::crosssection() {
	return 2.2698;
}
float rocket::dragcoef(float s) {
	return .2;
}

void rocket::accel(const vec3 &a) {
	vel += a * DELTATIME;
}
void rocket::force(const vec3 &a) {
	vel += a * DELTATIME / mass;
}

float rocket::altitude() {
	return length(pos)-R_EARTH;
}


void rocket::gravity() {
	float r = length(pos);
	accel(-pos * (G_PARAM / (r*r*r)));
}

void rocket::calcmass() {
	mass = emptymass;
	for (int i = 0; i < parts.size(); i++) {
		mass += parts[i]->mass();
	}
}

void rocket::fire(bool fstate) {
	firing = fstate;
}

void rocket::addpart(part *p) {
	parts.push_back(p);
}

rocket::rocket(const vec3 &pos, float f, float fuel, float m) : 
				pos(pos), up(normalize(vec3(.1, 1, 0))), vel(0), firing(false), thrustforce(f), emptymass(m)
{ 
	orientation = mat3::identity();
}