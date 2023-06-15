#ifndef EMPLEADO_CPP_
#define EMPLEADO_CPP_
#include "../headers/Empleado.h"
#include "../../datatypes/headers/DTEmpleado.h"

Empleado::Empleado(){

}

Empleado::Empleado(string nombre, string email, string password, Cargo cargo, Hostal* puntero_hostal){
    this -> nombre = nombre;
    this -> email = email;
    this -> password = password;
    this -> cargo = cargo;
    this -> puntero_hostal = puntero_hostal;
}

Empleado::Empleado(const Empleado& original){
    nombre = original.nombre;
    email = original.email;
    password = original.email;
    cargo = original.cargo;
    puntero_hostal = original.puntero_hostal;
}

Empleado::~Empleado(){

}

Hostal* Empleado::get_puntero_hostal(){
    return this -> puntero_hostal;
}

Cargo Empleado::get_cargo(){
    return this -> cargo;
}

DTEmpleado Empleado::get_DT(){
    return DTEmpleado(this->get_nombre(), this -> get_email(), this -> puntero_hostal->get_nombre(), this -> get_cargo());
}

#endif // EMPLEADO_CPP_