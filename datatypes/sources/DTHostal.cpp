#ifndef DTHOSTAL_CPP_
#define DTHOSTAL_CPP_
#include "../headers/DTHostal.h"
#include <iostream>

DTHostal::DTHostal(){

}

DTHostal::DTHostal(string nombre, string direccion, string telefono){
    this -> nombre = nombre;
    this -> direccion = direccion;
    this -> telefono = telefono;
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

#endif // DTHOSTAL_CPP_