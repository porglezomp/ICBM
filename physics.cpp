#include "physics.h"
#include "map"

// Data about the atmosphere at a certain height
struct atmEntry {
	float alt, density, H;
};

std::map<int, int> rangemap;
rangemap densitymap;


float airdensity(float z) {
	if (z > 300) return 0;
}