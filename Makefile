# fichero Makefile
#
# nombre del fichero ejecutable
#
TARGETS= ./bin/practica

SOURCES= src/practica.cc src/3Dmodel.cc src/dibujos.cc src/modeloPly.cc src/file_ply_stl.cc src/jerarquia.cc
TEMP = src/*~ include/*~
OBJECTS=	$(SOURCES:src/%.cc=obj/%.o)
DAT	=	data
INCLUDE = include
CARPETAS = include obj data bin src
# banderas para el compilador (C y C++). Se indican los directorios donde se puenden
# encontrar ficheros para incluir mediante la opcion -I
# la opcion -g sirve para permitir la depuración
#
CFLAGS=    -c -DXWINDOWS -DSHM -I/usr/include -I$(INCLUDE) -I.
CXXFLAGS=  -c -DXWINDOWS -DSHM -I/usr/include -I$(INCLUDE) -I.
DEPURACION=	-g -DXWINDOWS -DSHM -I/usr/include -I$(INCLUDE) -I.
# banderas pra el enlazador
# Se indica directorios donde encontrar las funciontecas con -L. Usando -l seguido del
# nombre se indica la funcionteca que se desea enlazar.
#
LDFLAGS=  -lGLU -lGL -lglut

# definicion del compilador
#
CC = g++ -Wno-write-strings

# orden que sera ejecutada por defecto
#
default :	$(CARPETAS) $(SOURCES) $(TARGETS)

# regla de ejecucion
#
$(CARPETAS):
	mkdir -p $(CARPETAS)
$(TARGETS) : $(OBJECTS)	
	$(CC) -o $@ $^ $(LDFLAGS)
$(OBJECTS) :
	$(CC) $(CXXFLAGS) src/$(@F:.o=.cc) -o $@

.PHONY: depuracion
depuracion :
	$(CC) $(DEPURACION) $(SOURCES) -o $(TARGETS) $(LDFLAGS)
#
clean:
	rm -f $(OBJECTS)
	rm -f $(TARGETS)

#
#
programa:
	$(TARGETS)
redo:
	rm -f $(TARGETS)
	rm -f $(OBJECTS)
	make

#
#
superclean:
	rm -f $(OBJECTS)
	rm -f $(TEMP)
	rm -f $(TARGETS)

#
#
tgz:
	rm -f $(OBJECTS)
	rm -f $(TEMP)
	tar -zcf practica.tgz -C ./src/ . -C ../bin/ . -C ../include/ .

