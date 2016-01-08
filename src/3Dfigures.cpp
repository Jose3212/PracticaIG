#include "3Dfigures.h"
_vertex3f figura3D::normaliza(_vertex3f v){
  _vertex3f j;
  //    cout << "vertice v: " << v.x << " " << v.y << " " << v.z <<endl;
  float dis = sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
  //    cout << "dis: " << dis << endl;
  j.x = v.x/dis;
  j.y = v.y/dis;
  j.z = v.z/dis;
  //    cout << "vertice j: " << j.x << " " << j.y << " " << j.z <<endl;
  //	cout << "vector normalizado1: " << j.x << " " << j.y << " " << j.z << " " <<endl;
  return j;
}

void figura3D::calcularNormales(){
  calcularNCaras();
  calcularNVertices();
}

//p4
void figura3D::drawNormales() 
{
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  float longitud_normales = 0.2;
  //	cout << "check1"<<endl;
  glPointSize(3);
  glColor3f(0, 0, 1);
  glBegin(GL_LINES);

  //	cout << "vertices: "<< vertices.size() << " nvertices: " <<nvertices.size()<<endl;
  for (int i= 0; i < nvertices.size(); i++)
  {
    _vertex3f v1( vertices[i].x, vertices[i].y, vertices[i].z);
    _vertex3f v2(v1.x + longitud_normales * nvertices[i].x, v1.y + longitud_normales * nvertices[i].y, v1.z + longitud_normales * nvertices[i].z);
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    //		glNormal3f(ncaras[i].x,ncaras[i].y,ncaras[i].z);
  }

  glEnd();

}


void figura3D::calcularNCaras(){
  ncaras.resize(caras.size());
  _vertex3f v1,v2,v3,ar1,ar2,normal;
  for(int i = 0; i < caras.size(); i++){
    //sacamos los vertices que componen la cara
    v1 = vertices[caras[i].x];
    v2 = vertices[caras[i].y];
    v3 = vertices[caras[i].z];
    //	cout << "Cara " << i << ": " << endl << "	P1: x= " << v1.x << " y= " << v1.y << " z= " << v1.z << endl<<"	P2: x= " << v2.x << " y= " << v2.y << " z= " << v2.z <<endl<< "	P3: x= " << v3.x << " y= " << v3.y << " z= " << v3.z << endl<<endl;
    //esto puede ser al revés /////////////////////////////////////////////////////
    ar1.x=v2.x - v1.x;
    ar1.y = v2.y - v1.y;
    ar1.z = v2.z - v1.z;
    ar2.x = v2.x - v3.x;
    ar2.y=v2.y - v3.y;
    ar2.z= v2.z - v3.z;
    //      ar1.x=v1.x - v3.x;
    //      ar1.y = v1.y - v3.y;
    //      ar1.z = v1.z - v3.z;
    //      ar2.x = v1.x - v2.x;
    //      ar2.y=v1.y - v2.y;
    //      ar2.z= v1.z - v2.z;

    //producto vectorial
    normal.x = ar1.y*ar2.z-ar1.z*ar2.y;
    normal.y = ar1.z*ar2.x-ar1.x*ar2.z;
    normal.z = ar1.x*ar2.y-ar1.y*ar2.x;
    //normalizamos y al vector
    ncaras[i]=normaliza(normal);
    //	cout << "vector caras normalizado2: " << ncaras[i].x << " " << ncaras[i].y << " " << ncaras[i].z << " " <<endl;
    //      cout << "NCARAS " << i << ": x= " << ncaras[i].x << " y= " << ncaras[i].y << " z= " << ncaras[i].z<<endl;
  }
}
void figura3D::calcularNVertices(){

  // Generamos las normales de los vertices

    vector<_vertex3f> normales_vertices;


  // Recorremos los vertices
  for(int i = 0; i < vertices.size(); i++)
  {

    _vertex3f verticeactual = vertices[i];
    _vertex3f normal(0,0,0);

    // Recorremos las caras
    for(int h = 0; h < caras.size(); h++)
    {
      // Comprobamos si el vertice esta en otra cara (por la posicion)
      if (caras[h].x == i || caras[h].y == i || caras[h].z == i)
      {
        normal = _vertex3f(normal.x + ncaras[h].x,
        normal.y + ncaras[h].y,
        normal.z + ncaras[h].z);
      }

    }

    // Antonio para normalizar
    float modulo=sqrt(normal.x*normal.x+normal.y*normal.y+normal.z*normal.z);
    normal.x=normal.x/modulo;
    normal.y=normal.y/modulo;
    normal.z=normal.z/modulo;
    // Fin Antonio

      // La agregago al vector
    normales_vertices.push_back(normal);
  }

  nvertices =normales_vertices;

}

void figura3D::cargarTextura(const string & im){
  //	if(pimg == NULL){
//  cout << "Cargando textura " << im <<endl;
  pimg = new jpg::Imagen(im);
  if (pimg != NULL){
    tamx = pimg->tamX(); 
    tamy = pimg->tamY(); 
    texels = pimg->leerPixels(); 
  }
  else cerr << "Error: error cargando la textura" <<endl;
  //	} else cerr << "Error: texturas ya cargadas" <<endl;
}
void figura3D::calcularCoordenadasTextura(int lados, int vperfil){
  if(pimg != NULL){
    vector<float> distancias;
    distancias.reserve(vperfil);
    float x,y,z,xtext, ytext;
    distancias[0]=0.0;
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

}

void figura3D::escalar(float es){
  for(int i = 0; i < vertices.size(); i++){
    vertices[i].x = vertices[i].x * es;
    vertices[i].y = vertices[i].y * es;
    vertices[i].z = vertices[i].z * es;
  }

};

vector<_vertex3f> figura3D::getVertices(){
  return vertices;
};
vector <cara> figura3D::getCaras(){
  return caras;
};

void figura3D::changeColor(float RR, float GG, float BB){
  R = RR; 
  G = GG; 
  B = BB;
}

figura3D::figura3D(){

  changeColor(1,1,1);
  //test
  //  	centro.x = 0.0;
  //	centro.y = 0.0;
  //	centro.z = 0.0;

}


void figura3D::esfera(int lados, float rad){
  vertices.resize(0);
  _vertex3f aux1(rad,0,0);
  vertices.push_back(aux1);
  //creamos el perfil de la circunferencia girando sobre el eje Y
  int tam = 1;
  int tamFinal=tam*lados+1;
  float radianesA = (270/M_PI) * 180;
  float radianesB = (90/M_PI) * 180;
  float incrementoGrados = (270 - 90)/(lados); 
  float cosa, sina;  
  vector <_vertex3f> auxV = vertices;
  float alpha = radianesA;
  for(int i = 0; i <= lados; i++){
    alpha = ( ((float) (incrementoGrados*i + 270)) *M_PI) / 180;
    cosa = cos(alpha);
    sina = sin(alpha);
    for(int j = 0; j < tam; j++){
      _vertex3f vaux((cosa * auxV[j].x) + (sina * auxV[j].z), auxV[j].y, -(sina * auxV[j].x) + (cosa * auxV[j].z));
      vertices.push_back(vaux);
    }
  }
  //creamos la esfera rotando el perfil a través del eje Z
  revolucionar('Z', lados, true);
  invertirNormales();
};

void figura3D::invertirNormales(){
  for (int i= 0; i < nvertices.size(); i++)
  {
    vertices[i].x = -vertices[i].x;
    vertices[i].y = -vertices[i].y;
    vertices[i].z = -vertices[i].z;
  }

};

void figura3D::trasladar(_vertex3f cen){
  for(int i = 0; i < vertices.size(); i++){
    vertices[i].x += cen.x;
    vertices[i].y += cen.y;
    vertices[i].z += cen.z;
  }
}

void figura3D::revolucionar_seccion(char eje_rotador, int lados, float  anguloA, float anguloB){
  //booleanos que indicarán si hace falta cerrar la figura por los extremos
  bool modificarAbajo=true,modificarArriba=true;
  //esta variable nos dirá cada cuantos grados colocaremos un punto
  float grados = 360.0/ ((float) lados);
  float alpha = 0.0;
  int tam = vertices.size();
  int tamFinal;

  //Vemos si tenemos que cerrar el circuito por arriba
  if(((eje_rotador=='X'))&&(vertices[0].z==0.0)&&(vertices[0].y==0.0))
    modificarArriba=false;
  else if(((eje_rotador=='Y'))&&(vertices[0].z==0.0)&&(vertices[0].x==0.0))
    modificarArriba=false;
  else if(((eje_rotador=='Z'))&&(vertices[0].x==0.0)&&(vertices[0].y==0.0))
    modificarArriba=false;
  //Vemos si tenemos que cerrar el circuito por abajo
  if(((eje_rotador=='X'))&&(vertices[tam-1].z==0.0)&&(vertices[tam-1].y==0.0))
    modificarAbajo=false;
  else if(((eje_rotador=='Y'))&&(vertices[tam-1].z==0.0)&&(vertices[tam-1].x==0.0))
    modificarAbajo=false;
  else if(((eje_rotador=='Z'))&&(vertices[tam-1].x==0.0)&&(vertices[tam-1].y==0.0))
    modificarAbajo=false;
  //calculamos lo que tenemos que reservar

  if(modificarArriba&&modificarAbajo) 
    tamFinal=((2+tam)*lados);
  else if (modificarArriba||modificarAbajo) 
    tamFinal=((tam+1)*lados);
  else 
    tamFinal=tam*lados;
  vertices.resize(tamFinal);
  //ajustamos el tamaño del perfil
  int tam2=tam;
  tam=tam+modificarArriba+modificarAbajo;

  //    if(modificarArriba) cout << "\nTapa arriba" <<endl;
  //    if(modificarAbajo) cout << "\nTapa ABAJO" <<endl;

  if(modificarAbajo){
    if((eje_rotador=='X')){
      _vertex3f aux(vertices[tam2-1].x, 0.0, 0.0);
      vertices.at(tam2) = aux;
    }
    else if((eje_rotador=='Y')){	
      _vertex3f aux(0.0, vertices[tam2-1].y, 0.0);
      vertices.at(tam2) = aux;
    }
    else if((eje_rotador=='Z')){	
      _vertex3f aux(0.0, 0.0, vertices[tam2-1].z);
      vertices.at(tam2) = aux;
    }

  }

  if(modificarArriba){
    if((eje_rotador=='X')){
      _vertex3f aux(vertices[0].x, 0.0, 0.0);
      vertices.insert(vertices.begin(), aux);

    }
    else if((eje_rotador=='Y')){	
      _vertex3f aux(0.0, vertices[0].y, 0.0);
      vertices.insert(vertices.begin(), aux);
    }
    else if((eje_rotador=='Z')){	
      _vertex3f aux(0.0, 0.0, vertices[0].z);
      vertices.insert(vertices.begin(), aux);
    }
    vertices.resize(vertices.size()-1);
  }

  //modificación examen
  float radianesA = (anguloA/M_PI) * 180;
  float radianesB = (anguloB/M_PI) * 180;
  float incrementoGrados = (anguloB - anguloA)/(lados); 
  float radianesIncremento = (incrementoGrados/M_PI)*180;

  float cosa,sina;
  //creamos el primer perfil
  vector <_vertex3f> auxV = vertices;
  vertices.resize(0);
  vertices.resize(tam);
  alpha = radianesA;
  for(int i = 0; i <= lados; i++){
    alpha = ( ((float) (incrementoGrados*i + anguloA)) *M_PI) / 180;
    cosa = cos(alpha);
    sina = sin(alpha);
    for(int j = 0; j < tam; j++){
      _vertex3f vaux((cosa * auxV[j].x) + (sina * auxV[j].z), auxV[j].y, -(sina * auxV[j].x) + (cosa * auxV[j].z));
      vertices.push_back(vaux);
    }
  }


  //FIN DE GENERAIÓN DE VÉRTICES

  //GENERAMOS LAS CARAS DEL OBJETO

  //RESIZE DE LAS CARAS
  caras.resize(2*(tam-1)*lados);

  //creamos las caras
  int cont=0;
  for(int i = 0; i < tamFinal-1; i++){
    if (((i+1)%(tam)==0) && (i != 0))
      i++;
    cara aux(i, i+1, (i + tam)%tamFinal );
    cara aux2( (i + tam)%tamFinal, i +1,  (i + tam +1)%tamFinal);
    caras[cont]= aux;
    caras[cont+1]=aux2;
    cont+=2;

  }

  //  cout << "Normales caras antes: " << ncaras.size() << " normales vertices antes: " << nvertices.size()<<endl;
  calcularNormales();
  //  cout << "Normales caras ahora: " << ncaras.size() << " normales vertices ahora: " << nvertices.size()<<endl;

}

//MODIFICACIÓN PROPUESTA POR EL PROFESOR

void figura3D::revolucionar(char eje_rotador, int lados, bool tapa){

  //booleanos que indicarán si hace falta cerrar la figura por los extremos
  bool modificarAbajo=false,modificarArriba=false;
  //esta variable nos dirá cada cuantos grados colocaremos un punto
  float grados = 360.0/ ((float) lados);
  float alpha = 0.0;
  int tam = vertices.size();
  int tamFinal;
  if(tapa){
    modificarAbajo=modificarArriba=true;
    //Vemos si tenemos que cerrar el circuito por arriba
    if(((eje_rotador=='X'))&&(vertices[0].z==0.0)&&(vertices[0].y==0.0))
      modificarArriba=false;
    else if(((eje_rotador=='Y'))&&(vertices[0].z==0.0)&&(vertices[0].x==0.0))
      modificarArriba=false;
    else if(((eje_rotador=='Z'))&&(vertices[0].x==0.0)&&(vertices[0].y==0.0))
      modificarArriba=false;
    //Vemos si tenemos que cerrar el circuito por abajo
    if(((eje_rotador=='X'))&&(vertices[tam-1].z==0.0)&&(vertices[tam-1].y==0.0))
      modificarAbajo=false;
    else if(((eje_rotador=='Y'))&&(vertices[tam-1].z==0.0)&&(vertices[tam-1].x==0.0))
      modificarAbajo=false;
    else if(((eje_rotador=='Z'))&&(vertices[tam-1].x==0.0)&&(vertices[tam-1].y==0.0))
      modificarAbajo=false;
  }
  //alteración de prueba
  //      modificarAbajo = false;
  //      modificarArriba = false;
  //fin de la alteración de prueba

  //con esta modificación evitamos las tapas, que no quedan bien en la lata de la p4
  //calculamos lo que tenemos que reservar
  if(modificarArriba&&modificarAbajo) 
    tamFinal=((2+tam)*lados);
  else if (modificarArriba||modificarAbajo) 
    tamFinal=((tam+1)*lados);
  else 
    tamFinal=tam*lados;
  vertices.resize(tamFinal);
  //ajustamos el tamaño del perfil
  int tam2=tam;
  tam=tam+modificarArriba+modificarAbajo;

  //    if(modificarArriba) cout << "\nTapa arriba" <<endl;
  //    if(modificarAbajo) cout << "\nTapa ABAJO" <<endl;

  if(modificarAbajo){
    if((eje_rotador=='X')){
      _vertex3f aux(vertices[tam2-1].x, 0.0, 0.0);
      vertices.at(tam2) = aux;
    }
    else if((eje_rotador=='Y')){	
      _vertex3f aux(0.0, vertices[tam2-1].y, 0.0);
      vertices.at(tam2) = aux;
    }
    else if((eje_rotador=='Z')){	
      _vertex3f aux(0.0, 0.0, vertices[tam2-1].z);
      vertices.at(tam2) = aux;
    }

  }

  if(modificarArriba){
    if((eje_rotador=='X')){
      _vertex3f aux(vertices[0].x, 0.0, 0.0);
      vertices.insert(vertices.begin(), aux);

    }
    else if((eje_rotador=='Y')){	
      _vertex3f aux(0.0, vertices[0].y, 0.0);
      vertices.insert(vertices.begin(), aux);
    }
    else if((eje_rotador=='Z')){	
      _vertex3f aux(0.0, 0.0, vertices[0].z);
      vertices.insert(vertices.begin(), aux);
    }
    vertices.resize(vertices.size()-1);
  }




  //procedemos a hacer la revolución
  float cosa,sina;
  for (int i = 1; i < lados; i++){
    alpha = (((float) i) * 2.0 * M_PI) / ((float) lados);
    cosa = cos(alpha);
    sina = sin(alpha);
    for(int j = 0; j < tam; j++){
      if(eje_rotador == 'X'){
        vertices[(i*tam)+j].x = vertices[j].x;
        vertices[(i*tam)+j].y = (cosa * vertices[j].y) - (sina * vertices[j].z);
        vertices[(i*tam)+j].z = (sina * vertices[j].y) + (cosa * vertices[j].z);
      }
      else if(eje_rotador == 'Y'){
        vertices[(i*tam)+j].x = (cosa * vertices[j].x) + (sina * vertices[j].z);
        vertices[(i*tam)+j].y = vertices[j].y;
        vertices[(i*tam)+j].z = -(sina * vertices[j].x) + (cosa * vertices[j].z);
      }
      else if(eje_rotador == 'Z'){
        vertices[(i*tam)+j].x = (cosa * vertices[j].x) - (sina * vertices[j].y);
        vertices[(i*tam)+j].y = (sina * vertices[j].x) + (cosa * vertices[j].y);
        vertices[(i*tam)+j].z =vertices[j].z;
      }
      else{
        cerr << "\nError: eje no valido"<<endl;
      }

    }	

  }

  //FIN DE GENERAIÓN DE VÉRTICES

  //GENERAMOS LAS CARAS DEL OBJETO

  //RESIZE DE LAS CARAS
  caras.resize(2*(tam-1)*lados);
  //creamos las caras
  int cont=0;
  for(int i = 0; i < tamFinal-1; i++){
    if (((i+1)%(tam)==0) && (i != 0))
      i++;
    cara aux(i, i+1, (i + tam)%tamFinal );
    cara aux2( (i + tam)%tamFinal, i +1,  (i + tam +1)%tamFinal);
    caras[cont]= aux;
    caras[cont+1]=aux2;
    cont+=2;

  }
  calcularCoordenadasTextura(lados, tam);

  //  cout << "Normales caras antes: " << ncaras.size() << " normales vertices antes: " << nvertices.size()<<endl;
  calcularNormales();
  //  cout << "Normales caras ahora: " << ncaras.size() << " normales vertices ahora: " << nvertices.size()<<endl;

}




void figura3D::draw( char modo){
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //      	if(nvertices.size() > 0)
  //              drawNormales();
  //posible resultado similar por defecto
  //  glShadeModel(GL_SMOOTH);
  if (pimg != NULL)
  {
    //	cout << "Dibuja textura" <<endl;
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tamx, tamy, 0, GL_RGB, GL_UNSIGNED_BYTE, texels);
    //-
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    //por si quedase espacio sin rellenar, REPEAT ( no tablero)
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_COLOR_MATERIAL);
  }
  else
  {
    //	cout << "Desactiva textura" <<endl;
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);
  }

  switch(modo){
  case 'p' : 
    draw_vertice();  
    break;
  case 'a' : 
    draw_alambre();
    break;
  case 's' : 
    draw_solido(); 
    break;
  case 'c' : 
    draw_ajedrez(); 
    break;
  case 'm' : 
    draw_solido();
    draw_vertice();
    draw_alambre();
    break;

  default: 
    cerr << "\nError: ningún modo válido de dibujo seleccionado" <<endl;
  }

};

void figura3D::draw_solido(){
  glColor3f(R,G,B);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);   
  bool hay_texturas = vtexturas.size();
  bool hay_normales = nvertices.size();
  for (int i=0;i<caras.size();i++){
    int posv1 = caras[i].x; 
    int posv2 = caras[i].y;
    int posv3 = caras[i].z; 


    if (hay_texturas && vtexturas[posv1].x != -1)
      glTexCoord2f(vtexturas[posv1].x, vtexturas[posv1].y);
    if (hay_normales)
      glNormal3f(nvertices[posv1].x, nvertices[posv1].y, nvertices[posv1].z);
    //pintamos v1      
    glVertex3f(vertices[posv1].x, vertices[posv1].y, vertices[posv1].z);

    if (hay_texturas&& vtexturas[posv2].x != -1)
      glTexCoord2f(vtexturas[posv2].x, vtexturas[posv2].y);
    if (hay_normales)
      glNormal3f(nvertices[posv2].x, nvertices[posv2].y, nvertices[posv2].z);
    //pintamos v2
    glVertex3f(vertices[posv2].x, vertices[posv2].y, vertices[posv2].z);
    if (hay_texturas&& vtexturas[posv3].x != -1)
      glTexCoord2f(vtexturas[posv3].x, vtexturas[posv3].y);
    if (hay_normales)
      glNormal3f(nvertices[posv3].x, nvertices[posv3].y, nvertices[posv3].z);
    //pintamos v3            
    glVertex3f(vertices[posv3].x, vertices[posv3].y, vertices[posv3].z);

  }
  glEnd();
  glDisable(GL_TEXTURE_2D);

};

void figura3D::draw_vertice(){
  glColor3f(R,G,B);
  glPointSize(4);
  glBegin(GL_POINTS);
  for (int i=0;i<vertices.size();i++)
    glVertex3fv((GLfloat *) &vertices[i]);

  glEnd();
};

void figura3D::draw_ajedrez(){

  glBegin(GL_TRIANGLES);   
  for (int i=0;i<caras.size();i++){
    if(i % 2 == 0)
      glColor3f(R,G,B);
    else
      glColor3f(B,-R,G);

    glVertex3fv((GLfloat *) &(vertices[caras[i].x]));
    glVertex3fv((GLfloat *) &(vertices[caras[i].y]));
    glVertex3fv((GLfloat *) &(vertices[caras[i].z]));
  }
  glEnd();

}
void figura3D::draw_alambre(){
  glColor3f(R,G,B);

  glBegin(GL_LINES);
  for (int i=0;i<caras.size();i++){

    glVertex3fv((GLfloat *) &(vertices[caras[i].x]));
    glVertex3fv((GLfloat *) &(vertices[caras[i].y]));

    glVertex3fv((GLfloat *) &(vertices[caras[i].y]));
    glVertex3fv((GLfloat *) &(vertices[caras[i].z]));

    glVertex3fv((GLfloat *) &(vertices[caras[i].x]));
    glVertex3fv((GLfloat *) &(vertices[caras[i].z]));

  }

  glEnd();
};




