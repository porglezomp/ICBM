#include "booster.h"
#include "part.h"
#include "constants.h"

booster::booster(rocket *r, float f, float t) : part(r), fuel(f), thrust(t), firing(true) { 
	localup = vec3(0, 1, 0);
}

void booster::update() {
	// part::update();
	if (firing && fuel > 0) {
		parent->force(localup*parent->orientation * thrust);
		fuel -= .128;
	}
	if (fuel <= 0) {
		firing = false;
		fuel = 0;
	}
}

float booster::mass() {
	return 10 + fuel * FUELMASS;
}

void booster::print() {
	printf("	Fuel: %.2fL\n", fuel);
}