#include "physics.h"
#include "map"

// Data about the atmosphere at a certain height
struct atmEntry {
	float density, H;
	atmEntry(float d, float H) : density(d), H(H) { } 
};

// A map for atmospheric data at altitudes (KM)
// Sourced from http://www.armscontrol.ru/course/articles/primer.pdf
std::map<int, atmEntry> rangemap;
rangemap densitymap;
densitymap[0] = atmEntry(1.225, 10.42);
densitymap[1] = atmEntry(1.122, 10.30);
densitymap[2] = atmEntry(1.007, 10.19);
densitymap[3] = atmEntry(0.909, 10.06);
densitymap[4] = atmEntry(0.819, 9.95);
densitymap[5] = atmEntry(0.763, 9.82);
densitymap[6] = atmEntry(0.660, 9.70);
densitymap[8] = atmEntry(0.526, 9.46);
densitymap[10] = atmEntry(0.414, 9.21);
densitymap[15] = atmEntry(0.195, 8.16);
densitymap[20] = 10;
densitymap[30] = 11;
densitymap[40] = 12;
densitymap[50] = 13;
densitymap[60] = 14;
densitymap[80] = 15;
densitymap[100] = 16;
densitymap[150] = 17;
densitymap[200] = 18;
densitymap[300] = 19;

float airdensity(float z) {
	if (z > 300) return 0;
	if (z < 0) return 1.225;
	return 
}