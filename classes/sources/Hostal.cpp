#ifndef HOSTAL_CPP_
#define HOSTAL_CPP_
#include "../headers/Hostal.h"
//#include "../headers/Empleado.h"
#include "../../classes/headers/Habitacion.h"
#include <iostream>
#include <stdlib.h>
#include "../../ICollection/String.h"
#include "string.h" 
#include "../headers/Empleado.h" 
using namespace std;
Hostal::Hostal(){

}

Hostal::Hostal(DTHostal nuevo_hostal){
    this -> nombre = nuevo_hostal.get_nombre();
    this -> direccion = nuevo_hostal.get_direccion();
    this -> telefono = nuevo_hostal.get_telefono();
    this -> habitaciones = new OrderedDictionary();
    this -> reviews = new OrderedDictionary();
    this -> empleados = new OrderedDictionary();
    this -> promedio = 0;
}

Hostal::Hostal(string nombre, string direccion, string telefono){
    this -> nombre = nombre;
    this -> direccion = direccion;
    this -> telefono = telefono;
    this -> habitaciones = new OrderedDictionary();
    this -> reviews = new OrderedDictionary();
    this -> empleados = new OrderedDictionary();
    this -> promedio = 0;
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

float Hostal::get_promedio(){
    return this -> promedio;
}

DTHostal Hostal::get_DT(){
    return DTHostal(this -> get_nombre(),this -> get_direccion(), this -> get_telefono(), this -> get_promedio());
}

void Hostal::alta_habitacion(DTHabitacion hab, Hostal* ptr_hostal){
    Habitacion* nueva_habitacion = new Habitacion(hab,ptr_hostal);

    IKey* ik = new Integer(nueva_habitacion -> get_numero());

    this -> habitaciones -> add(ik,nueva_habitacion);

}
 bool Hostal::no_es(string email){
    char parce_char[email.length()+1];
    strcpy(parce_char,email.c_str());

    IKey* ik = new String(parce_char);
    return this -> empleados -> member(ik);
 }
void Hostal::asignar_empleado(Empleado* puntero_empleado){
    
    string email = puntero_empleado -> get_email();
    char parce_email[email.length()+1];
    strcpy(parce_email,email.c_str());

    IKey* ik = new String(parce_email);
    this -> empleados -> add(ik,puntero_empleado);
}

#endif // HOSTAL_CPP_