#include "jerarquia.hpp"
Jerarquia::Jerarquia(vector <Modelo> figuras){
    this-> figuras = figuras;
    numero_figuras = figuras.size();
}
void Jerarquia::dibujar(int j){
    for(int i=0; i < numero_figuras; i++){
        figuras[i].drawModel(j);
    }
}
void Jerarquia::aniade_figura(Modelo figura){
    figuras.push_back(figura);
    numero_figuras++;
}
Jerarquia::Jerarquia(){
    numero_figuras = 0;
}
void Jerarquia::senialar(int i){
    if(trans < 5&&tipo == 0){
        trans++;
    }
    else{
        trans--;
        tipo=1;
    }
    if(trans < -5){
        tipo=0;
    }
    if(angle != -90){
        angle = angle - 5;
    }
    glMatrixMode(GL_MODELVIEW);
    for(int n = 1; n< 5; n++){
        glPushMatrix();
        glTranslatef(trans,trans,0);
        if(n!=1)glRotatef(angle,1,0,0);
        else glRotatef(angle/2,0,0,1);
        figuras[n].drawModel(i);
        glPopMatrix();
    }
    glPushMatrix();
    glTranslatef(trans,trans,0);
    glRotatef(-90,0,1,0);
    //glRotatef(-45,0,0,1);
    figuras[0].drawModel(i);
    glPopMatrix();
    for(int n = 5; n < figuras.size(); n++){
        glPushMatrix();
        glTranslatef(trans,trans,0);
        glRotatef(-45,0,0,1);
        figuras[n].drawModel(i);
        glPopMatrix();
    }
}
void Jerarquia::barcenas(int i){
//    if(trans < 1){
//        trans+=-0.1;
//    }
    if(angle > -90&&tipo == 0){
        angle-=5;
    }
    else{
        angle+=5;
        tipo=1;
    }
    if(angle > 0){
        tipo=0;
    }
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    for(int n = 0; n <5;n++){
    glPushMatrix();
    if(n==0){
        glRotatef(angle,0,1,0);
//        glTranslatef(0,0,trans);
    }
    if(n>0 && n!=2) {
        glRotatef(angle,1,0,0);
//        glTranslatef(0,0,trans);
    }
    figuras[n].drawModel(i);
    glPopMatrix();
    }
    figuras[5].drawModel(i);
    figuras[6].drawModel(i);
}
void Jerarquia::saludar(int i){
    if(angle < 25&&tipo == 0){
        angle+=5;
    }
    else{
        angle-=5;
        tipo=1;
    }
    if(angle < -25){
        tipo=0;
    }
    double angulo = angle/2;
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    for(int n = 0; n <figuras.size();n++){
    glPushMatrix();
    if(n<6){
    glRotatef(angle,0,0,1);
    }
    else glRotatef(angulo,0,0,1);
    figuras[n].drawModel(i);
    glPopMatrix();
    }/*
    glPushMatrix();
    glRotatef(angle,0,1,0);
    figuras[5].drawModel(i);
    glPopMatrix();
    figuras[6].drawModel(i);*/
}
void Jerarquia::girar_munieca(int i){
    //cout<<"Entramos"<<endl;
    if(angle < 90&&tipo == 0){
        angle+=5;
    }
    else{
        angle-=5;
        tipo=1;
    }
    if(angle < 0){
        tipo=0;
    }
    //else angle-=5;
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    for(int n = 0; n <5;n++){
    glPushMatrix();
    glRotatef(angle,0,1,0);
    figuras[n].drawModel(i);
    glPopMatrix();
    }
    glPushMatrix();
    glRotatef(angle,0,1,0);
    figuras[5].drawModel(i);
    glPopMatrix();
    figuras[6].drawModel(i);
    //cout<<"No tengo ni puta idea como va"<<endl;
}