/**
**********************************************
CURVA B-SPLINE
**********************************************
**/

#include <GL/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
#include<math.h>


/**Variables globales*/
int SCREEN_WIDTH = 900;
int SCREEN_HEIGHT =700; int numeroPuntos=0;
GLint mover=0, pos=0; //Variables para mover los puntos

/**Variables globales para el funcionamiento de los Menus*/
GLint modelo=0;
GLint ejes=0;
GLint puntosMover=0;
GLint curvas=0;
GLint linea=0;
GLint puntosMostrar=0;
GLint modeloPuntosMover=0;

/**Prototipos de funcion*/
void init(void);
void display(void);
void reshape(int, int);
/**Funciones para las graficas (se explicaran a detalle mas adelante)**/
void graficaPuntosBezier(void);
void graficaCurvaB_Spline(void);
float CurvaB_Spline(float,int, int , int );
void dibujarEjes(void);
void polilineasB_Spline(void);
void introducirClickMostrar(int,int,int,int);
void introducirClickMover(int,int,int,int);
void moverPuntos(int,int);
void motion(int,int);
void modelo1(bool);void modelo2(bool);void modelo3(bool);void modelo4(bool);void modelo5(bool);

/**Menus*/
void menuPuntosdeControl(int);
void menuPolilinea(int);
void menuCurvaBSpline(int);
void menuMoverPuntos(int);
void menuEjeCoordenadas(int);
void mainMenu(int);
void menu();

    /**Clase se que permite guardar la posicion de los
    puntos de control que estemos agregando**/
class Point{
    public:
        float x, y, z;
        void axyz(float x2, float y2){x = x2; y = y2;}
        const Point & operator = (const Point & rPoint){
            x = rPoint.x;
            y = rPoint.y;
            z = rPoint.z;
            return *this;
        }
};
Point abc[4];

/**Funciones que se pasa como parametro un booleano para poder hacer
    funcionales las opciones de activado y desactivado en los menus**/
        //cada modelo es una opcion del menu
void modelo1(bool band){
    if(band){glutMouseFunc(introducirClickMostrar);}
    glPointSize(6);
        graficaPuntosBezier();
}
void modelo2(bool state){
    if(state){
        if(numeroPuntos>=4){
            polilineasB_Spline();
            graficaPuntosBezier();
        }
    }
}
void modelo3(bool state){
    if(state)
        if(numeroPuntos>=4)
            graficaCurvaB_Spline();
}

void modelo4(bool band){
    if(band){glutMouseFunc(introducirClickMover);}
}

void modelo5(bool state){
    if(state){
        glColor3f(1,1,1);
        dibujarEjes();
    }
}
/***************************************/

/***EstaS funciones nos permitiran establecer en que parte de
    la ventana se estara dando click con el mouse para luego
    realizar las acciones correspondientes***/
void introducirClickMostrar(int boton, int state, int x, int y){
    if(boton==GLUT_LEFT_BUTTON && state == GLUT_DOWN && puntosMostrar==1){ //condicional para añadir nuevos puntos de control
        abc[numeroPuntos].axyz((float)x,(float)(SCREEN_HEIGHT -y));
 	 	numeroPuntos++;
 	}
}

void introducirClickMover(int boton,int state,int x,int y){
    if(boton==GLUT_LEFT_BUTTON && state == GLUT_DOWN && puntosMover==1){//condicional para dar movimiento a puntos de control
 	 	moverPuntos(x,SCREEN_HEIGHT - y);
 	}else{
        mover=0;
 	}
}
/***************************************/

/***Funciones para graficar los puntos y unirlos con lineas***/
void graficaPuntosBezier(void){
    float x,y;
    glBegin(GL_POINTS);
    glColor3f(0.976,0.973,0.973);
    for(int i=0;i<numeroPuntos;i++){
        x=abc[i].x;
        y=abc[i].y;
        glVertex2f(x,y);
    }
    glEnd();
}
/*** Funcion para graficar la polilinea ***/
void polilineasB_Spline(void){
    GLfloat  x, y; //declarar variables
    glColor3f(0.953,0.871,0.541); // para el color de los puntos
    glLineWidth(1); // para agrandar la linea
    glBegin(GL_LINE_STRIP);
    for(int i=0;i<numeroPuntos;i++){
        x=abc[i].x;
        y=abc[i].y;
        glVertex2f(x,y);
    }
    glEnd();
}

/*** Funcion para graficar la Curva B Spline ***/
void graficaCurvaB_Spline(void){
    float x,y;
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    glColor3f(0.922,0.58,0.525);//Para cambiar el color de la curva
    for(int i=0;i<=numeroPuntos-4;i++){  // Va iterando por cada 4 puntos de control
        for(float u=0.0;u<=1;u+=0.01){
            x=CurvaB_Spline(u,0, i, i+4);
            y=CurvaB_Spline(u,1,i, i+4);
            glVertex2f(x,y);
        }
    }
    glEnd();
}
/***************************************/
/***Funcion que nos permitira Dibujar la curva en base a los puntos***/
float CurvaB_Spline(float u,int coordenada, int p, int q){
    float suma=0.0;
    float punto0=0, punto1=0, punto2=0, punto3=0;
    int m=0;
        punto0=pow(1.0-u,3)/(6);                /**Formula para el F0(u)*/
        punto1=(3*pow(u,3)-6*u*u+4)/(6);        /**Formula para el F1(u)*/
        punto2=(1+3*u+3*u*u-3*pow(u,3))/(6);    /**Formula para el F2(u)*/
        punto3=pow(u,3)/(6);                    /**Formula para el F3(u)*/
    float punto[4]={punto0, punto1, punto2, punto3};
    if(coordenada==0){
        for(int i=p;i<q;i++){// para el eje x
            suma=suma+abc[i].x*punto[m];  m=m+1;  /**Qi(u) = F0(u)Pi + F1(u)P(i+1) + F2(u)P(i+2) + F3(u)P(i+3)**/
        }
    }
    else{
        for(int i=p;i<q;i++){// para el eje y
            suma=suma+abc[i].y*punto[m];  m=m+1;   /**Qi(u) = F0(u)Pi + F1(u)P(i+1) + F2(u)P(i+2) + F3(u)P(i+3)**/
        }
    }
    return suma;
}

/***************************************/
/**Funcion que permite validar la condicion para realizar
        el movimiento de los puntos de control**/
void moverPuntos(int x, int y){
    for(int i=0; i<numeroPuntos; i++){
        if(x<=abc[i].x+5 && x>=abc[i].x-5 && y<=abc[i].y+5 && y>=abc[i].y-5){
            mover=1; pos=i; i=numeroPuntos;
        }else{
            mover=0;pos=i;
        }
    }
}
/**Funcion que permite actualizar la posicion los puntos de control**/
void motion(int x, int y){
    if(mover==1){
        abc[pos].x = float(x);
        abc[pos].y = float(SCREEN_HEIGHT - y);
    }
}
/***************************************/
/***Funcion para graficar el eje de coordenadas***/
void dibujarEjes(void){
    glBegin(GL_LINES);
        glVertex2f(0,SCREEN_HEIGHT/2);
        glVertex2f(SCREEN_WIDTH,SCREEN_HEIGHT/2);
        glVertex2f(SCREEN_WIDTH/2,0);
        glVertex2f(SCREEN_WIDTH/2,SCREEN_HEIGHT);
    glEnd();
}

/***Funciones para los menus***/

/**Habilita ingresar nuevos puntos de control**/
void menuPuntosdeControl(int opc){
    switch(opc){
        case 1: puntosMostrar=1;  modelo1(true); break;
        case 2: puntosMostrar=2;  modelo1(false); break;
    }
}

/**Habilita mostrar polilinea**/
void menuPolilinea(int opc){
    switch(opc){
        case 1: linea=1; modelo2(true); break;
        case 2: linea=2; modelo2(false); break;
    }
}

/**Habilita curva B-Spline**/
void menuCurvaBSpline(int opc){
    switch(opc){
        case 1: curvas=1;  modelo3(true); break;
        case 2: curvas=2;  modelo3(false); break;
    }
}

/**Habilita movimiento de los puntos de control**/
void menuMoverPuntos(int opc){
    switch(opc){
        case 1: puntosMover=1; modelo4(true);  break;
        case 2: puntosMover=2; modelo4(false); break;
    }
}

/**Habilita mostrar ejes coordenados**/
void menuEjeCoordenadas(int opc){
    switch(opc){
        case 1: ejes=1; modelo5(true); break;
        case 2: ejes=2; modelo5(false); break;
    }
}

/**Para cerrar la aplicacion**/
void mainMenu(int opc){
    switch(opc){
        case 6: exit(-1);
    }
    glutPostRedisplay();
}

void menu(){
    /**SubMenu**/
 	int subMenuPuntosControl = glutCreateMenu(menuPuntosdeControl);
        glutAddMenuEntry("Activado",1);
        glutAddMenuEntry("Desactivado",2);

    int subMenuPolilinea = glutCreateMenu(menuPolilinea);
        glutAddMenuEntry("Activado",1);
        glutAddMenuEntry("Desactivado",2);

    int subMenuCurvaBSpline = glutCreateMenu(menuCurvaBSpline);
        glutAddMenuEntry("Activado",1);
        glutAddMenuEntry("Desactivado",2);

    int subMenuMoverPuntos = glutCreateMenu(menuMoverPuntos);
        glutAddMenuEntry("Activado",1);
        glutAddMenuEntry("Desactivado",2);

    int subMenuEjeCoordenadas = glutCreateMenu(menuEjeCoordenadas);
        glutAddMenuEntry("Activado",1);
        glutAddMenuEntry("Desactivado",2);

 	/**Main Menu**/
 	int menu = glutCreateMenu(mainMenu);
        glutAddSubMenu("Ingresar Puntos de Control",subMenuPuntosControl);
        glutAddSubMenu("Mostrar Polilinea",subMenuPolilinea);
        glutAddSubMenu("Mostrar Curva B-Spline",subMenuCurvaBSpline);
        glutAddSubMenu("Mover Puntos de Control",subMenuMoverPuntos);
        glutAddSubMenu("Mostrar Eje Coordenadas",subMenuEjeCoordenadas);
        glutAddMenuEntry("Salir de la aplicación",6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
            /**Funcion Principal **/
int main (int argc, char*argv[]){
 	glutInit(&argc, argv);
 	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 	glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
 	glutInitWindowPosition(500,150);
 	glutCreateWindow("PC-03 | CURVA B-SPLINE by Cisneros & Valdivia");
 	init();
 	menu();
 	glutReshapeFunc(reshape);
 	glutDisplayFunc(display);
 	glutMotionFunc(motion);
 	glEnable(GL_DEPTH_TEST);
 	glutMainLoop();
 	return 0;
}
/**Funcion init **/
void init(void){
    glClearColor(0.153,0.157,0.22,0.0);
    glShadeModel(GL_FLAT);
}
/**Funcion display **/
void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
        menuPuntosdeControl(puntosMostrar);
        menuPolilinea(linea);
        menuCurvaBSpline(curvas);
        menuMoverPuntos(puntosMover);
        menuEjeCoordenadas(ejes);
        mainMenu(modelo);
    glFlush();
    glPopMatrix();
    glutSwapBuffers();
}
/**Funcion reshape **/
void reshape(int w, int h) {
 	glViewport(0,0,(GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, SCREEN_WIDTH,0.0,SCREEN_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
