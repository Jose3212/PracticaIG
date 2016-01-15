#ifndef _escenaH_
#define	_escenaH_
#include "PLY2.h"
#include "cuadro.h"
//Esta clase va a servir para dibujar las distintas escenas requeridas en la práctica 4

using namespace std;
class escena{
GLuint ID_text;
  PLY lata_tapa;
  PLY lata_tronco;
  PLY lata_culo;
  PLY peon1;
  PLY peon2;
  PLY peon3;
  PLY bet1;
  PLY bet2;
  PLY bet3;
  PLY bet4;
  PLY bet5;
  PLY bet6;
  int figuraSeleccionada;
  figura3D esfera;
  bool esferaTextura;
  cuadro cuad;
  bool instancia;
  int dibujo;
GLUquadric  *esfer;
public:
  escena();
  bool instanciado();
  void cambiarTexturaEsfera();
  void instanciar(int lados, char eje);
  void cambiarEscena();
  void seleccionarFigura(int i);
  void draw(char mode);
_vertex3f centroGiro();

};

#endif
