#include "physics.h"
#include "math.h"
#include "stdio.h"

// Data about the atmosphere at a certain height
struct atmEntry {
	float altitude, density, H;
	atmEntry(float a, float d, float H) : altitude(a), density(d), H(H) { }
	atmEntry() : density(0), H(0) { }
};

// A map for atmospheric data at altitudes (KM)
// Sourced from http://www.armscontrol.ru/course/articles/primer.pdf
atmEntry *densitymap[301];

void interval(int start, int end, atmEntry *val) {
	for (int i = start; i < end; i++) {
		densitymap[i] = val;
	}
}

void initatmosphere() {
	// Fill the LUT
	interval(0, 1, new atmEntry(0, 1.225, 10.42));
	interval(1, 2, new atmEntry(1, 1.122, 10.30));
	interval(2, 3, new atmEntry(2, 1.007, 10.19));
	interval(3, 4, new atmEntry(3, 0.909, 10.06));
	interval(4, 5, new atmEntry(4, 0.819, 9.95));
	interval(5, 6, new atmEntry(5, 0.763, 9.82));
	interval(6, 8, new atmEntry(6, 0.660, 9.70));
	interval(8, 10, new atmEntry(8, 0.526, 9.46));
	interval(10, 15, new atmEntry(10, 0.414, 9.21));
	interval(15, 20, new atmEntry(15, 0.195, 8.16));
	interval(20, 30, new atmEntry(20, 0.0889, 7.62));
	interval(30, 40, new atmEntry(30, 0.0184, 7.15));
	interval(40, 50, new atmEntry(40, 0.0040, 6.99));
	interval(50, 60, new atmEntry(50, 0.00103, 7.06));
	interval(60, 80, new atmEntry(60, 3.10E-4, 7.24));
	interval(80, 100, new atmEntry(80, 1.85E-5, 7.20));
	interval(100, 150, new atmEntry(100, 5.60E-7, 6.85));
	interval(150, 200, new atmEntry(150, 2.08E-9, 7.43));
	interval(200, 300, new atmEntry(200, 2.54E-10, 8.97));
	interval(300, 301, new atmEntry(300, 1.92E-11, 12.06));
}

float airdensity(float z) {
	z /= 1000;
	if (z > 300) return 0;
	if (z < 0) return 1.225;
	atmEntry a = *densitymap[int(z)];
	return a.density*exp(-(z-a.altitude)/a.H);
}