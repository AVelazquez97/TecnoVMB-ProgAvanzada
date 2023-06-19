#ifndef EMPLEADO_CPP_
#define EMPLEADO_CPP_
#include "../headers/Empleado.h"
#include "../../datatypes/headers/DTEmpleado.h"

Empleado::Empleado():Usuario(){

}

Empleado::Empleado(DTEmpleado nuevo_empleado):Usuario(nuevo_empleado.get_nombre(), nuevo_empleado.get_email(),nuevo_empleado.get_contrasena()){
    this -> cargo = nuevo_empleado.get_cargo();
    this -> puntero_hostal = nullptr;
}

Empleado::Empleado(string nombre, string email, string contrasena, Cargo cargo, Hostal* puntero_hostal):Usuario(nombre, email, contrasena){
    this -> cargo = cargo;
    this -> puntero_hostal = nullptr;
}

Empleado::Empleado(const Empleado& original){
    nombre = original.nombre;
    email = original.email;
    contrasena = original.contrasena;
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