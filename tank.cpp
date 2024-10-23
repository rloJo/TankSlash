#include "tank.h"
#include <GL/glut.h>
#include <math.h>

Tank::Tank(float x, float y, float z, float r, float g, float b) :
	tankX(x), tankY(y), tankZ(z),
	tankColRed(r), tankColGreen(g), tankColBlue(b),
	ID(2)
{}

void Tank::setTankX(float value) {
	tankX = value;
}

float Tank::getTankColRed() {
	return tankColRed;
}


float Tank::getTankColGreen() {
	return tankColGreen;
}

float Tank ::getTankColBlue() {
	return tankColBlue;
}

void Tank :: setTankCol(float r, float g, float b) {
	tankColRed = r;
	tankColGreen = g;
	tankColBlue = b;
}

float Tank::getTankX() {
	return tankX;
}

float Tank::getTankY() {
	return tankY;
}

float Tank::getTankZ() {
	return tankZ;
}

int Tank::getTankID() {
	return  ID;
}

bool Tank::isHit(vec3 pos) {
	int x = tankX;
	int y = tankY;
	int z = tankZ;
	vec3 tankSpot(x, y, z);
	vec3 diff = tankSpot - pos;
	if (diff.Length() < 3) return true;
	return false;
}

void Tank::DrawTank(float time, float hy) {
	glPushMatrix(); //ÅÊÅ© ±×¸®±â
		glTranslatef(sin(time * 0.0001) * 7 - 1, tankY, tankZ);
		glPushMatrix();  //ÅÊÅ©ÀÇ ÇÏºÎ ¸öÅë
			glPushMatrix();
				glScalef(1, 0.4, 1);
				glutSolidCube(4);
			glPopMatrix();
			glPushMatrix(); //¹ÙÄû 1
				glTranslatef(1.0, -1.3, 1.7);
				glutSolidSphere(0.5, 20, 20);
			glPopMatrix();
			glPushMatrix(); //¹ÙÄû 2
				glTranslatef(-1, -1.3, 1.7);
				glutSolidSphere(0.5, 20, 20);
			glPopMatrix();
			glPushMatrix(); //¹ÙÄû 3
				glTranslatef(1.0, -1.3, -1.7);
				glutSolidSphere(0.5, 20, 20);
			glPopMatrix();
			glPushMatrix(); //¹ÙÄû 4;
				glTranslatef(-1.0, -1.3, -1.7);
				glutSolidSphere(0.5, 20, 20);
			glPopMatrix();
			glPushMatrix(); //ÅÊÅ©ÀÇ »ó´Ü ¸öÅë
				glTranslatef(0.5, 1.3, 0);
				glRotated(90, 0, 1, 0);
				glutSolidSphere(1.0, 20, 20);
				glPushMatrix(); //Æ÷½Å ½ÃÀÛ
					glRotatef(90, 0, 0, 1);
					glRotatef(-sin(hy * 0.1) * 30, 0, 0, 1);
					glTranslatef(0, 1.5, 0);
					glPushMatrix();
						glScalef(0.1, 1, 0.1);
						glutSolidCube(3);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}