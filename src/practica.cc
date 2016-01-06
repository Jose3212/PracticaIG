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
#include "material.hpp"
using namespace std;
int i,j;
float light_alpha = 0.0;
float light_beta = 0.0;
bool textura = false;
jpg::Imagen * Textura;



GLuint loadTexture(jpg::Imagen* image) {

  GLuint textureId;

  glGenTextures(1, &textureId); //Make room for our texture

  glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit

  //Map the image to the texture

  glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D

         0,                            //0 for now

         GL_RGB,                       //Format OpenGL uses for image

         image->tamX(), image->tamY(),  //Width and height

         0,                            //The border of the image

         GL_RGB, //GL_RGB, because pixels are stored in RGB format

         GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored

                           //as unsigned numbers

         image->leerPixels());               //The actual pixel data

  return textureId; //Returns the id of the texture

}
GLuint _textureId;


/*
Brazo brazo;
Palma palma;
Dedo indice;
Dedo anular;
Dedo corazon;
Dedo menique;
Dedo pulgar;
Jerarquia dedos;
*/
Material m1;
GLUquadric  *quadObj;
//Los ponemos como variables globales para no tener que pasar parametros a las funciones a traves del main.
Cubo c1(5);
Tetraedro t1(5);


ModeloPly peon1("./data/perfil.ply");
ModeloPly peon2("./data/perfil.ply");
ModeloPly peon3("./data/perfil.ply");
ModeloPly lata_cue("./data/lata-pcue.ply");
ModeloPly lata_sup("./data/lata-psup.ply");
ModeloPly lata_inf("./data/lata-pinf.ply");
Modelo esfera;
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

void cambiaLuz(){
	cout << "Alfa: " << light_alpha << ", Beta: " << light_beta << endl;	
	GLfloat light_ambient[]={0.3, 0.3, 0.3, 1.0};
	GLfloat light_diffuse[]={0.5, 0.5, 0.5, 1.0};
	GLfloat light_specular[]={1.0, 1.0, 1.0, 1.0};
	GLfloat light_position[]={light_alpha, 5.0, light_beta, 0.0};
	//GLfloat spotlight[]={light_alpha,light_beta,1.0};
	//GLfloat angulo[] = {90};
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	//glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF,angulo);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT2);
	glEnable(GL_SMOOTH);
	glShadeModel(GL_SMOOTH);

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
	//esfera.drawNormales(i);
	switch (i){
		case 0:
			m1.material_difuso();
			break;
		case 1:
			m1.material_no_difuso();
			break;
		case 2:
			m1.material_metal();
			break;
		case 3:
			m1.material_azul();
	}
/*
	peon1.drawNormales(1);

	peon2.drawNormales(1);
	peon3.drawNormales(1);
	lata_cue.drawNormales(1);
	lata_sup.drawNormales(1);
	lata_inf.drawNormales(1);
	*/
if(textura == true){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  //glRotatef(90,1.0f,0.0f,0.0f);

  //glRotatef(rotate,0.0f,0.0f,1.0f);

  gluQuadricTexture(quadObj,1);
}
else{
	glDisable(GL_TEXTURE_2D);
}
gluSphere (quadObj, 5, 40, 40);
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
		if (toupper(Tecla1)=='Q') exit(0);
		switch (toupper(Tecla1)){
			
			case 'A': // aumentar el valor de β
				light_beta +=1;
				cambiaLuz();
				break;
			case 'Z': // disminuir el valor de β
				light_beta-=1;
				cambiaLuz();
				break;
			case 'X': // aumentar el valor de α
				light_alpha+=1;
				cambiaLuz();
				break;
			case 'C': // disminuir el valor de α
				light_alpha-=1;
				cambiaLuz();
				break;
			case '1':
				i=0;
				break;
			case '2':
				i=1;
				break;
			case '3':
				i=2;
				break;
			case '4':
				i=3;
				break;
			case 'L':
				if(!textura){
					textura = true;
				}
				else{
					textura = false;
				}
				break;
			case 'M':
				glEnable(GL_LIGHT0);
				break;
			case 'T':
				esfera.carga_textura("./data/text-madera.jpg");
				break;
			case 'E':
				esfera.quita_textura();
				break;
			draw_objects();
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

void EnableLighting(void) {

GLfloat light_ambient[]={0.3, 0.3, 0.3, 1.0};
GLfloat light_diffuse[]={0.5, 0.5, 0.5, 1.0};
GLfloat light_specular[]={1.0, 1.0, 1.0, 1.0};
GLfloat light_position[]={10.0, 5.0, 5.0, 1.0};
GLfloat light_position1[]={1.0, 1.0, -1.0, 1.0};
	GLfloat matSpecular[] = {1.0, 1.0, 1.0, 1.0};
	float shininess = 20;
GLfloat light_ambient1[]={0.3, 0.3, 0.3, 1.0};
GLfloat light_diffuse1[]={0, 1.0, 1.0, 1.0};
GLfloat light_specular1[]={1.0, 1.0, 0, 1.0};
//GLfloat light_position1[]={1.0, 1.0, 1.0, 1.0};
/*glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient1);
glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse1);
glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular1);
glLightfv(GL_LIGHT2, GL_POSITION, light_position1);*/
glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
glLightfv(GL_LIGHT0, GL_POSITION, light_position);
/*
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, matSpecular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, matSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	*/
	/*GLfloat emision[] = {0.3, 0.3, 0.3, 1.0};
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emision);
	*/
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
//glEnable(GL_LIGHT2);
glEnable(GL_SMOOTH);
glShadeModel(GL_SMOOTH);

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
EnableLighting();
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
Textura = new jpg::Imagen("./data/text-madera.jpg");
_textureId = loadTexture(Textura);

delete Textura;
/*
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
/*ant.escalar(0.05);
ant.trasladar_figurax(2);
ant.trasladar_figuray(8.5);
*/

peon1.peon = true;
/*peon1.set_colores(0.0, 0.0, 0.0, 1.0);
peon2.set_colores(1.0, 1.0,1.0, 1.0);
*/
/*
peon3.set_colores(1.0,1.0,1.0,1.0);
lata_cue.set_colores(1.0,1.0,1.0,1.0);
lata_sup.set_colores(0.184314, 0.309804, 0.309804, 1.0);
lata_inf.set_colores(0.184314, 0.309804, 0.309804, 1.0);

lata_cue.generarRevolucion(0,360);
lata_sup.generarRevolucion(0,360);
lata_inf.generarRevolucion(0,360);
peon1.generarRevolucion(0,360);
peon2.generarRevolucion(0,360);
peon3.generarRevolucion(0,360);
lata_cue.escalar(5);
lata_sup.escalar(5);
lata_inf.escalar(5);
lata_cue.rotar_z(180);
lata_sup.rotar_z(180);
lata_inf.rotar_z(180);
lata_cue.trasladar_figuray(2);
lata_sup.trasladar_figuray(2);
lata_inf.trasladar_figuray(2);
peon1.trasladar_figurax(5);
peon2.trasladar_figurax(-5);
peon3.trasladar_figurax(2.5);
lata_inf.generarBarrido();
lata_sup.generarBarrido();
lata_cue.generarBarrido();
peon1.generarBarrido();
peon2.generarBarrido();
peon3.generarBarrido();
peon3.carga_textura("./data/text-madera.jpg");
lata_cue.carga_textura("./data/text-lata-1.jpg");
*/
esfera.esfera(20,3);
quadObj = gluNewQuadric();
gluQuadricTexture(quadObj, GL_TRUE);

//esfera.generarBarrido();
//esfera.set_colores(1.0,1.0,1.0,1.0);
//esfera.carga_textura("./data/text-madera.jpg");

/*
dedos.aniade_figura(pulgar);
dedos.aniade_figura(indice);
dedos.aniade_figura(anular);
dedos.aniade_figura(corazon);
dedos.aniade_figura(menique);
dedos.aniade_figura(palma);
dedos.aniade_figura(brazo);
*/
//dedos.aniade_figura(ant);
//beethoven.generarBarrido();
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
