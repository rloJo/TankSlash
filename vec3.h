#pragma once
#ifndef VEC3_H
#define VEC_H

class vec3 {
public :
	float val[3];
	vec3(float x =0, float y=0, float z=0);
	vec3 operator+ (vec3 x);
	vec3 operator- (vec3 x);
	vec3 operator* (float x);
	float Length();
};

#endif // !VEC3_H
