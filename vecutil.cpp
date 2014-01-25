#include "vecutil.h"
#include "graphicsmath0/vec2.h"
#include "graphicsmath0/vec3.h"
#include "graphicsmath0/vec4.h"
#include "stdio.h"
#include "math.h"

#define PI 3.141592654
#define RAD2DEG 180/PI
#define DEG2RAD PI/180

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
	char NvS = v.z > 0 ? 'N' : 'S';
	char EvW = v.y > 0 ? 'E' : 'W';
	float angle = acos(dot(normalize(v), vec3(0, 0, 1)))*RAD2DEG;
	float lat;
	if (angle < 90) lat = 90 - angle;
	else lat = angle - 90;
	float lon = acos(dot(normalize(v), vec3(1, 0, 0)))*RAD2DEG;
	printf("%f %cº, %f %cº\n", lat, NvS, lon, EvW);
}