#include "3Dmodel.h"
void Modelo::trasladar_figurax(float traslacion){
	for (int i = 0; i < vertices.size(); i++){
		vertices[i].x+=traslacion;
	}
}
void Modelo::trasladar_figuray(float traslacion){
	for (int i = 0; i < vertices.size(); i++){
		vertices[i].y+=traslacion;
	}
}
void Modelo::escalar(double escalado){
	_vertex3f punto;
	for (int i = 0; i < vertices.size(); i++){
		punto.x = vertices[i].x*escalado;
		punto.y = vertices[i].y*escalado;
		punto.z = vertices[i].z*escalado;
		vertices[i]=punto;
	}
}
void Modelo::rotar_z(double ang){
	double angulo = grados_radianes(ang);
	_vertex3f punto;
	for (int i = 0; i < vertices.size(); i++){
		punto.x = (vertices[i].x * cos(angulo)) - (vertices[i].y * sin(angulo));
		punto.y = (vertices[i].x * sin(angulo)) + (vertices[i].y * cos(angulo));
		punto.z = vertices[i].z;
		vertices[i]=punto;
	}
}
_vertex3f Modelo::modulizar(_vertex3f normales){
	double modulo = sqrt(normales.x*normales.x+normales.y*normales.y+normales.z*normales.z);
	normales.x=normales.x/modulo;normales.y=normales.y/modulo;normales.z=normales.z/modulo;
	return normales;
}
void Modelo::generarBarrido(){
	/*Esta implementación es muy fácil teniendo una buena base de algebra lineal.
	 *Como ya sabemos, el vector normal a dos vectores se haya como el producto
	 *vectorial de estos dos, así pues ya que con dos vectores podemos montar una cara,
	 *con el producto vectorial de esto obtenemos un vector perpendicular( o normal).
	 *Con un vector normal y una cara podemos montar una figura 3D.
	 */
	vector<_vertex3f> norm_car;
	for (int i = 0; i < triangulos.size();i++){
		_vertex3f a,b,c,ab,bc,normal;
		a=vertices.at(triangulos.at(i).x);
		b=vertices.at(triangulos.at(i).y);
		c=vertices.at(triangulos.at(i).z);
		ab.x=a.x-b.x;ab.y=a.y-b.y;ab.z=a.z-b.z;
		bc.x=b.x-c.x;bc.y=b.y-c.y;bc.z=b.z-c.z;
		normal.x = ab.y * bc.z - ab.z * bc.y;
        normal.y = ab.z * bc.x - ab.x * bc.z;
        normal.z = ab.x * bc.y - ab.y * bc.x;
		normal=modulizar(normal);
		norm_car.push_back(normal);
	}
	setNC(norm_car);
	vector<_vertex3f> norm_vert;
	for(int j = 0; j < vertices.size();j++){
		_vertex3f vert, normal(0,0,0);
		vert = vertices.at(j);
		for(int n = 0; n < triangulos.size();n++){
			if((triangulos[n].x==j)||(triangulos[n].y==j)||(triangulos[n].z==j)){
				normal = _vertex3f(normal.x + norm_car[n].x, normal.y + norm_car[n].y, normal.z + norm_car[n].z);
			}
		}
		normal = modulizar(normal);
		norm_vert.push_back(normal);
	}
	setNV(norm_vert);
}
_vertex3f Modelo::rotar(_vertex3f p, double alpha){
	_vertex3f point;

    point.x = cos(alpha) * p.x + sin(alpha) * p.z;
    point.y = p.y;
    point.z = -sin(alpha) * p.x + cos(alpha) * p.z;

    return point;
}
float Modelo::grados_radianes(float angulo){
	return angulo*M_PI/180;

}
void Modelo::generarRevolucion(float angulo_inicial, float angulo_final){
	float ang_ini, ang_fin;
	ang_ini = grados_radianes(angulo_inicial);
	ang_fin = grados_radianes(angulo_final);
	for(unsigned int m = 0;m < vertices.size(); m++){ 
		vertices[m] = rotar(vertices[m],ang_ini);
	}
	vector<_vertex3f> puntos(vertices);	//Para guardar los nuevos puntos.
	vector<_vertex3f> perfil(vertices);	//Para trabajar con el perfil.
	vector<_vertex3i> triang;	//Para guardar las caras.
	int pasos = 10;	//Numero de perfiles que vamos a generar.
		//2*pi es una vuelta entera, así pues dividimos entre los perfiles que generaremos

	double angulo= (ang_ini-ang_fin) / pasos;
	//perfil[0]=rotar(perfil[0],ang_ini);	
	//puntos[0]=perfil[0];
	for(int i = 0; i < pasos; i++){
		vector<_vertex3f> siguientePerfil(perfil.size());
		for(unsigned int j = 0; j < perfil.size(); j++){
			siguientePerfil[j] = rotar(perfil[j],angulo);	//Obtenemos el perfil rotado
		}
		puntos.insert(puntos.end(),siguientePerfil.begin(),siguientePerfil.end());	//Intrdocimos los nuevos puntos
		unsigned int inicioPerfil, finPerfil;
		inicioPerfil = i * perfil.size();
		finPerfil = inicioPerfil + perfil.size();
		for(unsigned int n = inicioPerfil+1, j = finPerfil+1; n < finPerfil; n++, j++){	//Metemos las caras.
			triang.push_back(_vertex3i(n-1, j-1,j));
			triang.push_back(_vertex3i(n-1,j,n));
		}
		perfil = siguientePerfil;
	}
	/* Ahora viene la parte que considero más complicada, para montar las tapas, debemos obtener
	 * el punto superior central y el punto inferior central. Debería obtener la altura del primer y último punto para localizar
	 * las tapas.
	 * */
	
	if(puntos.front().x){	//Tapa superior
		_vertex3f puntoCentral(0.0, puntos.front().y,0.0);	//Metemos el punto central
		puntos.push_back(puntoCentral);
		for(int paso = 0; paso < pasos; paso++){	//Solo tenemos que controlar las caras.
			int perfilActual = paso * perfil.size();
			int siguientePerfil = perfilActual + perfil.size();
			triang.push_back(_vertex3i(puntos.size()-1,siguientePerfil,perfilActual));
		}
	}
	if(puntos[perfil.size()-1].x){	//Tapa inferior
		_vertex3f puntoCentral(0.0,puntos[perfil.size()-1].y,0.0);
		puntos.push_back(puntoCentral);
		for(int paso = 0; paso < pasos;paso++){
			int perfilActual=(paso+1)*perfil.size()-1;
			int siguientePerfil=perfilActual + perfil.size();
			triang.push_back(_vertex3i(puntos.size()-1,perfilActual,siguientePerfil));
		}
	}
	
	setVert(puntos);
	setTrian(triang);
}
void Modelo::drawModel(int i){
	GLenum dibujo;
	int v1,v2,v3;
	float x=0,y=0,z=0;
	switch(i){
	case 0:
		dibujo = GL_POINTS; //Pintamos Puntos
		x=1;
		break;
	case 1:
		dibujo = GL_LINES; //Pintamos Lineas
		y=1;
		break;
	case 4:
		drawModel(0);
		drawModel(1);
	default:
		dibujo = GL_TRIANGLES; //Dibujamos triangulos para el sólido, o modo ajedrez
		x=0.8;
		y=0.8;
		z=0.8;
		break;
	}
	glPointSize(4);
	glBegin(dibujo);
	for(int j =0; j < triangulos.size();j++){
		glColor3f(x,y,z);
		if(i==2){ //Hacemos el ajedrez
			if((j%2)==0){ //Vamos intercambiando colores
				glColor3f(0, 0, 0);
			}
		}
		v1 = triangulos.at(j)._0;
		v2 = triangulos.at(j)._1;
		v3 = triangulos.at(j)._2;
		glVertex3f(vertices.at(v1).x, vertices.at(v1).y,vertices.at(v1).z);
		glVertex3f(vertices.at(v2).x, vertices.at(v2).y,vertices.at(v2).z);
		glVertex3f(vertices.at(v3).x, vertices.at(v3).y,vertices.at(v3).z);
	}
	glEnd();
}
void Modelo::drawNormales(int i){
	GLenum dibujo;
	float t = 5;
	int v1,v2,v3;
	float x=0,y=0,z=0;
	switch(i){
	case 0:
		dibujo = GL_POINTS; //Pintamos Puntos
		x=1;
		break;
	case 1:
		dibujo = GL_LINES; //Pintamos Lineas
		y=1;
		break;
	case 4:
		drawModel(0);
		drawModel(1);
	default:
		dibujo = GL_TRIANGLES; //Dibujamos triangulos para el sólido, o modo ajedrez
		x=0.8;
		y=0.8;
		z=0.8;
		break;
	}
	glPointSize(4);
	glBegin(dibujo);
	for (int i= 0; i < vertices.size(); i++)
        {
            _vertex3f _1 = vertices.at(i);
            _vertex3f _2;

            _2.x = _1.x + t * normalesVert.at(i).x;
            _2.y = _1.y + t * normalesVert.at(i).y;
            _2.z = _1.z + t * normalesVert.at(i).z;

            glVertex3f(_1.x, _1.y, _1.z);
            glVertex3f(_2.x, _2.y, _2.z);
        }
	glEnd();
}
