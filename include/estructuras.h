#ifndef _estructuras_
#define	_estructuras_
#include <math.h>
#include <GL/glut.h>

struct cara{
  int x,y,z;
  cara(){
    x = 0; 
    y = 0; 
    z = 0;
  }

  cara(int xx, int yy, int zz){
    x = xx; 
    y = yy; 
    z = zz;
  };
};

struct vertice2D{
  float x,y;
  vertice2D(){
    x = 0; 
    y = 0; 
  }

  vertice2D(float xx, float yy){
    x = xx; 
    y = yy; 
  };

};

struct materiall{
    void metal(){

    }

    void material_difuso(){
        GLfloat light_diffuse[]={1.0, 1.0, 1.0, 1.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_diffuse);
        	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
    }
    void material_no_difuso(){
        GLfloat light_diffuse[]={0.0, 0.0, 0.0, 0.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_diffuse);
        	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
    }
    void material_amarillo(){
        GLfloat light_diffuse[]={0.6, 1.0, 1.0, 0.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_diffuse);
        	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
    }
    void material_azul(){
        GLfloat light_diffuse[]={0.8, 1.0, 0.7, 0.0};
        GLfloat light_diffuse1[]={0.5, 0.3, 0.0, 0.0};
        GLfloat light_diffuse2[]={0.0, 1.0, 1.0, 0.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_diffuse1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_diffuse2);
        	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
    }
    void material_m(){
        GLfloat light_diffuse[]={0.0, 0.5, 0.5, 0.0};
        GLfloat light_diffuse1[]={0.6, 0.6, 0.0, 0.0};
        GLfloat light_diffuse2[]={0.0, 0.6, 0.6, 0.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_diffuse1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_diffuse2);
        	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);
        
    }
    void material_m1(){
        GLfloat light_diffuse[]={0.0, 0.0, 0.0, 0.0};
        GLfloat light_diffuse1[]={1.0, 1.0, 0.0, 0.0};
        GLfloat light_diffuse2[]={0.0, 1.0, 1.0, 0.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, light_diffuse1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, light_diffuse2);
        	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10);
    }


};


//struct vertice{
//  float x,y,z;
//  vertice(){
//    x = 0; 
//    y = 0; 
//    z = 0;
//  }



//  vertice(float xx, float yy, float zz){
//    x = xx; 
//    y = yy; 
//    z = zz;
//  };

//};

//struct normal{
//  float x,y,z;
//  void normaliza(){
//    int dis = sqrt(x*x+y*y+z*z);
//    x = x/dis;
//    y = y/dis;
//    z = z/dis;
//  }

//  normal(){
//    x = 0; 
//    y = 0; 
//    z = 0;
//  }

//  normal(int xx, int yy, int zz){
//    x = xx; 
//    y = yy; 
//    z = zz;
//  };

//  normal(vertice v1, vertice v2, vertice v3){
//    //puede que haya que cambiar el orden de los vectores
//    vertice ar1(v1.x - v3.x,v1.y - v3.y, v1.z - v3.z);
//    vertice ar2(v2.x - v3.x,v2.y - v3.y, v2.z - v3.z);
//    x = (ar1.y - ar2.z)* (ar2.y-ar1.z);
//    y = -(ar1.x - ar2.z)* (ar2.x-ar1.z);
//    z = (ar1.x - ar2.y)* (ar2.x-ar1.y);
//    //normalizamos
//    normaliza();
//  };
//  void add(normal n){
//    x = x+ n.x;
//    y = y+ n.y;
//    z = z+ n.z;
//    normaliza();
//  }

//};
//struct reflectividad{
//  float R,G,B,opacidad;
//  reflectividad(){
//    R = 0; 
//    G = 0; 
//    B = 0;
//    opacidad = 1;
//  }

//  reflectividad(float RR, float GG, float BB, float op){
//	R = RR; G = GG; B = BB; opacidad = op;
//  };

//};

#endif	


