#ifndef _MODELOPLY_H
#define _MODELOPLY_H
#include "3Dmodel.h"
#include "file_ply_stl.h"
class ModeloPly : public Modelo{
    public:
        ModeloPly();
        ModeloPly(char* archivo);
        vector<_vertex3f> getVert(){return vertices;}
};
#endif