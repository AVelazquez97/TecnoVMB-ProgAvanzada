#ifndef DTEMPLEADO_CPP_
#define DTEMPLEADO_CPP_
#include "../headers/DTEmpleado.h"

DTEmpleado::DTEmpleado(){

}

DTEmpleado::DTEmpleado(string nombre, string email, string nombre_hostal, Cargo cargo){
    this -> nombre = nombre;
    this -> email = email;
    this -> nombre_hostal = nombre_hostal;
    this -> cargo = cargo;
}

string DTEmpleado::get_nombre(){
    return this -> nombre;
}

string DTEmpleado::get_email(){
    return this -> email;
}

string DTEmpleado::get_nombre_hostal(){
    return this -> nombre_hostal;
}

Cargo DTEmpleado::get_cargo(){
    return this -> cargo;
}


#endif // DTEMPLEADO_CPP_