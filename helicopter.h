#pragma once
#ifndef HELICOPTER_H
#define HELICOPTER_H
#include "vec3.h"

class Helicopter {
private :
	float helicopterPropeller;
	float helicopterHeight;
	float helicopterX;
	float helicopterZ;
	float helicopterColRed;
	float helicopterColGreen;
	float helicopterColBlue;
	int ID;
	
public: 
	Helicopter(float x, float y, float z, float r, float g, float b);
	void DrawHelicopter();
	float getHelicopterHeight();
	float getHelicopterX();
	float getHelicopterZ();
	float getHelicopterColRed();
	float getHelicopterColGreen();
	float getHelicopterColBlue();
	void setHelicopterPropella(float value);
	void setHelicopterX(float x);
	void setHelicopterHeight(float y);
	void setHelicopterZ(float z);
	int getHelicopterID();
	void setHelicopterCol(float r, float g, float b);
	bool isHit(vec3 pos);
};

#endif