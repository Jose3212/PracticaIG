#ifndef _CAMARA
#define _CAMARA
#include <GL/glut.h>
#include <math.h>
class Camara{
private:
    double x,y,z;
    double look_x, look_y, look_z;
    double up_x, up_y, up_z;
    double giro_x,giro_y;
    double ang_x,ang_y,ang_z;
public:
    Camara(){}
    Camara(double x, double y, double z){
        this->x = x;
        this->y = y;
        this->z = z;
        look_x = 0;
        look_y = 0;
        look_z = 0;
        up_y = 1;
        up_x = 0;
        up_z = 0;
        ang_x= 0;
        ang_y= 0;
        ang_z= 0;
        set_vision();       
    }
    void set_vision();
    void cambia_posicion(double m, double n, double l, double o);
    void girar_vista(double giro_x, double giro_y);
    
};


#endif