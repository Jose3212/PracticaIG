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

    glMatrixMode(GL_MODELVIEW);
    glTranslatef(trans,trans,0);
    for(int n = 0; n < figuras.size()-1; n++){
        glPushMatrix();
        if(n==0){
            glRotatef(angle_dedos,0,0,1);
            glRotatef(angle_dedosb,0,1,0);
        }
        if(n>0 && n!=1 && n<5) {
             glRotatef(angle_dedos,0,0,1);
             glRotatef(angle_dedosb,1,0,0);
//        glTranslatef(0,0,trans);
        }
        else if(n==1){
            glRotatef(angle_munieca,0,0,1);
        }
        else if(n==5)glRotatef(angle_munieca,0,0,1);
        else if(n==6)glRotatef(angle_brazo,0,0,1);
//        glTranslatef(trans,trans,0);
        figuras[n].drawModel(i);
        glPopMatrix();
    }
    glPushMatrix();
    //glTranslatef(trans,trans,0);
    glRotatef(angle_dedos,0,0,1);
    glRotatef(angle_dedosb,1,0,0);
    figuras[7].drawModel(i);
    glPopMatrix();

}
void Jerarquia::indice(int i){
//    if(trans < 1){
//        trans+=-0.1;
//    }
    if(angle_dedosb > -90&&tipo == 0){
        angle_dedosb-=5;
    }
    else{
        angle_dedosb+=5;
        tipo=1;
    }
    if(angle_dedosb > 0){
        tipo=0;
    }
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(trans,trans,0);
    //glLoadIdentity();
    for(int n = 0; n <5;n++){
    glPushMatrix();
    if(n==0){
        glRotatef(angle_dedos,0,0,1);
        glRotatef(angle_dedosb,0,1,0);
//        glTranslatef(0,0,trans);
    }
    if(n>0 && n!=1) {
        glRotatef(angle_dedos,0,0,1);
        glRotatef(angle_dedosb,1,0,0);
//        glTranslatef(0,0,trans);
    }
    else if(n==1){
        glRotatef(angle_munieca,0,0,1);
    }
    figuras[n].drawModel(i);
    glPopMatrix();
    }
    glPushMatrix();
    glRotatef(angle_munieca,0,0,1);
    figuras[5].drawModel(i);
    glPopMatrix();
    glPushMatrix();
    glRotatef(angle_brazo,0,0,1);
    figuras[6].drawModel(i);
    glPopMatrix();
    glPushMatrix();
    //glTranslatef(trans,trans,0);
    glRotatef(angle_dedos,0,0,1);
    glRotatef(angle_dedosb,1,0,0);
    figuras[7].drawModel(i);
    glPopMatrix();
}
void Jerarquia::saludar(int i){
    if(angle_brazo < 25&&tipo == 0){
        angle_brazo+=5;
        angle_munieca+=5;
        angle_dedos+=5;
    }
    else{
        angle_brazo-=5;
        angle_munieca-=5;
        angle_dedos-=5;
        tipo=1;
    }
    if(angle_brazo < -25){
        tipo=0;
    }
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(trans,trans,0);
    //glLoadIdentity();
    for(int n = 0; n <figuras.size()-1;n++){
    glPushMatrix();
    if(n<5){
    if(n==0){
        glRotatef(angle_dedos,0,0,1);
        glRotatef(angle_dedosb,0,1,0);
//        glTranslatef(0,0,trans);
    }
    if(n>0 && n!=1) {
        glRotatef(angle_dedos,0,0,1);
        glRotatef(angle_dedosb,1,0,0);
//        glTranslatef(0,0,trans);
    }
    else if(n==1){
        glRotatef(angle_munieca,0,0,1);
    }
    }
    else if(n<6) glRotatef(angle_munieca,0,0,1);
    else glRotatef(angle_brazo,0,0,1);
    figuras[n].drawModel(i);
    glPopMatrix();
    }
    glPushMatrix();
    //glTranslatef(trans,trans,0);
    glRotatef(angle_dedos,0,0,1);
    glRotatef(angle_dedosb,1,0,0);
    figuras[7].drawModel(i);
    glPopMatrix();
    /*
    glPushMatrix();
    glRotatef(angle,0,1,0);
    figuras[5].drawModel(i);
    glPopMatrix();
    figuras[6].drawModel(i);*/
}
void Jerarquia::girar_munieca(int i){
    //cout<<"Entramos"<<endl;
    //angle_munieca = angle_brazo;
    if(angle_munieca < angle_brazo+25&&tipo == 0){
        angle_munieca+=5;
        angle_dedos+=5;
    }
    else{
        angle_munieca-=5;
        angle_dedos-=5;
        tipo=1;
    }
    if(angle_munieca < angle_brazo-25){
        tipo=0;
    }
    //else angle-=5;
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(trans,trans,0);
    //glLoadIdentity();
    for(int n = 0; n <5;n++){
    glPushMatrix();
    if(n==0){
        glRotatef(angle_dedos,0,0,1);
        glRotatef(angle_dedosb,0,1,0);
//        glTranslatef(0,0,trans);
    }
    if(n>0 && n!=1) {
        glRotatef(angle_dedos,0,0,1);
        glRotatef(angle_dedosb,1,0,0);
//        glTranslatef(0,0,trans);
    }
    else if(n==1){
        glRotatef(angle_munieca,0,0,1);
    }
    figuras[n].drawModel(i);
    glPopMatrix();
    }
    glPushMatrix();
    glRotatef(angle_munieca,0,0,1);
    figuras[5].drawModel(i);
    glPopMatrix();
    glPushMatrix();
    glRotatef(angle_brazo,0,0,1);
    figuras[6].drawModel(i);
    glPopMatrix();
    glPushMatrix();
    //glTranslatef(trans,trans,0);
    glRotatef(angle_dedos,0,0,1);
    glRotatef(angle_dedosb,1,0,0);
    figuras[7].drawModel(i);
    glPopMatrix();
    //cout<<"No tengo ni puta idea como va"<<endl;
}