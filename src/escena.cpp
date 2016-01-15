#ifndef _escenaCPP_
#define	_escenaCPP_
#include "escena.h"
escena::escena(){
  instancia = false;
};
bool escena::instanciado(){
  return instancia;
}
void escena::instanciar(int lados, char eje){
  dibujo = 3;
  instancia = true;
  lados = 50;
figuraSeleccionada=0;

  esfer = gluNewQuadric();
  eje = 'Y';
  //peon1
  peon1 = PLY("./modelos_ply/p2");
  peon1.cargarTextura("./texturas/text-madera.jpg");
  peon1.revolucionar(eje, lados, true);
  //  peon1.changeColor(1.0,1.0,1.0);
  peon1.trasladar(_vertex3f(0,0,3));
  //		//peon2
  peon2.load("./modelos_ply/p2");
  peon2.revolucionar(eje, lados,true);
  peon2.changeColor(1,1,1);
  peon2.trasladar(_vertex3f(3,0,3));

  //		//peon3
  peon3.load("./modelos_ply/p2");
  peon3.revolucionar(eje, lados,true);
  peon3.changeColor(0,0,0);
  peon3.trasladar(_vertex3f(-3,0,3));

  //tapa de la lata
  lata_tapa = PLY("./modelos_ply/lata-psup");
  //  lata_tapa.changeColor(0.2,0.3,0.3);
  lata_tapa.escalar(5);
  lata_tapa.trasladar(_vertex3f(0,-1.5,0));
  lata_tapa.revolucionar(eje, lados, false);
  //tronco de la lata
  lata_tronco = PLY("./modelos_ply/lata-pcue");
  lata_tronco.cargarTextura("./texturas/text-madera.jpg");
  //  lata_tronco.changeColor(1.0,1.0,1.0);
  lata_tronco.escalar(5);
  lata_tronco.trasladar(_vertex3f(0,-1.5,0));
  lata_tronco.revolucionar(eje, lados,false);
  //culo de la lata
  lata_culo = PLY("./modelos_ply/lata-pinf");
  //  lata_culo.changeColor(0.2,0.3,0.3);
  lata_culo.escalar(5);
  lata_culo.trasladar(_vertex3f(0,-1.5,0));
  lata_culo.revolucionar(eje, lados,false);
  //textura para la esfera
  jpg::Imagen * Textura = new jpg::Imagen("./texturas/text-madera.jpg");
  ID_text = _file_ply::loadTexture(Textura);
  delete Textura;
  esfera.esfera(10, 5);
  cuad.cargarTextura("./texturas/text-lata-1.jpg");
  cuad.initialize(20,20);
  //  cuad.changeColor(1,1,1);

  //objetos p5
  float escalado_beethoven = 0.5;
  float distancias_beethoven= 10;
  float levantamiento_beethoven=2.7;
  bet1.load("./modelos_ply/beethoven");
  bet1.trasladar(_vertex3f(-distancias_beethoven,levantamiento_beethoven,distancias_beethoven));
  bet1.escalar(escalado_beethoven);
  bet2.load("./modelos_ply/beethoven");
  bet2.trasladar(_vertex3f(0,levantamiento_beethoven,distancias_beethoven));
  bet2.escalar(escalado_beethoven);
  bet3.load("./modelos_ply/beethoven");
  bet3.trasladar(_vertex3f(distancias_beethoven,levantamiento_beethoven,distancias_beethoven));
  bet3.escalar(escalado_beethoven);
  bet4.load("./modelos_ply/beethoven");
  bet4.trasladar(_vertex3f(-distancias_beethoven,levantamiento_beethoven,-distancias_beethoven));
  bet4.escalar(escalado_beethoven);
  bet5.load("./modelos_ply/beethoven");
  bet5.trasladar(_vertex3f(0,levantamiento_beethoven,-distancias_beethoven));
  bet5.escalar(escalado_beethoven);
  bet6.load("./modelos_ply/beethoven");
  bet6.trasladar(_vertex3f(distancias_beethoven,levantamiento_beethoven,-distancias_beethoven));
  bet6.escalar(escalado_beethoven);

}



void escena::draw(char mode){
  //    materiall m;

  switch(dibujo){
  case 0:
    peon1.draw(mode);
    peon2.draw(mode);
    peon3.draw(mode);
    lata_tapa.draw(mode);
    lata_tronco.draw(mode);
    lata_culo.draw(mode);
    //referencia suelo
    glPushMatrix();
    glTranslatef(0,-1.7,0);
    glPushMatrix();
    glRotatef(-90,1,0,0);
    glTranslatef(-cuad.getAncho()*0.5,0,0);
    glTranslatef(0,-cuad.getAlto()*0.5,0);

    cuad.dibujar(mode);
    glPopMatrix();
    glPopMatrix();
    break;
  case 1: 
    if(esferaTextura){
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, ID_text);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      gluQuadricTexture(esfer,1);
    }
    else{
      //con esto no funcionan los materiales glEnable(GL_COLOR_MATERIAL);     
      glDisable(GL_TEXTURE_2D);
    }
    gluSphere (esfer, 4, 40, 40);
    //        esfera.draw(mode);
    break;
  case 2:
    cuad.dibujar(mode);
    break;
  case 3:
    //dibujamos los beethoven
    glPushMatrix();
    glLoadName(1);
    bet1.draw(mode);
    glPushMatrix();
    glPushMatrix();
    glLoadName(2);
    bet2.draw(mode);
    glPushMatrix();
    glPushMatrix();
    glLoadName(3);
    bet3.draw(mode);
    glPushMatrix();
    glPushMatrix();
    glLoadName(3);
    bet3.draw(mode);
    glPushMatrix();
    glPushMatrix();
    glLoadName(4);
    bet4.draw(mode);
    glPushMatrix();
    glPushMatrix();
    glLoadName(5);
    bet5.draw(mode);
    glPushMatrix();
    glPushMatrix();
    glLoadName(6);
    bet6.draw(mode);
    glPushMatrix();
    //referencia suelo
    glPushMatrix();
    glTranslatef(0,-1.7,0);
    glPushMatrix();
    glRotatef(-90,1,0,0);
    glTranslatef(-cuad.getAncho()*0.5,0,0);
    glTranslatef(0,-cuad.getAlto()*0.5,0);

    cuad.dibujar(mode);
    glPopMatrix();
    glPopMatrix();
    break;
  default: 
    break;
  }
}
void escena::cambiarEscena(){
  dibujo = (dibujo +1) % 4;
};

_vertex3f escena::centroGiro(){
_vertex3f cen(0,0,0);
switch(figuraSeleccionada){
case 1: cen=bet1.referenciaObjeto(); break;
case 2: cen=bet2.referenciaObjeto(); break;
case 3: cen=bet3.referenciaObjeto(); break;
case 4: cen=bet4.referenciaObjeto(); break;
case 5: cen=bet5.referenciaObjeto(); break;
case 6: cen=bet6.referenciaObjeto(); break;
}
return cen;
}

void escena::cambiarTexturaEsfera(){
  if(esferaTextura){
    gluQuadricTexture(esfer, GL_TRUE);
    esferaTextura = !esferaTextura;
  }
  else{
    esferaTextura = !esferaTextura;
    gluQuadricTexture(esfer, GL_FALSE);
  }
}

void escena::seleccionarFigura(int i){
  cout << "Se ha seleccionado el beethoven " << i<<endl;
  bet1.changeColor(1,1,1);
  bet2.changeColor(1,1,1);
  bet3.changeColor(1,1,1);
  bet4.changeColor(1,1,1);
  bet5.changeColor(1,1,1);
  bet6.changeColor(1,1,1);
  switch(i){
  case 1: 
    bet1.changeColor(1,0,0); 
figuraSeleccionada=1;
    break;
  case 2: 
    bet2.changeColor(1,0,0); 
figuraSeleccionada=2;
    break;
  case 3: 
    bet3.changeColor(1,0,0); 
figuraSeleccionada=3;
    break;
  case 4: 
    bet4.changeColor(1,0,0); 
figuraSeleccionada=4;
    break;
  case 5: 
    bet5.changeColor(1,0,0); 
figuraSeleccionada=5;
    break;
  case 6: 
    bet6.changeColor(1,0,0); 
figuraSeleccionada=6;
    break;
  default: 
    cerr << "ERROR EN LA SELECCION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl; 
    break;
  }

}


#endif






