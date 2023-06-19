program: main.o functions.o fabrica.o controlador.o icontrolador.o collections.o interfaces.o string.o integer.o objetos.o datatypes.o
	g++ -o programa *.o
	make clean

main.o: main/main.cpp
	g++ -c main/main.cpp

functions.o: main/functions.h main/functions.cpp
	g++ -c main/functions.cpp

fabrica.o: fabrica/Fabrica.h fabrica/Fabrica.cpp
	g++ -c fabrica/Fabrica.cpp

controlador.o: controlador/Controlador.h controlador/Controlador.cpp
	g++ -c controlador/Controlador.cpp

icontrolador.o: iControlador/IControlador.h iControlador/IControlador.cpp
	g++ -c iControlador/IControlador.cpp

collections.o: ICollection/collections/*.h ICollection/collections/*.cpp 
	g++ -c ICollection/collections/*.cpp

interfaces.o: ICollection/interfaces/*.h  ICollection/interfaces/*.cpp
	g++ -c ICollection/interfaces/*.cpp

string.o: ICollection/String.h ICollection/String.cpp
	g++ -c ICollection/String.cpp

integer.o: ICollection/Integer.h ICollection/Integer.cpp
	g++ -c ICollection/Integer.cpp

objetos.o: classes/headers/*.h classes/sources/*.cpp
	g++ -c classes/sources/*.cpp

datatypes.o: datatypes/headers/*.h datatypes/sources/*.cpp
	g++ -c datatypes/sources/*.cpp

clean:
	rm -f *.o

