#ifndef DTHABITACION_CPP_
#define DTHABITACION_CPP_
#include "../headers/DTHabitacion.h"
#include "../../classes/headers/Hostal.h"
#include <iostream>
using namespace std;

DTHabitacion::DTHabitacion(){

}

DTHabitacion::DTHabitacion(int numero, float precio, int capacidad,Hostal pertenece){
    this -> numero = numero;
    this -> precio = precio;
    this -> capacidad = capacidad;
    this -> pertenece = pertenece.get_nombre();
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

string DTHabitacion::get_pertenece(){
    return this -> pertenece;
}

#endif // DTHABITACION_CPP_