#ifndef _DIBUJOS_H
#define _DIBUJOS_H
#include "3Dmodel.h"
class Cubo : public Modelo{
public:
	Cubo(double tamano);
};
class Tetraedro : public Modelo{
public:
	Tetraedro(double tamano);
};
class Dedo : public Modelo{
public:
    Dedo();
};
class Palma : public Modelo{
public:
    Palma();
};
class Brazo : public Modelo{
public:
    Brazo();
};
/*
class test1 : public Modelo{
public:
	test1();
};
class test2 : public Modelo{
public:
	test2();
};
class test3 : public Modelo{
public:
	test3();
};
class test4 : public Modelo{
public:
	test4();
};
class test5 : public Modelo{
public:
	test5();
};
*/
#endif
