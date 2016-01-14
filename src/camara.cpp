#include "camara.hpp"
void Camara::set_vision(){
        glRotatef(ang_x,1.0,0.0,0.0); 
    glRotatef(ang_y,0.0,1.0,0.0);
    glTranslated(-x,-y,-z);
}
void Camara::cambia_posicion(double m, double n, double l, double o){
    if (m==1){
        float xrotrad, yrotrad;
        yrotrad = (ang_y / 180 * 3.141592654f);
        xrotrad = (ang_x/ 180 * 3.141592654f); 
        x -= float(sin(yrotrad));
        z += float(cos(yrotrad)) ;
        y += float(sin(xrotrad));
    }
    else if (n==1){
       float yrotrad;
        yrotrad = (ang_y / 180 * 3.141592654f);
        x -= float(cos(yrotrad)) * 0.2;
        z -= float(sin(yrotrad)) * 0.2;
    }
    else if(l==1){
        float yrotrad;
        yrotrad = (ang_y / 180 * 3.141592654f);
        x += float(cos(yrotrad)) * 0.2;
        z += float(sin(yrotrad)) * 0.2;
    }
    else if(o==1){
        float xrotrad, yrotrad;
        yrotrad = (ang_y / 180 * 3.141592654f);
        xrotrad = (ang_x / 180 * 3.141592654f); 
        x += float(sin(yrotrad)) ;
        z -= float(cos(yrotrad)) ;
        y -= float(sin(xrotrad)) ;
    }
    
}
void Camara::girar_vista(double giro_x, double giro_y){
    ang_x+=giro_x;
    ang_y+=giro_y;
    
}