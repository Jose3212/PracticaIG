#ifndef _camaraCPP_
#define	_camaraCPP_
#include "camaraOrtho.h"


camaraOrtho::camaraOrtho(){
  ortogonal = false;
  examinar = false;
  esferica = false;
}

void camaraOrtho::cambiarEsferica(){
reset();
  esferica = !esferica;
}

camaraOrtho::camaraOrtho(float x, float y, float z, float m_x, float m_y, float m_z, float vo_x, float vo_y, float vo_z, float an_x,float an_y,float an_z){
  ortogonal = false;
  examinar = false;
  esferica = false;
  //PARÁMETROS LOOK AT
  obs_x=x;
  obs_y=y; 
  obs_z=z; 
  //PARÁMETROS QUE NO USO SIN LOOK AT
  mirada_x=m_x; 
  mirada_y=m_y; 
  mirada_z=m_z; 
  vec_obs_x=vo_x; 
  vec_obs_y=vo_y; 
  vec_obs_z=vo_z;
  //FIN DE PARÁMETROS QUE NO USO SIN LOOK AT
  //FIN DE PARÁMETROS LOOK AT
  ang_x = an_x;
  ang_y = an_y;
  ang_z = an_z;
  //GUARDAMOS PARA RESET
  backupValores.reserve(12);
  backupValores.push_back(obs_x);
  backupValores.push_back(obs_y);
  backupValores.push_back(obs_z);
  backupValores.push_back(mirada_x);
  backupValores.push_back(mirada_y);
  backupValores.push_back(mirada_z);
  backupValores.push_back(vec_obs_x);
  backupValores.push_back(vec_obs_y);
  backupValores.push_back(vec_obs_z);
  backupValores.push_back(ang_x);
  backupValores.push_back(ang_y);
  backupValores.push_back(ang_z);

}

void camaraOrtho::setProyeccion(float a,float b, float c, float d, float e, float f){
izquierda=a;
derecha=b;
abajo=c;
arriba=d;
cerca=e;
lejos=f;
}

void camaraOrtho::cambiarProyeccion(int p){
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
cout << "izquierda: "<< izquierda<<"derecha"<< derecha<<"abajo"<< abajo<<"arriba: "<< arriba<<"cerca"<< cerca<<"lejos"<< lejos<<endl;
  switch(p){
  case 0:
    ortogonal = false;
    cout << "Frustum"<<endl;

    glFrustum(izquierda,derecha,abajo,arriba,cerca,lejos);
    break;
  case 1:
    ortogonal = true;
    cout << "Ortogonal"<<endl;

    glOrtho(izquierda*zoom,derecha*zoom,abajo*zoom,arriba*zoom,cerca,lejos);
    break;
  }
};

void camaraOrtho::activarExplorar(_vertex3f puntoGiro){
//explorar = true;
esferica = true;
//FAIO
//obs_x = puntoGiro.x;
//obs_y = puntoGiro.y;
//obs_z = puntoGiro.z;
obs_x = 5;
obs_y = 0;
obs_z = 10;
}
void camaraOrtho::setObservador(){
  //  cout << "Translada " << -obs_x << " " << -obs_y << "     "<<-obs_z<<endl;
  if(ortogonal){
//    cout << "observador ortogonal"<<endl;
    cout << " obs_x " << obs_x << " obs_y " << obs_y << " obs_z " << obs_z << " mirada_x " << mirada_x << " mirada_y " << mirada_y << " mirada_z " << mirada_z << "vec_obs_x: " << vec_obs_x << "vec_obs_y: " << vec_obs_y << "vec_obs_z: " << vec_obs_z<<endl;
    gluLookAt (obs_x, obs_y, obs_z, mirada_x, mirada_y, mirada_z, vec_obs_x, vec_obs_y, vec_obs_z);
  }
  else{
//    cout << "observador no ortogonal"<<endl;

    if(esferica){
      glTranslated(-obs_x,-obs_y,-obs_z);
      glRotatef(ang_x,1,0,0);
      glRotatef(ang_y,0,1,0);
    }
    else{
      glRotatef(ang_x,1.0,0.0,0.0); 
      glRotatef(ang_y,0.0,1.0,0.0);
      glTranslated(-obs_x,-obs_y,-obs_z);
    }
  }


};

void camaraOrtho::girar(float x, float y){
  //ratonEstatico(x, y);
  if(ortogonal){
    obs_x -=x;
    obs_z -=y;
    mirada_x-=x;
    mirada_z-=y;
  }
  else{
    ang_x+=y;
    ang_y+=x;
  }
}

void camaraOrtho::desplazar(char movimiento){
if(!esferica)
  if(!ortogonal){
    float xrotrad, yrotrad;
    switch(movimiento){
    case 's':

      yrotrad = (ang_y / 180 * 3.141592654f);
      xrotrad = (ang_x/ 180 * 3.141592654f); 
      obs_x -= float(sin(yrotrad));
      obs_z += float(cos(yrotrad)) ;
      obs_y += float(sin(xrotrad));
      break;
    case 'a':
      yrotrad = (ang_y / 180 * 3.141592654f);
      obs_x -= float(cos(yrotrad)) * 0.2;
      obs_z -= float(sin(yrotrad)) * 0.2;
      break;
    case 'd':
      yrotrad = (ang_y / 180 * 3.141592654f);
      obs_x += float(cos(yrotrad)) * 0.2;
      obs_z += float(sin(yrotrad)) * 0.2;
      break;
    case 'w':
      yrotrad = (ang_y / 180 * 3.141592654f);
      xrotrad = (ang_x / 180 * 3.141592654f); 
      obs_x += float(sin(yrotrad)) ;
      obs_z -= float(cos(yrotrad)) ;
      obs_y -= float(sin(xrotrad)) ;
      break;

    }
  }
else{
    switch(movimiento){
    case 's':
cout << "obs_y ortogonal" << obs_y << endl;
	zoom+= 1;
      break;
    case 'w':
cout << "obs_y ortogonal" << obs_y << endl;
	zoom-= 1;
      break;
    }

cambiarProyeccion(ortogonal);
}
}
void camaraOrtho::reset(){
  obs_x=backupValores[0];
  obs_y=backupValores[1];
  obs_z=backupValores[2];
  mirada_x=backupValores[3];
  mirada_y=backupValores[4];
  mirada_z=backupValores[5];
  vec_obs_x=backupValores[6];
  vec_obs_y=backupValores[7];
  vec_obs_z=backupValores[8];
  ang_x=backupValores[9];
  ang_y=backupValores[10];
  ang_z=backupValores[11];

}


#endif	















