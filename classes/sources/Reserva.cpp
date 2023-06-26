#ifndef RESERVA_CPP_
#define RESERVA_CPP_
#include "../headers/Reserva.h"

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

tm* Reserva::get_checkin(){
    time_t checkin = chrono::system_clock::to_time_t(this->checkin);
    tm* checkin_tm = localtime(&checkin);
    return checkin_tm;
}

tm* Reserva::get_checkout(){
    time_t checkout = chrono::system_clock::to_time_t(this->checkout);
    tm* checkout_tm = localtime(&checkout);
    return checkout_tm;
}

Estado Reserva::get_estado(){
    return this -> estado_reserva;
}

#endif // RESERVA_CPP_