#include <iostream>
#include <vector>
#include <GL/freeglut.h>
#include "imageloader.h"
#include "textureloader.h"

bool mouseDown = false;
bool movement = false;
float xrot = 0.0f, yrot = 0.0f;
float xmov = 0.0f, ymov = 0.0f, zmov = 0.0f;
float sizes = 1.0f;

void display();

void LoadTexture() {
	Model file = Model("C:/Users/Alfriyanis/Desktop/Github/GRAFKOM_TR_H_672016125/GRAFKOM_TR_H_672016125/Woman1.tga");

	glEnable(GL_TEXTURE_2D);

	GLuint texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, file.HasAlphaChannel() ? GL_RGBA : GL_RGB, file.GetWidth(), file.GetWidth(), 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, file.GetPixels().data());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
	case 'Q':
		sizes += 0.2f;
		break;
	case 'e':
	case 'E':
		sizes -= 0.2f;
		break;
	case 'a':
	case 'A':
		yrot -= 5.0f;
		break;
	case 'd':
	case 'D':
		yrot += 5.0f;
		break;
	case 's':
	case 'S':
		xrot += 5.0f;
		break;
	case 'w':
	case 'W':
		xrot -= 5.0f;
		break;
	case 'r':
	case 'R':
		if (movement) {
			movement = false;
			printf("Stop Run\n");
		}
		else {
			printf("Run\n");
			movement = true;
		}
		break;
	}

	glutPostRedisplay();
}

void keyboardSpecial(int key, int x, int y) {

	switch (key) {
	case 100:
		xmov -= 0.025f;
		break;
	case 101:
		ymov += 0.025f;
		break;
	case 102:
		xmov += 0.025f;
		break;
	case 103:
		ymov -= 0.025f;
		break;
	}

	glutPostRedisplay();
}

/*
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		std::cout << "KLIK KIRI" << " = anda menekan LEFT_BUTTON" << std::endl;
		mouseDown = true;
		xmov = x - yrot;
		ymov = -y + xrot;
	}
	else
		mouseDown = false;
	glutPostRedisplay();
}

void mouseMotion(int x, int y) {
	if (mouseDown) {
		yrot = x - xmov;
		xrot = y + ymov;

		glLoadIdentity();
		gluLookAt(0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); //mengatur penglihatan objek
		glRotatef(xrot, 1.0, 0.0, 0.0);
		glRotatef(yrot, 0.0, 1.0, 0.0);
		glutPostRedisplay();
	}
}*/

void timer(int) {
	glutTimerFunc(1000 / 30, timer, 0);

	if (movement)
		yrot += 5.0f;
	else
		yrot = yrot;
	glutPostRedisplay();
}

void transform() {
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glTranslatef(xmov, ymov, zmov);
	glScalef(sizes, sizes, sizes); 
}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
	loaderNfg sketsa;
	sketsa.readfile();

	int Jumtampilan = sketsa.totalNFG / 3;

	LoadTexture();

	gluLookAt(0.0, 2.0, 8.0, 0.0, 1.5, 3.0, 0, 1, 0);

	transform();

	for (int i = 0; i < Jumtampilan; i++) {

		glBegin(GL_TRIANGLES);
		glTexCoord2f(sketsa.jumVertex[sketsa.jumTampilan[i].pos.x].uv.x, sketsa.jumVertex[sketsa.jumTampilan[i].pos.x].uv.y);
		glVertex3f (sketsa.jumVertex[sketsa.jumTampilan[i].pos.x].pos.x, 
					sketsa.jumVertex[sketsa.jumTampilan[i].pos.x].pos.y, 
					sketsa.jumVertex[sketsa.jumTampilan[i].pos.x].pos.z);
		glTexCoord2f(sketsa.jumVertex[sketsa.jumTampilan[i].pos.y].uv.x, sketsa.jumVertex[sketsa.jumTampilan[i].pos.y].uv.y);
		glVertex3f (sketsa.jumVertex[sketsa.jumTampilan[i].pos.y].pos.x, 
					sketsa.jumVertex[sketsa.jumTampilan[i].pos.y].pos.y, 
					sketsa.jumVertex[sketsa.jumTampilan[i].pos.y].pos.z);
		glTexCoord2f(sketsa.jumVertex[sketsa.jumTampilan[i].pos.z].uv.x, sketsa.jumVertex[sketsa.jumTampilan[i].pos.z].uv.y);
		glVertex3f (sketsa.jumVertex[sketsa.jumTampilan[i].pos.z].pos.x, 
					sketsa.jumVertex[sketsa.jumTampilan[i].pos.z].pos.y, 
					sketsa.jumVertex[sketsa.jumTampilan[i].pos.z].pos.z);
		glEnd();



	}

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void ukuran(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w > h) {
		glViewport(0, 0, w, w);
		glTranslatef(0.0, -0.5, 0.0);
		glRotatef(180.0, 0.0, 1.0, 0.0);
		glScalef(-0.5, 0.5, -0.5);
	}
	else {
		glViewport(0, 0, w, h);
	}

	gluPerspective(20.0, w / h, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myinit() {
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("GRAFKOM_TR_H");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	//glutMouseFunc(mouse);
	//glutMotionFunc(mouseMotion);
	glutTimerFunc(0, timer, 0);
	glutReshapeFunc(ukuran);
	glutDisplayFunc(display);

	myinit();
	glutMainLoop();

	return 0;
}