#include "cuadro.h"



void cuadro::colocar_texturaExamen(int lados, int vperfil){


};

void cuadro::initialize(int xx, int yy){
  alto = yy;
  ancho = xx;
  int version = 0;
  int x = xx+1;
  int y = yy+1;
  if(xx < 3) x = 4;
  if(yy < 3) y = 4;
  if(version == 0){
    //v1
    vertices.resize(x*y);
    caras.resize(xx*yy*2);
    for(int i = 0,k=0,t=0; i < x; i++){
      for(int j= 0; j < y; j++,k++){
        vertices[k].x = i;
        vertices[k].y = j;
        vertices[k].z = 0.0;

        if(j != y-1 && i != x-1){
          caras[t].x=k;
          caras[t].y=k+1;
          caras[t].z=k+y;
          t++;
          caras[t].x=k+1;
          caras[t].y=k+1+y;
          caras[t].z=k+y;
          t++;

        }
      }
    }
  }
  else {
    //versión rateando puntos
    int tamanio = x*4+y*4-16;
    vertices.resize(tamanio);
    tamanio = xx*yy*2-((xx-2)*(yy-2)*2);
    caras.resize(tamanio);

    //indice vertices
    int k = 0;
    //indice caras
    int t = 0;
    //pilar 1
    for(int w = 0; w < 2; w++)
      for(int i = 0; i < y; i++,k++){
        vertices[k].x = w;//cambiar si queremos centrar
        vertices[k].y = i;//cambiar si queremos centrar
        vertices[k].z = 0.0;
        if(w != 1 ){
          if(i != y-1){
            caras[t].x=k;
            caras[t].y=k+1;
            caras[t].z=k+y;
            t++;
          }
          if(i > 0){
            caras[t].x=k;
            caras[t].y=k+y;
            caras[t].z=k+y-1;
            t++;
          }
        }	
        else{
          if(i==0){
            caras[t].x=k;
            caras[t].y=k+1;
            caras[t].z=k+y;
            t++;
            caras[t].x=k+1;
            caras[t].y=k+y;
            caras[t].z=k+y+1;
            t++;

          }
          else if(i == y-2){
            caras[t].x=k;
            caras[t].y=k+1;
            caras[t].z=k+4;
            t++;
            caras[t].x=k+1;
            caras[t].y=k+5;
            caras[t].z=k+4;
            t++;

          }
        }

      }
    for(int i = 1; i < x-1;i++){
      for(int j = 0; j < 4; j++){
        if(i > 1 && i < (x-2)){
          vertices[k].x = i;	
          vertices[k].z = 0.0;
          if(j < 2) vertices[k].y = j;
          else vertices[k].y = y +j-4;

          if(j%2 == 0){
            caras[t].x=k;
            caras[t].y=k+1;
            if(i != x-3 || j == 0) caras[t].z=k+4;
            else caras[t].z=k+y;
            t++;

            caras[t].x=k+1;
            if(i != x-3 || j == 0){
              caras[t].y=k+4;
              caras[t].z=k+5;
            }
            else{
              caras[t].y=k+y;
              caras[t].z=k+y+1;
            }
            t++;
          }


          k++;
          //	if(i < x-1 && j%2 != 0){
          //	    caras[t].x=k;
          //            caras[t].y=k+4;
          //            caras[t].z=k+3;
          //		t++;
          //	}

        }

      }
    }

    //pilar 2 (casi igual que el 1)
    for(int w = x-2; w < x; w++)
      for(int i = 0; i < y; i++,k++){
        vertices[k].x = w;
        vertices[k].y = i;
        vertices[k].z = 0.0;

        if(w != x-1 ){
          if(i != y-1){
            caras[t].x=k;
            caras[t].y=k+1;
            caras[t].z=k+y;
            t++;
          }
          if(i > 0){
            caras[t].x=k;
            caras[t].y=k+y;
            caras[t].z=k+y-1;
            t++;
          }
        }	
      }
  }

  //calcular coordenadas de textura
  //  calcularCoordenadasTextura(x,y);
  colocar_textura(x,y);



  calcularNormales();
  changeColor(1.0,0.2,0.7);
};

void cuadro::colocar_textura(int lados, int vperfil){
  lados = lados-2;
  vperfil = vperfil-2;
  vector<float> distancias;
  distancias.resize(vperfil);
  vtexturas.resize(0);
  float x,y,z,xtext, ytext;
  distancias[0]=0.0;
  //jugamos con qe tienen la misma separacion, 1
  for(int i = 1; i < vperfil; i++){
    x = vertices[i].x-vertices[i-1].x;
    y = vertices[i].y-vertices[i-1].y;
    z = vertices[i].z-vertices[i-1].z;
    distancias[i] = distancias[i-1] + sqrt(x*x+y*y+z*z);
  } 
  for(int i = 0; i < lados; i++){
    for(int j = vperfil-1; j >-1; j--){
      xtext = ((float)i)/(lados-1);
      ytext =distancias[j]/distancias[vperfil-1];
      vtexturas.push_back(vertice2D(xtext,ytext));
    }
  }
}


void cuadro::dibujar(char mode){
  if(mode == 's')
    dsolido();
  else
    draw(mode);

};

void cuadro::dsolido(){
  dbordes();
  dtextura();
};
void cuadro::dbordes(){
  glEnable(GL_COLOR_MATERIAL);
  glDisable(GL_TEXTURE_2D);

  int indice =alto*2+2;
  glBegin(GL_TRIANGLES);   
  for (int i=4;i<caras.size();i++){
    //    if(i == indice && i != caras.size() -alto*2+2){ 
    //      i=i+alto*2-5;
    //      indice+=alto*2;
    //    }
    //    else{
    if( i < 8 ||  i > 11){
      if(i % 2 == 0)
        glColor3f(0,0,0);
      else
        glColor3f(1,1,1);
      //      glNormal3f(nvertices[posv1].x, nvertices[posv1].y, nvertices[posv1].z);
      glVertex3fv((GLfloat *) &(vertices[caras[i].x]));
      glVertex3fv((GLfloat *) &(vertices[caras[i].y]));
      glVertex3fv((GLfloat *) &(vertices[caras[i].z]));
    }
    //    }
  }
  glEnd();

};
void cuadro::dtextura(){
  activarTexturas();

  glColor3f(R,G,B);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);   


  //  bool hay_normales=nvertices.size();
  //  int indice = alto+2;
  //  int indiceT=0;
  //  int pintada = alto-2;
  //  int auxi = 0;

  //  for(int i = 0; i < vtexturas.size(); i++)

  //    for(int i = indice; auxi < ancho-2; auxi++, i=i+indice-1){

  //      dibujarCarasExam(i,i+pintada,hay_normales,indiceT);
  //      indiceT++;
  //    }

  bool hay_normales=nvertices.size();
  int indice = 0;
  int indiceT=0;
  int pintada = 2;
  int auxi = 0;
  for(int i = 0; i < vtexturas.size(); i++)

    for(int i = indice; auxi < 2; auxi++, i=i+5){
      dibujarCarasExam(i,i+pintada,hay_normales,indiceT);
      indiceT++;
    }

  glEnd();
  glDisable(GL_TEXTURE_2D);

};

void cuadro::dibujarCaras(int principio, int final, bool hay_normales, int & indiceT){
  for (int i=final-1;i>principio-1;i--){

    int posv1=i;//6
    int posv2=posv1+1;//7
    int posv3=posv2+alto;//11
    int posv4=posv3+1;//12
    ///////
    //Pintamos una cara del cuadrado
    ///////
    glTexCoord2f(vtexturas[indiceT+1].x, vtexturas[indiceT+1].y); 
    if (hay_normales)
      glNormal3f(nvertices[posv1].x, nvertices[posv1].y, nvertices[posv1].z);
    //pintamos v1_      
    glVertex3f(vertices[posv1].x, vertices[posv1].y, vertices[posv1].z);

    glTexCoord2f(vtexturas[indiceT].x, vtexturas[indiceT].y); 
    if (hay_normales)
      glNormal3f(nvertices[posv2].x, nvertices[posv2].y, nvertices[posv2].z);
    //pintamos v2_
    glVertex3f(vertices[posv2].x, vertices[posv2].y, vertices[posv2].z);

    glTexCoord2f(vtexturas[indiceT+alto].x, vtexturas[indiceT+alto].y);
    if (hay_normales)
      glNormal3f(nvertices[posv3].x, nvertices[posv3].y, nvertices[posv3].z);
    //pintamos v3            
    glVertex3f(vertices[posv3].x, vertices[posv3].y, vertices[posv3].z);
    ///////
    //Pintamos la otra cara del cuadrado
    ///////

    glTexCoord2f(vtexturas[indiceT+alto].x, vtexturas[indiceT+alto].y);
    if (hay_normales)
      glNormal3f(nvertices[posv3].x, nvertices[posv3].y, nvertices[posv3].z);
    //pintamos v3            
    glVertex3f(vertices[posv3].x, vertices[posv3].y, vertices[posv3].z);

    glTexCoord2f(vtexturas[indiceT].x, vtexturas[indiceT].y); 
    if (hay_normales)
      glNormal3f(nvertices[posv2].x, nvertices[posv2].y, nvertices[posv2].z);
    //pintamos v2_      
    glVertex3f(vertices[posv2].x, vertices[posv2].y, vertices[posv2].z);

    glTexCoord2f(vtexturas[indiceT+alto-1].x, vtexturas[indiceT+alto-1].y); 
    if (hay_normales)
      glNormal3f(nvertices[posv4].x, nvertices[posv4].y, nvertices[posv4].z);
    //pintamos v4_
    glVertex3f(vertices[posv4].x, vertices[posv4].y, vertices[posv4].z);
    indiceT++;
  }
}

void cuadro::dibujarCarasExam(int principio, int final, bool hay_normales, int & indiceT){
  for (int i=final-1;i>principio-1;i--){

    int posv1=i;//6
    int posv2=posv1+1;//7
    int posv3=posv2+alto;//11
    int posv4=posv3+1;//12
    ///////
    //Pintamos una cara del cuadrado
    ///////
    glTexCoord2f(vtexturas[indiceT+1].x, vtexturas[indiceT+1].y); 
    if (hay_normales)
      glNormal3f(nvertices[posv1].x, nvertices[posv1].y, nvertices[posv1].z);
    //pintamos v1_      
    glVertex3f(vertices[posv1].x, vertices[posv1].y, vertices[posv1].z);

    glTexCoord2f(vtexturas[indiceT].x, vtexturas[indiceT].y); 
    if (hay_normales)
      glNormal3f(nvertices[posv2].x, nvertices[posv2].y, nvertices[posv2].z);
    //pintamos v2_
    glVertex3f(vertices[posv2].x, vertices[posv2].y, vertices[posv2].z);

    glTexCoord2f(vtexturas[indiceT+alto].x, vtexturas[indiceT+alto].y);
    if (hay_normales)
      glNormal3f(nvertices[posv3].x, nvertices[posv3].y, nvertices[posv3].z);
    //pintamos v3            
    glVertex3f(vertices[posv3].x, vertices[posv3].y, vertices[posv3].z);
    ///////
    //Pintamos la otra cara del cuadrado
    ///////

    glTexCoord2f(vtexturas[indiceT+alto].x, vtexturas[indiceT+alto].y);
    if (hay_normales)
      glNormal3f(nvertices[posv3].x, nvertices[posv3].y, nvertices[posv3].z);
    //pintamos v3            
    glVertex3f(vertices[posv3].x, vertices[posv3].y, vertices[posv3].z);

    glTexCoord2f(vtexturas[indiceT].x, vtexturas[indiceT].y); 
    if (hay_normales)
      glNormal3f(nvertices[posv2].x, nvertices[posv2].y, nvertices[posv2].z);
    //pintamos v2_      
    glVertex3f(vertices[posv2].x, vertices[posv2].y, vertices[posv2].z);

    glTexCoord2f(vtexturas[indiceT+alto-1].x, vtexturas[indiceT+alto-1].y); 
    if (hay_normales)
      glNormal3f(nvertices[posv4].x, nvertices[posv4].y, nvertices[posv4].z);
    //pintamos v4_
    glVertex3f(vertices[posv4].x, vertices[posv4].y, vertices[posv4].z);
    indiceT++;
  }
}












