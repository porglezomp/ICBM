#include "rocket.h"
#include "constants.h"
#include "vecutil.h"
#include "graphicsmath0/graphicsmath.h"
#include "stdio.h"
#include "stdlib.h"
#include "physics.h"
#include "debug.h"

void rocket::update() {
	calcmass();
	gravity();
	drag();
	thrust();
	pos += vel * DELTATIME;
	collision();
	time += DELTATIME;
}

void rocket::print() {
	printf("Time: %02i:%02i:%02i:%02i\n", (int)(time/3600), (int)(time/60)%60, (int)(time)%60, (int)(time*60)%60);
	printf("	Velocity: %.4f\n", length(vel));
	printf("	Altitude: %.2f\n", altitude());
	printf("	"); printlatlon(pos);
	printf("	Fuel: %.2f\n", fuel);
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

		vel.z = .05;
	}
}

void rocket::thrust() {
	if (firing) {
		force(up * thrustforce);
		fuel -= .128;
	}
	if (fuel <= 0) {
		firing = false;
		fuel = 0;
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
	mass = emptymass + fuel*FUELMASS;
}

void rocket::fire(bool fstate) {
	firing = fstate;
}

rocket::rocket(const vec3 &pos, float f, float fuel, float m) : 
				pos(pos), up(normalize(vec3(.3, .2, 1))), vel(0), firing(false), thrustforce(f), emptymass(m),
				fuel(fuel) { }