#ifndef _3D_MODEL
#define _3D_MODEL
#include <GL/glut.h>
#include <vector>
#include "vertex.h"
#include "math.h"
#include "jpg_imagen.hpp"
#include <string>
class Modelo{
private:
    _vertex3f rotar(_vertex3f p, double alpha);
	float grados_radianes(float angulo);
    double distancia(_vertex3f a,_vertex3f b);
protected:
	vector <_vertex3f> vertices;
    jpg::Imagen * imagen;
    GLuint ident_textura;
    _vertex4f colore;
	vector <_vertex3i> triangulos;
  vector <_vertex3f> normalesVert;
  vector <_vertex3f> normalesCara;
  vector <_vertex2f> texturas;

public:
    void set_colores(double r, double g, double b, double a){
        colore._0=r;
        colore._1=g;
        colore._2=b;
        colore._3=a;
    }
    void carga_textura(const string & ruta){
        imagen = new jpg::Imagen(ruta);
    }
    void trasladar_figurax(float traslacion);
    void trasladar_figuray(float traslacion);
    void rotar_z(double ang);
    void escalar(double escalado);
	Modelo(){
	}
    void dibujar_normales();
    _vertex3f modulizar(_vertex3f normales);
	void drawModel(int i = 0);
    void drawNormales(int i = 0);
    void mostrar_normales();
    void generar_matrix_textura(int n, int m);
    void generarRevolucion(float angulo_inicial = 0, float angulo_final = 2*M_PI);
    void generarBarrido();
    void setVert(vector<_vertex3f> vertex){vertices = vertex;}
    void setTrian(vector<_vertex3i> triang){triangulos = triang;}
    void setNV(vector<_vertex3f> vertex){for(int i=0;i<normalesVert.size();i++)normalesVert[i]= vertex[i];}
    void setNC(vector<_vertex3f> triang){for(int i=0;i<normalesCara.size();i++)normalesCara[i] = triang[i];}
};
#endif
