#ifndef VECUTIL_H
#define VECUTIL_H 1

struct vec2;
struct vec3;
struct vec4;

/*
 * @brief prints a vector
 * This method formats and prints a vector, then a newline
 * @param The vector to be printed
 */
void printvec(const vec2&);
/// @overload
void printvec(const vec3&);
/// @overload
void printvec(const vec4&);

/*
 * @brief prints a vector inline
 * This method formats and prints a vector without printing a newline
 * @param The vector to be printed 
 */
void printveci(const vec2&);
/// @overload
void printveci(const vec3&);
/// @overload
void printveci(const vec4&);

/*
 * @brief print the latitude and longitude of a point
 * This function takes a vector and calculates the latitude and longitude of the point.
 * It assumes that +Z is at the north pole, and +X at the prime meridian on the equator.
 * The output is in the form "angleº N/S, angleº E/W"
 * @param The vector to display lat/lon for
 */
void printlatlon(const vec3&);


#endif