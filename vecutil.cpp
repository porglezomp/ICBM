#include "vecutil.h"
#include "graphicsmath0/vec2.h"
#include "graphicsmath0/vec3.h"
#include "graphicsmath0/vec4.h"
#include "stdio.h"
#include "math.h"

void printvec(const vec2 &v) {
	printf("<%.2f, %.2f>\n", v.x, v.y);
}
void printvec(const vec3 &v) {
	printf("<%.2f, %.2f, %.2f>\n", v.x, v.y, v.z);
}
void printvec(const vec4 &v) {
	printf("<%.2f, %.2f, %.2f, %.2f>\n", v.x, v.y, v.z, v.w);
}

void printveci(const vec2 &v) {
	printf("<%.2f, %.2f>", v.x, v.y);
}
void printveci(const vec3 &v) {
	printf("<%.2f, %.2f, %.2f>", v.x, v.y, v.z);
}
void printveci(const vec4 &v) {
	printf("<%.2f, %.2f, %.2f, %.2f>", v.x, v.y, v.z, v.w);
}

void printlatlon(const vec3 &v) {
	char NvS = 'N';
	char EvW = 'W';
	float lat = 1.0;
	float lon = 1.0;
	printf("%f %cº, %f %cº\n", lat, NvS, lon, EvW);
}