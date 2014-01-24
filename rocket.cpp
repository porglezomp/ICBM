#include "rocket.h"
#include "constants.h"
#include "vecutil.h"
#include "graphicsmath0/graphicsmath.h"
#include "stdio.h"
#include "stdlib.h"

void rocket::update() {
	calcmass();
	gravity();
	thrust();
	pos += vel * DELTATIME;
	collision();
	time += DELTATIME;
}

void rocket::print() {
	printf("Time: %02i:%02i:%02i:%02i\n", (int)(time/3600), (int)(time/60)%60, (int)(time)%60, (int)(time*60)%60);
	printf("	Velocity: %.4f\n", length(vel));
	printf("	Altitude: %.2f\n", length(pos) - R_EARTH);
	printf("	"); printlatlon(pos);
	printf("	Fuel: %.2f\n", fuel);
	printf("	Mass: %f\n", mass);
}

void rocket::collision() {
	if (pos.z < R_EARTH) {
		if (length(vel) > 10) {
			print();
			printf("You crashed going really fast. (%f m/s)\n", length(vel));
			exit(1);
		}
		pos.z = R_EARTH;
		vel.z = .05;
	}
}

void rocket::thrust() {
	if (firing) {
		accel(up * force / mass);
		fuel -= .128;
	}
	if (fuel <= 0) {
		firing = false;
		fuel = 0;
	}
}

void rocket::drag() {
	vec3 force = -vel;
	float v = length(vel);
	force *= .5 * crosssection() * airdensity(pos) * dragcoef(v) * v;
}

void rocket::crosssection() {
	return 2.2698;
}
void rocket::dragcoef(float s) {
	
}

void rocket::accel(const vec3 &a) {
	vel += a * DELTATIME;
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
				pos(pos), up(vec3(0, 0, 1)), vel(0), firing(false), force(f), emptymass(m),
				fuel(fuel) { }