#ifndef _TABLERO
#define _TABLERO
#include "3Dmodel.h"
#include "jpg_imagen.hpp"
#include "jpg_jinclude.h"
#include "jpg_memsrc.hpp"
#include "jpg_readwrite.hpp"

class Tablero{
private:
    Modelo contorno;
    vector <Modelo> cuadros;
    jpg::imagen textura;
public:
    Tablero(){}
    Tablero(int cortes, jpg::imagen tex1, jpg::imagen tex2);
    void pinto();
};

#endif
