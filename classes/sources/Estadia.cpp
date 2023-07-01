#ifndef ESTADIA_CPP_
#define ESTADIA_CPP_
#include "../headers/Estadia.h"
#include "../../iControlador/IControlador.h"
#include "../../fabrica/Fabrica.h"

Fabrica fab_estadia;
IControlador* controlador_estadia = fab_estadia.getInterface();
Estadia::Estadia(){}


Estadia::Estadia(int codigo, tm* checkin, Habitacion* ptr_habitacion, Huesped* ptr_huesped){
    this -> codigo = codigo;
   
    tm checkin_tm = *checkin;
    time_t checkin_time = mktime(&checkin_tm);
    this -> checkin = chrono::system_clock::from_time_t(checkin_time);

    this -> ptr_habitacion = ptr_habitacion;

    this -> ptr_huesped = ptr_huesped;

    ptr_huesped -> asignar_estadia_usuario(this);
}

void Estadia::set_checkin(tm* checkin){
    tm checkin_tm = *checkin;
    time_t checkin_time = mktime(&checkin_tm);
    this -> checkin = chrono::system_clock::from_time_t(checkin_time);
}

void Estadia::set_checkout(tm* checkout){
    tm checkout_tm = *checkout;
    time_t checkout_time = mktime(&checkout_tm);
    this -> checkout = chrono::system_clock::from_time_t(checkout_time);
}

int Estadia::get_codigo(){
    return this -> codigo;
}

tm* Estadia::get_checkin(){
    time_t checkin = chrono::system_clock::to_time_t(this->checkin);
    tm* checkin_tm = localtime(&checkin);
    return checkin_tm;
}

tm* Estadia::get_checkout(){
    time_t checkout = chrono::system_clock::to_time_t(this->checkout);
    tm* checkout_tm = localtime(&checkout);
    return checkout_tm;
}
chrono::system_clock::time_point Estadia::get_checkout_chrono(){
    return this -> checkout;
}
bool Estadia::perteneceA(string nombre_hostal){
    return ptr_habitacion -> pertenece_a_hostal(nombre_hostal);
}
void Estadia::finalizar(){
    tm checkout_tm = *controlador_estadia -> get_fecha_sistema();
    time_t checkout_time = mktime(&checkout_tm);
    this -> checkout = chrono::system_clock::from_time_t(checkout_time);
}
#endif // ESTADIA_CPP_