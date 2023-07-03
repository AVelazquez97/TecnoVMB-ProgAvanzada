#ifndef RESERVA_CPP_
#define RESERVA_CPP_

#include "../headers/Reserva.h"
#include "../headers/Estadia.h"
#include "../../iControlador/IControlador.h"
#include "../../fabrica/Fabrica.h"

Fabrica fab_reserva;
IControlador* controlador_reserva = fab_reserva.getInterface();
Reserva::Reserva(){}


Reserva::Reserva(int codigo,tm *checkin, tm *checkout, Estado estado_reserva, Habitacion* ptr_habitacion){
    this -> codigo = codigo;
    this -> estado_reserva = estado_reserva;
    this -> ptr_habitacion = ptr_habitacion;

    tm checkin_tm = *checkin;
    time_t checkin_time = mktime(&checkin_tm);
    this -> checkin = chrono::system_clock::from_time_t(checkin_time);

    tm checkout_tm = *checkout;
    time_t checkout_time = mktime(&checkout_tm);
    this -> checkout = chrono::system_clock::from_time_t(checkout_time);

    this -> estadias = new OrderedDictionary();
}

Reserva::Reserva(int codigo,tm *checkin, tm *checkout, Estado estado_reserva, Habitacion* ptr_habitacion, bool tipo){
    this -> codigo = codigo;
    this -> estado_reserva = estado_reserva;
    this -> ptr_habitacion = ptr_habitacion;
    this -> tipo = tipo;

    tm checkin_tm = *checkin;
    time_t checkin_time = mktime(&checkin_tm);
    this -> checkin = chrono::system_clock::from_time_t(checkin_time);

    tm checkout_tm = *checkout;
    time_t checkout_time = mktime(&checkout_tm);
    this -> checkout = chrono::system_clock::from_time_t(checkout_time);

    this -> estadias = new OrderedDictionary();
}

void Reserva::set_checkin(tm* checkin){
    tm checkin_tm = *checkin;
    time_t checkin_time = mktime(&checkin_tm);
    this -> checkin = chrono::system_clock::from_time_t(checkin_time);
}

void Reserva::set_checkout(tm* checkout){
    tm checkout_tm = *checkout;
    time_t checkout_time = mktime(&checkout_tm);
    this -> checkout = chrono::system_clock::from_time_t(checkout_time);
}

int Reserva::get_codigo(){
    return this -> codigo;
}
Habitacion* Reserva::get_puntero_habitacion(){
    return ptr_habitacion;
}
tm* Reserva::get_checkin(){
    time_t checkin = chrono::system_clock::to_time_t(this->checkin);
    tm* checkin_tm = localtime(&checkin);
    return checkin_tm;
}

bool Reserva::get_tipo(){
    return this -> tipo;
}

tm* Reserva::get_checkout(){
    time_t checkout = chrono::system_clock::to_time_t(this->checkout);
    tm* checkout_tm = localtime(&checkout);
    return checkout_tm;
}
chrono::system_clock::time_point Reserva::get_checkin_chrono(){
    return this -> checkin;
}
chrono::system_clock::time_point Reserva::get_checkout_chrono(){
    return this -> checkout;
}

Estado Reserva::get_estado(){
    return this -> estado_reserva;
}
bool Reserva::pertenece_a_hostal(string nombre_hostal){
    return ptr_habitacion -> pertenece_a_hostal(nombre_hostal);
}
void Reserva::alta_estadia(Huesped* ptr_huesped){
    Estadia* ptr_estadia = new Estadia(controlador_reserva -> get_contador_estadia(),controlador_reserva -> get_fecha_sistema(),ptr_habitacion,ptr_huesped);
    IKey* ik_estadia = new Integer(ptr_estadia -> get_codigo());
    this -> estadias -> add(ik_estadia,ptr_estadia);
    this -> estado_reserva = Cerrada;
}

DTReserva Reserva::getDT(){
    return DTReserva(this -> get_codigo(), this -> get_checkin(),this -> get_checkout(), this -> get_estado());
}

int Reserva::get_cantidad_estadias(){
    int cant = 0;
    cant += this -> estadias -> getSize();
    return cant;
}

void Reserva::set_estado(Estado estado){
    this -> estado_reserva = estado;
}

#endif // RESERVA_CPP_