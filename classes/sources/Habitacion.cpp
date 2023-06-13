#ifndef HABITACION_CPP_
#define HABITACION_CPP_
#include "../headers/Habitacion.h"

Habitacion::Habitacion(){}

Habitacion::Habitacion(int numero, float precio, int capacidad){
    this -> numero = numero;
    this -> precio = precio;
    this -> capacidad = capacidad;
}

Habitacion::Habitacion(const Habitacion& original){
    numero = original.numero;
    precio = original.precio;
    capacidad = original.capacidad;
}

Habitacion::~Habitacion(){

}

void Habitacion::set_numero(int numero){
    this -> numero = numero;
}

void Habitacion::set_precio(float precio){
    this -> precio = precio;
}

void Habitacion::set_capacidad(int capacidad){
    this -> precio = precio;
}

int Habitacion::get_numero(){
    return this -> numero;
}

float Habitacion::get_precio(){
    return this -> precio;
}

int Habitacion::get_capacidad(){
    return this -> capacidad;
}

DTHabitacion Habitacion::get_DT(){
    return DTHabitacion(this->get_numero(),this -> get_precio(),this -> get_capacidad());
}

#endif // HABITACION_CPP_