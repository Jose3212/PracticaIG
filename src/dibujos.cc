#include "dibujos.h"
Dedo::Dedo(){

	vertices.push_back(_vertex3f(0.65,3,0));
	vertices.push_back(_vertex3f(0.65,3.5,0));
	vertices.push_back(_vertex3f(0.65,4,0));
	vertices.push_back(_vertex3f(0.55,4.5,0));
	vertices.push_back(_vertex3f(0.55,5,0));
	vertices.push_back(_vertex3f(0.55,5.5,0));
	vertices.push_back(_vertex3f(0.45,6,0));
	vertices.push_back(_vertex3f(0.45,6.5,0));
	vertices.push_back(_vertex3f(0.45,7,0));
	vertices.push_back(_vertex3f(0.45,7.5,0));
	vertices.push_back(_vertex3f(0.40,8,0));

}
Palma::Palma(){
	
	vertices.push_back(_vertex3f(2,-1,0.45));
	vertices.push_back(_vertex3f(2,2,0.45));
	vertices.push_back(_vertex3f(-2,2,0.45));
	vertices.push_back(_vertex3f(-2,1,0.45));
	vertices.push_back(_vertex3f(-2.5,0,0.45));
	vertices.push_back(_vertex3f(-2,-1,0.45));
	//vertices.push_back(_vertex3f(-2,-1,1));
	vertices.push_back(_vertex3f(2,-1,-0.45));
	vertices.push_back(_vertex3f(2,2,-0.45));
	vertices.push_back(_vertex3f(-2,2,-0.45));
	vertices.push_back(_vertex3f(-2,1,-0.45));
	vertices.push_back(_vertex3f(-2.5,0,-0.45));
	vertices.push_back(_vertex3f(-2,-1,-0.45));
	vertices.push_back(_vertex3f(2,-1,0.45));
	//vertices.push_back(_vertex3f(-2,-1,-1));
	
	triangulos.push_back(_vertex3i(0,1,2));
	triangulos.push_back(_vertex3i(2,0,5));
	triangulos.push_back(_vertex3i(5,3,4));
	triangulos.push_back(_vertex3i(2,8,3));
	triangulos.push_back(_vertex3i(3,9,8));
	triangulos.push_back(_vertex3i(4,9,3));
	triangulos.push_back(_vertex3i(4,9,10));
	triangulos.push_back(_vertex3i(5,10,4));
	triangulos.push_back(_vertex3i(10,11,5));
	triangulos.push_back(_vertex3i(7,8,11));
	triangulos.push_back(_vertex3i(11,7,6));
	triangulos.push_back(_vertex3i(11,9,10));
	triangulos.push_back(_vertex3i(7,1,0));
	triangulos.push_back(_vertex3i(6,0,7));
	
}
Brazo::Brazo(){
	vertices.push_back(_vertex3f(2,-2,0));
	vertices.push_back(_vertex3f(2,-2.5,0));
	vertices.push_back(_vertex3f(2,-3,0));
	vertices.push_back(_vertex3f(2.25,-3.5,0));
	vertices.push_back(_vertex3f(2.5,-4,0));
	vertices.push_back(_vertex3f(2.75,-4.5,0));
	vertices.push_back(_vertex3f(3,-5,0));
	vertices.push_back(_vertex3f(3.25,-5.5,0));
	vertices.push_back(_vertex3f(3.5,-6,0));
	vertices.push_back(_vertex3f(3.75,-6.5,0));
	vertices.push_back(_vertex3f(4,-7,0));
}
Tetraedro::Tetraedro(double tamano){
	vertices.push_back(_vertex3f(-tamano,-tamano,tamano));	//Así lo haremos del tamaño que deseemos
	vertices.push_back(_vertex3f(tamano,-tamano,tamano));
	vertices.push_back(_vertex3f(0,-tamano,-tamano));
	vertices.push_back(_vertex3f(0,tamano,0));	//punta superior del tetraedro
	vertices.push_back(_vertex3f(-tamano,-tamano,tamano));
	//Ahora montamos los triangulos
	triangulos.push_back(_vertex3i(0,1,3));
	triangulos.push_back(_vertex3i(3,2,1));
	triangulos.push_back(_vertex3i(1,2,0));
	triangulos.push_back(_vertex3i(0,2,3));
	triangulos.push_back(_vertex3i(0,1,3));
}
Cubo::Cubo(double tamano){
	//Parte Delantera
	vertices.push_back(_vertex3f(tamano,-tamano,tamano));
	vertices.push_back(_vertex3f(tamano,tamano,tamano));
	vertices.push_back(_vertex3f(-tamano,tamano,tamano));
	vertices.push_back(_vertex3f(-tamano,-tamano,tamano));
	//Parte trasera, igual pero con -z
	vertices.push_back(_vertex3f(tamano,-tamano,-tamano));
	vertices.push_back(_vertex3f(tamano,tamano,-tamano));
	vertices.push_back(_vertex3f(-tamano,tamano,-tamano));
	vertices.push_back(_vertex3f(-tamano,-tamano,-tamano));
	vertices.push_back(_vertex3f(tamano,-tamano,tamano));
	//Montar triangulos
	triangulos.push_back(_vertex3i(0,1,2));
	triangulos.push_back(_vertex3i(2,3,0));
	triangulos.push_back(_vertex3i(3,7,6));
	triangulos.push_back(_vertex3i(6,2,3));
	triangulos.push_back(_vertex3i(7,4,5));
	triangulos.push_back(_vertex3i(5,6,7));
	triangulos.push_back(_vertex3i(5,4,0));
	triangulos.push_back(_vertex3i(0,1,5));
	triangulos.push_back(_vertex3i(1,5,6));
	triangulos.push_back(_vertex3i(6,2,1));
	triangulos.push_back(_vertex3i(0,4,7));
	triangulos.push_back(_vertex3i(7,3,0));
	triangulos.push_back(_vertex3i(0,1,2));
}
/*
test1::test1(){
	vertices.push_back(_vertex3f(1.0,2.0,0.0));
	vertices.push_back(_vertex3f(1.0,-2.0,0.0));
	vertices.push_back(_vertex3f(0,0,0));
	triangulos.push_back(_vertex3i(0,1,2));
}
test2::test2(){
	vertices.push_back(_vertex3f(0,-2,0));
	vertices.push_back(_vertex3f(1,-2,0));
	vertices.push_back(_vertex3f(2,1,0));
	triangulos.push_back(_vertex3i(0,1,2));
}
test3::test3(){
	vertices.push_back(_vertex3f(0,2,0));
	vertices.push_back(_vertex3f(1,2,0));
	vertices.push_back(_vertex3f(2,1,0));
}
test4::test4(){
	vertices.push_back(_vertex3f(0,2,0));
	vertices.push_back(_vertex3f(1,2,0));
	vertices.push_back(_vertex3f(1,-2,0));
	vertices.push_back(_vertex3f(0,-2,0));
}
test5::test5(){
	vertices.push_back(_vertex3f(0,1,0));
	vertices.push_back(_vertex3f(1,-1,0));
	vertices.push_back(_vertex3f(0,-1,0));
}
*/
