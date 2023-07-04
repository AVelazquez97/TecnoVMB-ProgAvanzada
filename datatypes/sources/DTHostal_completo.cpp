#ifndef DTHOSTAL_COMPLETO_CPP_
#define DTHOSTAL_COMPLETO_CPP_

#include "../headers/DTHostal_completo.h"
#include <iostream>

DTHostal_completo::DTHostal_completo(){
    this -> promedio = 0;
}

DTHostal_completo::DTHostal_completo(string nombre, string direccion, string telefono,float promedio){
    this -> nombre = nombre;
    this -> direccion = direccion;
    this -> telefono = telefono;
    this -> promedio = promedio;
}

string DTHostal_completo::get_nombre(){
    return this -> nombre;
}

string DTHostal_completo::get_direccion(){
    return this -> direccion;
}

string DTHostal_completo::get_telefono(){
    return this -> telefono;
}

float DTHostal_completo::get_promedio(){
    return this -> promedio;
}

OrderedDictionary* DTHostal_completo::get_reviews(){
    return dynamic_cast<OrderedDictionary*>(reviews);
}

OrderedDictionary* DTHostal_completo::get_habitaciones(){
    return dynamic_cast<OrderedDictionary*>(habitaciones);
}

ostream& operator << (ostream& salida, DTHostal_completo hostal) {
    salida << "| Nombre: " << hostal.get_nombre() << " |" << endl <<
		"| Direccion: " << hostal.get_direccion() << " |" << endl <<
		"| Telefono: " << hostal.get_telefono() << " |" << endl <<
		"| Calificación Promedio: " << hostal.get_promedio() << " |" << endl << endl;
    return salida;
} 


#endif // DTHOSTAL_COMPLETO_CPP_