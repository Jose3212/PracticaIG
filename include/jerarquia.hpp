#ifndef _JERARQUIA
#define _JERARQUIA
#include "3Dmodel.h"
class Jerarquia : public Modelo{
private:
    vector <Modelo> figuras;
    int numero_figuras;
    double angle_munieca = 0;
    double angle_dedos = 0;
    double angle_brazo = 0;
    double angle_dedosb = 0;
    double trans = 0;
    double tipo = 0;
    double control[5];
public:
    Jerarquia();
    Jerarquia(vector <Modelo> figuras);
    void dibujar(int j = 0);
    void aniade_figura(Modelo figura);
    void girar_munieca(int i =4);
    void saludar(int i =4);
    void indice(int i = 4);
    void senialar(int i = 4);
};
#endif