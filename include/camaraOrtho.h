#ifndef _camaraH_
#define	_camaraH_
#include "3Dfigures.h"
#include <vector>
#include <GL/glut.h>
class camaraOrtho {
private:
  float obs_x;
  float obs_y; 
  float obs_z; 
  float mirada_x; 
  float mirada_y; 
  float mirada_z; 
  float vec_obs_x; 
  float vec_obs_y; 
  float vec_obs_z;
  float ang_x;
  float ang_y;
  float ang_z;
  vector<float> backupValores;
  bool ortogonal;
  bool esferica;
bool examinar;
float izquierda;
float derecha;
float abajo;
float arriba;
float cerca;
float lejos;
    float zoom = 50; 
public:
  camaraOrtho();
  camaraOrtho(float x, float y, float z, float m_x, float m_y, float m_z, float vo_x, float vo_y, float vo_z, float an_x,float an_y,float an_z);
  void setObservador();
  void girar(float x, float y);
  void desplazar(char movimiento);
  void reset();
void setProyeccion(float a,float b, float c, float d, float e, float f);
  void cambiarProyeccion(int p);
  //esta función activa la cámara esférica o la desactiva
  void cambiarEsferica();
  void activarExplorar(_vertex3f puntoGiro);
};

#endif	


