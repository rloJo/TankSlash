#include "helicopter.h"
#include <GL/glut.h>

Helicopter:: Helicopter(float x, float y, float z, float r, float g, float b) :
	helicopterX(x), helicopterHeight(y), helicopterZ(z),
	helicopterColRed(r), helicopterColGreen(g), helicopterColBlue(b), 
	helicopterPropeller(0), ID(1)
{}

float Helicopter::getHelicopterColRed() {
	return helicopterColRed;
}

void Helicopter::setHelicopterX(float x) {
	helicopterX += x;
}


void Helicopter::setHelicopterHeight(float y) {
	helicopterHeight += y;
}


void Helicopter::setHelicopterZ(float z) {
	helicopterZ += z;
}

float Helicopter :: getHelicopterColGreen(){
	return helicopterColGreen;
}

float Helicopter::getHelicopterColBlue() {
	return helicopterColBlue;
}

float Helicopter::getHelicopterX() {
	return helicopterX;
}

float Helicopter::getHelicopterHeight() {
	return helicopterHeight;
}

float Helicopter::getHelicopterZ() {
	return helicopterZ;
}

int Helicopter::getHelicopterID() {
	return  ID;
}

void Helicopter :: setHelicopterPropella(float value) {
	helicopterPropeller += value;
}

void Helicopter::setHelicopterCol(float r, float g, float b) {
	helicopterColRed = r;
	helicopterColGreen = g;
	helicopterColBlue = b;
}


bool Helicopter::isHit(vec3 pos) {
	int x = helicopterX;
	int y = helicopterHeight;
	int z = helicopterZ;
	vec3 helicopterSpot(x, y, z);
	vec3 diff = helicopterSpot - pos;
	if (diff.Length() < 1.5) return true;
	return false;
}


void Helicopter::DrawHelicopter() {
	glPushMatrix();
		glTranslatef(helicopterX, helicopterHeight, helicopterZ); //헬기의 기본 위치
		glPushMatrix(); //헬기 몸통 시작
			glutSolidCube(1.5);
			glPushMatrix(); //다리 지지대 1
				glTranslatef(0.5, -1, 0);
				glRotatef(90, 0, 1, 0);
				glPushMatrix();
					glScalef(0.1, 0.4, 0.1);
					glutSolidCube(2);
				glPopMatrix();
				glPushMatrix(); //다리1
					glTranslatef(0, -0.5, 0);
					glPushMatrix();
						glScalef(1, 0.1, 0.1);
						glutSolidCube(2);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			glPushMatrix(); //다리 지지대 2
				glTranslatef(-0.5, -1, 0);
				glRotatef(90, 0, 1, 0);
				glPushMatrix();
					glScalef(0.1, 0.4, 0.1);
					glutSolidCube(2);
				glPopMatrix();
				glPushMatrix(); //다리2
				glTranslatef(0, -0.5, 0);
				glPushMatrix();
					glScalef(1, 0.1, 0.1);
					glutSolidCube(2);
				glPopMatrix();
			glPopMatrix();
			glPushMatrix(); //헬기 꼬리 시작
				glTranslatef(-2, 1, 0.5);
				glRotatef(90, 0, 0, 1);
				glPushMatrix();
					glScalef(0.1, 1, 0.1);
					glutSolidCube(3);
				glPopMatrix();
				glPushMatrix(); //꼬리 프로펠러
					glTranslatef(0.0, 1, 0.3);
					glRotatef(10 * helicopterPropeller, 0, 0, 1);
					glPushMatrix();
						glScalef(0.1, 0.5, 0.1);
						glutSolidCube(2);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();// 메인 프로펠러 지지대
				glTranslated(0, 2, 0.5);
				glPushMatrix();
					glScalef(0.1, 1, 0.1);
					glutSolidCube(1.5);
				glPopMatrix();
				glPushMatrix();//메인 프로펠러
					glTranslated(0, 0.7, 0);
					glRotatef(90, 0, 0, 1);
					glRotatef(10 * helicopterPropeller, 1, 0, 0);
					glPushMatrix();
						glScalef(0.01, 0.5, 0.01);
						glutSolidCube(10);
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
	glPopMatrix();
}