#ifndef _3D_MODEL
#define _3D_MODEL
#include <GL/glut.h>
#include <vector>
#include "vertex.h"
#include "math.h"
class Modelo{
private:
    _vertex3f rotar(_vertex3f p, double alpha);
	float grados_radianes(float angulo);
protected:
	vector <_vertex3f> vertices;
	vector <_vertex3i> triangulos;
  vector <_vertex3f> normalesVert;
  vector <_vertex3f> normalesCara;

public:
    void trasladar_figurax(float traslacion);
    void trasladar_figuray(float traslacion);
    void rotar_z(double ang);
    void escalar(double escalado);
	Modelo(){
	}
    _vertex3f modulizar(_vertex3f normales);
	void drawModel(int i = 0);
    void drawNormales(int i = 0);
    void generarRevolucion(float angulo_inicial = 0, float angulo_final = 2*M_PI);
    void generarBarrido();
    void setVert(vector<_vertex3f> vertex){vertices = vertex;}
    void setTrian(vector<_vertex3i> triang){triangulos = triang;}
    void setNV(vector<_vertex3f> vertex){normalesVert = vertex;}
    void setNC(vector<_vertex3f> triang){normalesCara = triang;}
};
#endif
