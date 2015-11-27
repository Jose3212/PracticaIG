#include "modeloPly.hpp"
ModeloPly::ModeloPly(){};
ModeloPly::ModeloPly(char* archivo){
    _file_ply f;
    vector<float> verti;
    vector<int> triang;
    f.open(archivo);
    f.read(verti, triang);
    f.close();
    for(int i = 0; i < verti.size();i+=3){
        vertices.push_back(_vertex3f(verti.at(i),verti.at(i+1),verti.at(i+2)));
    }
    for(int j = 0; j < triang.size();j+=3){
        triangulos.push_back(_vertex3i(triang.at(j),triang.at(j+1),triang.at(j+2)));
    }
}