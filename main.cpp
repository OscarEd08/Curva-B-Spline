#include <GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
#include<math.h>
#include<iostream>

int SCREEN_HEIGHT =480; int numeroPuntos=0;

class Point{ public:
 	float x, y, z;
 	void axyz(float x2, float y2){x = x2; y = y2;}
 	 	const Point & operator = (const Point & rPoint){
 	 	x = rPoint.x;  	 	y = rPoint.y;  	 	z = rPoint.z;  	 	return *this;  	}
};
Point abc[4];

void init() {
 	glClearColor(0.0,0.0,0.0,0.0);   	glColor3f(1.0,0.0,1.0);  	glPointSize (5);  	glMatrixMode(GL_PROJECTION);  	glLoadIdentity();  	gluOrtho2D(0.0, 640.0,0.0,480.0);
}


void dibujaLinea(Point p1, Point p2){
 	glBegin(GL_LINES);
 	glVertex3f(p1.x, p1.y, p1.z);  	glVertex3f(p2.x, p2.y, p2.z);
 	glEnd();  	glFlush();
}
 	void dibujaPunto(int x, int y){
 	glBegin(GL_POINTS);  	glVertex2i(x,y);
 	glEnd();  	glFlush();
}
 	Point dibujaBezier(Point A, Point B, Point C, Point D, double t){
 	 	Point P;
 	P.x = pow((1-t),3)*A.x+3*t*pow((1-t),2)*B.x+3*(1-t)*pow(t,2)*C.x + pow(t,3)*D.x;
 	P.y = pow((1-t),3)*A.y+3*t*pow((1-t),2)*B.y+3*(1-t)*pow(t,2)*C.y + pow(t,3)*D.y;  	P.z = pow((1-t),3)*A.z+3*t*pow((1-t),2)*B.z+3*(1-t)*pow(t,2)*C.z + pow(t,3)*D.z;
 	return P;
}

void introducirClic(int boton, int state, int x, int y){
 if(boton==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) exit(1);  if(boton==GLUT_LEFT_BUTTON && state == GLUT_DOWN){   abc[numeroPuntos].axyz((float)x,(float)(SCREEN_HEIGHT -y));
 	 	numeroPuntos++;
 	 	dibujaPunto(x, SCREEN_HEIGHT -y);  	 	if(numeroPuntos == 4){  	 	 	glColor3f(0.0,0.5,0.5);  	 	 	dibujaLinea(abc[0], abc[1]);  	 	 	dibujaLinea(abc[1], abc[2]);  	 	 	dibujaLinea(abc[2], abc[3]);

 	 	 	Point PO1d = abc[0];
 	 	 	for(double t=0.0; t<= 1.0; t+=0.1){
 	 	 	 	Point P = dibujaBezier(abc[0], abc[1], abc [2], abc[3], t);
 	 	 	 	dibujaLinea(PO1d, P);
 	 	 	 	PO1d = P;

	 	}
 	 	 	glColor3f(1.0,0.0,1.0);
 	 	 	numeroPuntos =0;
 	 	}
 	}
}
 	void ElDisplay(){
 	 	glClear(GL_COLOR_BUFFER_BIT);
 	 	glFlush();
 	}

int main (int argc, char*argv[]){
 	glutInit(&argc, argv);   	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  	glutInitWindowSize(640,480);  	glutInitWindowPosition(500,150);  	glutCreateWindow("Curva del Senior Bezier");  	glClearColor(0.1,0.1,0.1,0.1);
 	glClear(GL_COLOR_BUFFER_BIT);  	glutDisplayFunc(ElDisplay);  	glutMouseFunc(introducirClic);
 	init();  	glutMainLoop();  	system("pause");
}
