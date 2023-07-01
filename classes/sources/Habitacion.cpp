#ifndef HABITACION_CPP_
#define HABITACION_CPP_

#include "../headers/Habitacion.h"

Habitacion::Habitacion(){}

Habitacion::Habitacion(DTHabitacion nueva_habitacion, Hostal* puntero_hostal){
    this -> numero = nueva_habitacion.get_numero();
    this -> precio = nueva_habitacion.get_precio();
    this -> capacidad = nueva_habitacion.get_capacidad();
    this -> puntero_hostal = puntero_hostal;
    this -> estadias = new OrderedDictionary();
    this -> reservas = new OrderedDictionary();
}

Habitacion::Habitacion(int numero, float precio, int capacidad, Hostal* puntero_hostal){
    this -> numero = numero;
    this -> precio = precio;
    this -> capacidad = capacidad;
    this -> puntero_hostal = puntero_hostal;
    this -> estadias = new OrderedDictionary();
    this -> reservas = new OrderedDictionary();
}
bool Habitacion::pertenece_a_hostal(string nombre_hostal){
    if(puntero_hostal -> get_nombre() == nombre_hostal){
        return true;
    }else{
        return false;
    }
}

Habitacion::Habitacion(const Habitacion& original){
    numero = original.numero;
    precio = original.precio;
    capacidad = original.capacidad;
    puntero_hostal = puntero_hostal;
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

void Habitacion::set_puntero_hostal(Hostal* puntero_hostal){
    this -> puntero_hostal = puntero_hostal;
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

Hostal* Habitacion::get_puntero_hostal(){
    return this -> puntero_hostal;
}
OrderedDictionary* Habitacion::get_reservas(){
    return dynamic_cast<OrderedDictionary*>(reservas);
}
DTHabitacion Habitacion::get_DT(){
    return DTHabitacion(this -> get_numero(),this -> get_precio(),this -> get_capacidad());
}

void Habitacion::crear_reserva(int codigo,Huesped* huesped, tm* checkin, tm* checkout, bool tipo){
    
    ReservaIndividual* ri = new ReservaIndividual(codigo,checkin,checkout,Abierta,this,huesped,tipo); //cambiar el codigo
    IKey* ik_ri = new Integer(ri -> get_codigo());
    this -> reservas -> add(ik_ri,ri);
}

void Habitacion::crear_reserva(int codigo,OrderedDictionary* huespedes_encontrados, tm* checkin, tm* checkout, bool tipo){
    
    ReservaGrupal* rg = new ReservaGrupal(codigo,checkin,checkout,Abierta,this,huespedes_encontrados,tipo); //cambiar el codigo
    IKey* ik_rg = new Integer(rg -> get_codigo());
    this -> reservas -> add(ik_rg,rg);

}

#endif // HABITACION_CPP_