#DATAS = poner los datatypes acá con extensión .o
FABYCONT = IControlador.o Fabrica.o
FUNCIONES = functions.o


#Programa principal:
program: main.o $(FUNCIONES) Fabrica.o IControlador.o Controlador.o # + todos los.o 
	g++ -o $@ $^

#Main:
main.o: main/main.cpp $(FUNCIONES)
	g++ -c $^

functions.o: main/functions.cpp $(FABYCONT)
	g++ -c $^

#Clases:
Fabrica.o: fabrica/Fabrica.cpp IControlador.o Controlador.o 
	g++ -c $^

IControlador.o: iControlador/IControlador.cpp $(DATAS) 
	g++ -c $^

Controlador.o: controlador/Controlador.cpp  #+ objetos.o 
	g++ -c $^

#Datatypes:

#Colecciones:

#Interfaces de collecciones:


clean:
	rm -f programa *.o *.out main