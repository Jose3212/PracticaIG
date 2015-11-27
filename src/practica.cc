//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************
#include "stdlib.h"
#include "stdio.h"
#include <cstdlib>
#include "modeloPly.hpp"
#include "dibujos.h"
#include "jerarquia.hpp"
using namespace std;
int i,j;
Brazo brazo;
Palma palma;
Dedo indice;
Dedo anular;
Dedo corazon;
Dedo menique;
Dedo pulgar;
Jerarquia dedos;
//Los ponemos como variables globales para no tener que pasar parametros a las funciones a traves del main.
//Cubo c1(5);
//Tetraedro t1(5);
//ModeloPly ant("./data/ant.ply");
//ModeloPly beethoven("./data/beethoven.ply");
//ModeloPly big_dodge("./data/big_dodge.ply");
//test1 perfil;
//test2 perfil2;
//test3 perfil3;
//test4 perfil4;
//test5 perfil5;
// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//**************************************************************************
//
//***************************************************************************

void clear_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}

//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
	switch(j){
	case 0:
		brazo.drawModel(i);
		break;
	case 1:
		anular.drawModel(i);
		break;
	case 2:
		corazon.drawModel(i);
		break;
	case 3:
		menique.drawModel(i);
		break;
	case 4:
		dedos.dibujar(i);
		break;
	case 5:
		dedos.girar_munieca(i);
		break;
	case 6:
		dedos.saludar(i);
		break;
	case 7:
		dedos.barcenas(i);
		break;
	case 8:
		dedos.senialar(i);
		break;
/*	case 9:
		perfil5.drawModel(i);
		break;
*/
	}
}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{

clear_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{
//Añadimos teclas para retocar el programa.
	//if (toupper(Tecla1)=='Q') exit(0);
	switch(Tecla1){
	case '1':	//Tetraedro
		j=0;
		break;
	case '2':	//Cubo
		j=1;
		break;
	case '3':
		j=2;
		break;
	case '4':
		j=3;
		break;
	case '5':
		j=4;
		break;
	case 'g':
	case 'G':
		j=5;
		break;
	case 'd':
	case 'D':
		j=6;
		break;
	case 'b':
	case 'B':
		j=7;
		break;
	case 'e':
	case 'E':
		j=8;
		break;
	case 'j':	//Ajedrez
	case 'J':
		i=2;
		break;
	case 'p':	//Puntos
	case 'P':
		i=0;
		break;
	case 's':	//Solido
	case 'S':
		i=3;
		break;
	case 'a':	//Aristas
	case 'A':
		i=1;
		break;
	case 'q':	//Salida
	case 'Q':
		exit(0);
		break;
	case 't':	//todo
	case 'T':
		i=4;
		break;
	}
	//Pintamos de nuevo
	glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=5;
Window_height=5;
Front_plane=10;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=2*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
//
change_projection();
//
glViewport(0,0,UI_window_width,UI_window_height);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("Practica");

pulgar.generarRevolucion(0,360);
indice.generarRevolucion(0,360);
anular.generarRevolucion(0,360);
corazon.generarRevolucion(0,360);
menique.generarRevolucion(0,360);
brazo.generarRevolucion(0,360);
brazo.trasladar_figuray(0.5);
palma.escalar(1.50);
pulgar.escalar(0.75);
pulgar.trasladar_figurax(-1.65);
pulgar.trasladar_figuray(0.65);
pulgar.rotar_z(46);
indice.trasladar_figurax(-2);
anular.trasladar_figurax(-0.675);
corazon.trasladar_figurax(0.675);
menique.trasladar_figurax(2);
dedos.aniade_figura(pulgar);
dedos.aniade_figura(indice);
dedos.aniade_figura(anular);
dedos.aniade_figura(corazon);
dedos.aniade_figura(menique);
dedos.aniade_figura(palma);
dedos.aniade_figura(brazo);
//perfil5.generarRevolucion(0,360);
// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw_scene);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_keys);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_keys);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
