#include "helicopter.h"
#include "vec3.h"
#include "tank.h"
#include "bomb.h"
#include <GL/glut.h>
#include <vector>
#include <math.h>

using namespace std;

int MX = 300;
int MY = 300;
float g = 0; //����� ���� �������� �̻����� ���� �ʾ� ���� �߰�
int countMissile = 0;
float time = 0;

Helicopter helicopter(0, 5, 13, 0.4, 0.5, 0.4);
Tank tank((float) sin(time * 0.0001) * 7 - 1, 2, -14, 0, 0.5, 0.4);

vector<Bomb> bombs;
vector<Bomb> missiles;

//���콺�� ȭ�� ��ȯ
void MouseMove(GLint X, GLint Y)
{
	MX = X;
	MY = Y;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(MX / 300.0, MY / 300.0, 1.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
	glutPostRedisplay();
}

void CheckHeight() //����� ���� üũ�ϴ� �Լ�
{
	int hy = helicopter.getHelicopterHeight();

	if (hy >= 12.5) g = 5.5;
	else if (hy > 10) g = 5;
	else if (hy >= 7.5) g = 2.5;
	else g = 0;
}

void helicopterMove(int key, int mouseX, int mouseY) {
	float hx = helicopter.getHelicopterX();
	float hy = helicopter.getHelicopterHeight();
	if (key == GLUT_KEY_UP) {
		if (hy < 13)  helicopter.setHelicopterHeight(0.5);
	}

	if (key == GLUT_KEY_DOWN) {
		if (hy > 5) helicopter.setHelicopterHeight(-0.5);
	}

	if (key == GLUT_KEY_LEFT) {
		if (hx > -10)  helicopter.setHelicopterX(-0.5);
	}

	if (key == GLUT_KEY_RIGHT) {
		if (hx < 10)  helicopter.setHelicopterX(0.5);
	}
	glutPostRedisplay();
}

void BombPressed(unsigned char KeyPressed, int X, int Y) {
	if (KeyPressed == ' ' && bombs.size() < 5) { //space bar�� ������ ��⿡�� ��ź �߻� ��ź�� 5������ ��������
		Bomb sb;
		sb.pos.val[0] = helicopter.getHelicopterX();
		sb.pos.val[1] = helicopter.getHelicopterHeight() - 1;
		sb.pos.val[2] = helicopter.getHelicopterZ();
		sb.v.val[0] = 0;
		sb.v.val[1] = -1.5;
		sb.v.val[2] = 0;
		bombs.push_back(sb);
		glutPostRedisplay();
	}

}

void CreateMissile() {  //�̻����� �����ϴ� �Լ�
	countMissile = 0;
	Bomb sb;
	sb.pos.val[0] = sin(time * 0.0001) * 7 - 1;
	sb.pos.val[1] = 3 * (sin(helicopter.getHelicopterHeight() * 0.1)) + 2;
	sb.pos.val[2] = tank.getTankZ() + 3;
	sb.v.val[0] = 0;
	sb.v.val[1] = 1.5;
	sb.v.val[2] = -1.5;
	missiles.push_back(sb);
}

// �ݺ����� ó���� ���� Ÿ�̸� �̺�Ʈ �޼ҵ�
// ��� �����緯 �� ��ũ X��ġ �̵� ó��
void TimerEvent (int Value) {
	time += 10;
	helicopter.setHelicopterPropella(1);
	tank.setTankX(sin(time * 0.0001) * 7 - 1);
	glutPostRedisplay();
	glutTimerFunc(1, TimerEvent, 1);
	// �ֱ����� ȣ���� ���� �ڱ� �ڽ� ȣ��
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15.0, 15.0, -15.0, 15.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(MX / 300.0, MY / 300.0, 1.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
}

void InitLight(int n) {
	GLfloat mat_diffuse_ground[] = { 0.5, 0.3, 0.0, 1.0 };
	GLfloat mat_specular_ground[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient_ground[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess_ground[] = { 15.0 };

	GLfloat mat_diffuse_helicopter[] = { helicopter.getHelicopterColRed(), 
											helicopter.getHelicopterColGreen(), 
											helicopter.getHelicopterColBlue(), 1.0};
	GLfloat mat_specular_helicopter[] = { 0.0, 0.0, 0.8, 1.0 };
	GLfloat mat_ambient_helicopter[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat mat_shininess_helicopter[] = { 15.0 };

	GLfloat mat_diffuse_bomb[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_specular_bomb[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat mat_ambient_bomb[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat mat_shiniess_bomb[] = { 15.0 };

	GLfloat mat_diffuse_tank[] = { tank.getTankColRed(),
									tank.getTankColGreen(),
									tank.getTankColBlue(), 1.0};
	GLfloat mat_specular_tank[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient_tank[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess_tank[] = { 15.0 };

	GLfloat mat_diffuse_missile[] = { 0.8, 0.0, 0.3, 1.0 };
	GLfloat mat_specular_missile[] = { 0.7, 0.0, 0.2, 1.0 };
	GLfloat mat_ambient_missile[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess_missile[] = { 30.0 };

	GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 15.0 };
	GLfloat light_specular[] = { 1.0, 0.8, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_position[] = { -3, 6, 3.0, 0.0 };

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	switch (n) //��ü���� �ٸ� ���� ���������� ����ġ�� ���
	{
	case 0:
	default: //���� ��(����)
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_ground);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_ground);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_ground);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_ground);
		break;
	case 1: //����� ��(����)
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_helicopter);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_helicopter);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_helicopter);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_helicopter);
		break;
	case 2: //��ũ�� ��(����)
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_tank);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_tank);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_tank);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_tank);
		break;
	case 3: //��ź�� ��(����)
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_bomb);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_bomb);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_bomb);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiniess_bomb);
		break;

	case 4: //�̻����� ��(����)
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse_missile);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_missile);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_missile);
		glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess_missile);
		break;

	}
	glEnable(GL_NORMALIZE);
}

bool tankHitCheck() //��ũ�� �¾Ҵ��� üũ
{
	int b_size = bombs.size();
	for (int i = 0; i < b_size; i++)
		if (tank.isHit(bombs[i].pos)) return true;

	return false;
}

bool HeliHitCheck() //��Ⱑ �¾Ҵ��� üũ
{
	int m_size = missiles.size();
	for (int i = 0; i < m_size; i++)
		if (helicopter.isHit(missiles[i].pos)) return true;

	return false;
}

void UpdateMissiles() { //�̻��� ��ǥ ������Ʈ
	CheckHeight();
	vec3 acc(0, g, 30);
	float missileTime = 0.001;
	int size = missiles.size();
	for (int i = 0; i < size; i++) {
		missiles[i].v = missiles[i].v + (acc * missileTime);
		missiles[i].pos = missiles[i].pos + missiles[i].v * missileTime;
	}

	for (int i = 0; i < missiles.size(); ) {
		if (missiles[i].pos.val[2] > helicopter.getHelicopterZ())
			missiles.erase(missiles.begin() + i);
		else
			i++;
	}
}

void DrawMissiles() { //�̻��� �׸��� �Լ�
	UpdateMissiles();
	int size = missiles.size();
	for (int i = 0; i < size; i++) {
		InitLight(4);
		glPushMatrix();
		glTranslatef(missiles[i].pos.val[0],
			missiles[i].pos.val[1],
			missiles[i].pos.val[2]);
		glutSolidSphere(0.2, 20, 20);
		glPopMatrix();
	}

	for (int i = 0; i < missiles.size(); ) {
		if (missiles[i].pos.val[2] > 15)
			missiles.erase(missiles.begin() + i);
		else
			i++;
	}

}

void UpdateBombs() { //��ź�� ��ǥ ������Ʈ
	vec3 acc(0, -1, -30);
	float bombTime = 0.001;
	int size = bombs.size();
	for (int i = 0; i < size; i++) {
		bombs[i].v = bombs[i].v + (acc * bombTime);
		bombs[i].pos = bombs[i].pos + bombs[i].v * bombTime;
	}

	for (int i = 0; i < bombs.size();) {
		if (bombs[i].pos.val[1] < 0.5 + 0.25)//�ٴ��浹
			bombs.erase(bombs.begin() + i);
		else i++;
	}

	for (int i = 0; i < bombs.size(); ) { //�ָ� ��� ���
		if (bombs[i].pos.val[2] < -12)
			bombs.erase(bombs.begin() + i);
		else
			i++;
	}
}

void DrawBombs() { //��ź �׸��� �Լ�
	UpdateBombs(); //��ź ��ǥ ������Ʈ
	int size = bombs.size();
	for (int i = 0; i < size; i++) {
		InitLight(3);
		glPushMatrix();
			glTranslatef(bombs[i].pos.val[0],
				bombs[i].pos.val[1],
				bombs[i].pos.val[2]);
			glutSolidSphere(0.3, 20, 20);
		glPopMatrix();
	}
}


void DisPlayObject() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// ��
	InitLight(0);
	glPushMatrix();
		glTranslatef(0.0, 0.0, -20);
		glScalef(25, 0.5, 400);
		glutSolidCube(1.0);
	glPopMatrix();

	// ��ũ ��� �׸���
	InitLight(tank.getTankID());
	tank.DrawTank(time,helicopter.getHelicopterHeight());
	InitLight(helicopter.getHelicopterID());
	helicopter.DrawHelicopter();
	
	if (countMissile > 500 && missiles.size() < 5)//���� �ð����� �̻��� �߻�
		CreateMissile();

	countMissile++;

	bool tankhit = tankHitCheck(); //��ũ�� ����� ��ź�� ������ 
	
	//tank�� ���� (�ǰ� ǥ��)
	if (tankhit)  
		tank.setTankCol(1, 0, 0);
	else
		tank.setTankCol(0, 0.5, 0.4);

	bool heliHit = HeliHitCheck();

	//helicopter (�ǰ� ǥ��)
	if (heliHit)  
		helicopter.setHelicopterCol(1, 0, 0);
	else
		helicopter.setHelicopterCol(0.4, 0.5, 0.4);

	DrawBombs(); // ��Ⱑ ��� ��ź �׸���
	DrawMissiles(); // ��ũ�� ��� �̻��� �׸���
	glFlush();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Tank Slash");
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glutDisplayFunc(DisPlayObject);
	glutReshapeFunc(MyReshape);
	glutTimerFunc(10, TimerEvent, 1);
	glutSpecialFunc(helicopterMove);
	glutMotionFunc(MouseMove);
	glutKeyboardFunc(BombPressed);
	glClearColor(0.4, 0.4, 0.4, 1.0);
	glutMainLoop();
	return 0;
}