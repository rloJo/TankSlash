#include "vec3.h"
#include <math.h>

vec3::vec3(float x, float y, float z ) {
	val[0] = x;
	val[1] = y;
	val[2] = z;
}

vec3 vec3 :: operator+ (vec3 x) {
	return vec3(val[0] + x.val[0],
		val[1] + x.val[1],
		val[2] + x.val[2]);
}
vec3 vec3:: operator- (vec3 x) {
	return vec3(val[0] - x.val[0],
		val[1] - x.val[1],
		val[2] - x.val[2]);
}

vec3 vec3 :: operator* (float x) {
	return vec3(val[0] * x,
		val[1] * x, 
		val[2] * x);
}

float vec3 :: Length() {
	return sqrtf(val[0] * val[0] + val[1] * val[1] + val[2] * val[2]);
}