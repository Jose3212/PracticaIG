#ifndef _3DfiguresH_
#define	_3DfiguresH_
#include "estructuras.h"
#include "jpg_imagen.hpp"
#include <vector>
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include "vertex.h"

using namespace std;

class figura3D{
protected:
  void invertirNormales();
  vector<_vertex3f> vertices;
  vector <cara> caras;
  float R,G,B;
  //  _vertex3f centro;
  //p4
  vector <_vertex3f> nvertices;
  vector <_vertex3f> ncaras;
  vector <vertice2D> vtexturas;
  jpg::Imagen * pimg = NULL ;
  GLuint ID_text ;
  unsigned int tamx, tamy;
  unsigned char * texels;

  _vertex3f normaliza(_vertex3f v);

  void calcularNormales();

public:
  //p4
  void drawNormales();


  void calcularNCaras();

  void calcularNVertices();

  void cargarTextura(const string & im);

  void calcularCoordenadasTextura(int lados, int vperfil);

  void setCentro(float x, float y, float z);

  figura3D();

  void draw( char modo);

  void draw_solido();

  void draw_vertice();

  void draw_ajedrez();

  void draw_alambre();

  void revolucionar(char eje_rotador, int lados, bool tapa );

  void revolucionar_seccion(char eje_rotador, int lados, float  anguloA, float anguloB);

  void trasladar(_vertex3f cen);

  void esfera(int lados, float rad);

  void changeColor(float RR, float GG, float BB);

void activarTexturas();
  vector<_vertex3f> getVertices();
  vector <cara> getCaras();
  void escalar(float es);

};
#endif	

