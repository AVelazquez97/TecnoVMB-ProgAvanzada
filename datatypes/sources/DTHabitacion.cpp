#ifndef DTHABITACION_CPP_
#define DTHABITACION_CPP_
#include "../headers/DTHabitacion.h"
//#include "../../classes/headers/Hostal.h"
#include <iostream>
using namespace std;

DTHabitacion::DTHabitacion(){

}

DTHabitacion::DTHabitacion(int numero, float precio, int capacidad){
    this -> numero = numero;
    this -> precio = precio;
    this -> capacidad = capacidad;
    //this -> nombre_hostal = puntero_hostal -> get_nombre();
}

int DTHabitacion::get_numero(){
    return this -> numero;
}

float DTHabitacion::get_precio(){
    return this -> precio;
}

int DTHabitacion::get_capacidad(){
    return this -> capacidad;
}

string DTHabitacion::get_nombre_hostal(){
    return this -> nombre_hostal;
}

ostream& operator << (ostream& salida, DTHabitacion habitacion){
    salida << "| Número: " << habitacion.get_numero() << " |" << endl <<
	"| Precio: " << habitacion.get_precio() << " |" << endl <<
	"| Capacidad: " << habitacion.get_capacidad() << " |" << endl;

    return salida;
}

#endif // DTHABITACION_CPP_