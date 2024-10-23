#pragma once
#ifndef TANK_H
#define TANK_H
#include "vec3.h"

class Tank {
	private :
		float tankX;
		float tankY;
		float tankZ;
		float tankColRed;
		float tankColGreen;
		float tankColBlue;
		int ID;
	public:
		Tank(float x, float y, float z, float r, float g, float b);
		void setTankX(float value);
		void DrawTank(float time, float hy);
		float getTankX();
		float getTankY();
		float getTankZ();
		float getTankColRed();
		float getTankColGreen();
		float getTankColBlue();
		int getTankID();
		void setTankCol(float r, float g, float b);
		bool isHit(vec3 pos);
};


#endif