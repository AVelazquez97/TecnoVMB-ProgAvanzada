#ifndef HOSTAL_CPP_
#define HOSTAL_CPP_
#include "../headers/Hostal.h"

Hostal::Hostal(){

}

Hostal::Hostal(string nombre, string direccion, string telefono){
    this -> nombre = nombre;
    this -> direccion = direccion;
    this -> telefono = telefono;
    this -> habitaciones = new OrderedDictionary();
}

Hostal::Hostal(const Hostal& original){
    nombre = original.nombre;
    direccion = original.direccion;
    telefono = original.telefono;
}

Hostal::~Hostal(){

}

void Hostal::set_nombre(string nombre){
    this -> nombre = nombre;
}

void Hostal::set_direccion(string direccion){
    this -> direccion = direccion;
}

void Hostal::set_telefono(string telefono){
    this -> telefono = telefono;
}

string Hostal::get_nombre(){
    return this -> nombre;
}

string Hostal::get_direccion(){
    return this -> direccion;
}

string Hostal::get_telefono(){
    return this -> telefono;
}

DTHostal Hostal::get_DT(){
    return DTHostal(this -> get_nombre(),this -> get_direccion(), this -> get_telefono());
}


#endif // HOSTAL_CPP_