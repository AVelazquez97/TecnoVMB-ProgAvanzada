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

Empleado::Empleado(string nombre, string email, string contrasena, Cargo cargo):Usuario(nombre, email, contrasena){
    this -> cargo = cargo;
    this -> puntero_hostal = nullptr;
}

Empleado::Empleado(string nombre, string email, string contrasena, Cargo cargo, Hostal* puntero_hostal):Usuario(nombre, email, contrasena){
    this -> cargo = cargo;
    this -> puntero_hostal = puntero_hostal;
}

Empleado::Empleado(const Empleado& original){
    this -> nombre = original.nombre;
    this -> email = original.email;
    this -> contrasena = original.contrasena;
    this -> cargo = original.cargo;
    this -> puntero_hostal = original.puntero_hostal;
}

Empleado::~Empleado(){

}

Hostal* Empleado::get_puntero_hostal(){
    if(this -> puntero_hostal != nullptr){

        return this -> puntero_hostal;
    }else{
        return nullptr;
    }
}

Cargo Empleado::get_cargo(){
    return this -> cargo;
}

DTEmpleado Empleado::get_DT(){
    return DTEmpleado(this->get_nombre(), this -> get_email(),"",this -> puntero_hostal->get_nombre(), this -> get_cargo());
}

void Empleado::asignar_cargo(Cargo cargo ,Hostal* puntero_hostal){
    this -> cargo = cargo;
    this -> puntero_hostal = puntero_hostal;
}

#endif // EMPLEADO_CPP_