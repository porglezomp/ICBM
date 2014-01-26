#include "stdio.h"
#include "graphicsmath0/graphicsmath.h"
#include "vecutil.h"
#include "rocket.h"
#include "constants.h"
#include "physics.h"
#include "debug.h"
#include "booster.h"

#ifdef _WIN32
#include "windows.h"
inline void delay(unsigned long ms) {
	Sleep(ms);
}
#else
#include "unistd.h"
inline void delay(unsigned long ms) {
	usleep(ms*1000);
}
#endif



rocket r = rocket(vec3(0, R_EARTH, 0), 20000, 100, 100);

int main(int argc, char const *argv[]) {
	initatmosphere();
	FILE *f = fopen("atmosphere2.txt", "w");
	for (float i = 0; i < 300000; i += 10) {
		fprintf(f, "%f\n", airdensity(i));
	}
	fclose(f);
	printf("Simulation began:\n");
	r.addpart(new booster(&r, 100, 20000));
	r.addpart(new booster(&r, 100, 20000));
	r.addpart(new booster(&r, 100, 20000));
	r.print();
	r.fire(true);
	while (true) {
		r.update();
		r.print();
		delay(1000*DELTATIME);
	}
	return 0;
}