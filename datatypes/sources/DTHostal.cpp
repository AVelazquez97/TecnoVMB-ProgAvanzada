#ifndef DTHOSTAL_CPP_
#define DTHOSTAL_CPP_
#include "../headers/DTHostal.h"
#include <iostream>

DTHostal::DTHostal(){
    this -> promedio = 0;
}

DTHostal::DTHostal(string nombre, string direccion, string telefono){
    this -> nombre = nombre;
    this -> direccion = direccion;
    this -> telefono = telefono;
    this -> promedio = 0;
}

DTHostal::DTHostal(string nombre, string direccion, string telefono,float promedio){
    this -> nombre = nombre;
    this -> direccion = direccion;
    this -> telefono = telefono;
    this -> promedio = promedio;
}

string DTHostal::get_nombre(){
    return this -> nombre;
}

string DTHostal::get_direccion(){
    return this -> direccion;
}

string DTHostal::get_telefono(){
    return this -> telefono;
}

float DTHostal::get_promedio(){
    return this -> promedio;
}

ostream& operator << (ostream& salida, DTHostal hostal) {
    salida << "| Nombre: " << hostal.get_nombre() << " |" << endl <<
		"| Direccion: " << hostal.get_direccion() << " |" << endl <<
		"| Telefono: " << hostal.get_telefono() << " |" << endl <<
		"| Calificación Promedio: " << hostal.get_promedio() << " |" << endl << endl;
    return salida;
} 

#endif // DTHOSTAL_CPP_