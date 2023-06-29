#include "../headers/DTReserva.h"

DTReserva::DTReserva(){

}

DTReserva::DTReserva(int codigo,tm *checkin, tm *checkout,Estado estado){
    this -> codigo = codigo;
    this -> estado_reserva = estado;

    tm checkin_tm = *checkin;
    time_t checkin_time = mktime(&checkin_tm);
    this -> checkin = chrono::system_clock::from_time_t(checkin_time);

    tm checkout_tm = *checkout;
    time_t checkout_time = mktime(&checkout_tm);
    this -> checkout = chrono::system_clock::from_time_t(checkout_time);
}

int DTReserva::get_codigo(){
    return this -> codigo;
}

tm* DTReserva::get_checkin(){
    time_t checkin = chrono::system_clock::to_time_t(this->checkin);
    tm* checkin_tm = localtime(&checkin);
    return checkin_tm;
}
    
tm* DTReserva::get_checkout(){
    time_t checkout = chrono::system_clock::to_time_t(this->checkout);
    tm* checkout_tm = localtime(&checkout);
    return checkout_tm;
}
    
Estado DTReserva::get_estado(){
    return this -> estado_reserva;
}