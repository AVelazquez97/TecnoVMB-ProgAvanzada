#ifndef DTHABITACION_CPP_
#define DTHABITACION_CPP_
#include "../headers/DTHabitacion.h"

DTHabitacion::DTHabitacion(){

}

DTHabitacion::DTHabitacion(int numero, float precio, int capacidad){
    this -> numero = numero;
    this -> precio = precio;
    this -> capacidad = capacidad;
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

#endif // DTHABITACION_CPP_