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
	double module = normales.x*normales.x+normales.y*normales.y+normales.z*normales.z;
	module = sqrt(module);
	module = 1.0/module;
	normales.x*= module;
	normales.y*= module;
	normales.z*= module;
	return normales;
}
void Modelo::generarBarrido(){
	_vertex3f normal,P,Q;
	int v1,v2,v3;
	for( int i = 0; i < triangulos.size(); i++){
		v1=triangulos[i]._0;
		v2=triangulos[i]._1;
		v3=triangulos[i]._2;
		P=vertices[v2]-vertices[v1];
		Q=vertices[v3]-vertices[v1];
		normal.x=P.y*Q.z-P.z*Q.y;
		normal.y=Q.x*P.z-P.x*Q.z;
		normal.z=P.x*Q.y-Q.x*P.y;
		normal = modulizar(normal);
		normalesCara.push_back(normal);
	}
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
void Modelo::dibujar_normales(){
	glPointSize(4);
	glBegin(GL_POINTS);
	for(int i =0; i < normalesCara.size();i++){
		glNormal3f(normalesCara.at(i).x,normalesCara.at(i).y,normalesCara.at(i).z);
		//glVertex3f(normalesVert.at(i).x,normalesVert.at(i).y,normalesVert.at(i).z);
	}
	glEnd();
}
void Modelo::mostrar_normales(){
	for(int i = 0; i< normalesCara.size(); i++)cout<< " " << normalesCara.at(i).x << " - " << normalesCara.at(i).y << " - " << normalesCara.at(i).z << endl;
}
void Modelo::drawNormales(int i){
	GLenum dibujo;
	float t = 5;
	int v1,v2,v3;
	float x=0,y=0,z=0;
	if(i==0){
		glBegin(GL_TRIANGLES);
		for(int j =0; j < triangulos.size();j++){
			glNormal3f(normalesCara.at(j).x,normalesCara.at(j).y,normalesCara.at(j).z);
			v1 = triangulos.at(j)._0;
			v2 = triangulos.at(j)._1;
			v3 = triangulos.at(j)._2;
			glVertex3f(vertices.at(v1).x, vertices.at(v1).y,vertices.at(v1).z);
			glVertex3f(vertices.at(v2).x, vertices.at(v2).y,vertices.at(v2).z);
			glVertex3f(vertices.at(v3).x, vertices.at(v3).y,vertices.at(v3).z);
		}
		glEnd();
	}
	else{
		glBegin(GL_TRIANGLES);
		for(int j =0; j < triangulos.size();j++){
			v1 = triangulos.at(j)._0;
			v2 = triangulos.at(j)._1;
			v3 = triangulos.at(j)._2;
			glNormal3f(normalesCara.at(v1).x,normalesCara.at(v1).y,normalesCara.at(v1).z);
			glVertex3f(vertices.at(v1).x, vertices.at(v1).y,vertices.at(v1).z);
			glNormal3f(normalesCara.at(v2).x,normalesCara.at(v2).y,normalesCara.at(v2).z);
			glVertex3f(vertices.at(v2).x, vertices.at(v2).y,vertices.at(v2).z);
			glNormal3f(normalesCara.at(v3).x,normalesCara.at(v3).y,normalesCara.at(v3).z);
			glVertex3f(vertices.at(v3).x, vertices.at(v3).y,vertices.at(v3).z);
		}
		glEnd();
	}
	/*
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
	*/
}