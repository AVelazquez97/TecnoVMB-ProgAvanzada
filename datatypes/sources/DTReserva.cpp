#ifndef DTRESERVA_CPP_
#define DTRESERVA_CPP_

#include "../headers/DTReserva.h"
#include "../../classes/headers/Reserva.h"
#include <iomanip>

DTReserva::DTReserva(){

}

DTReserva::DTReserva(int codigo,tm *checkin, tm *checkout,Estado estado){
    this -> codigo = codigo;

    tm checkin_tm = *checkin;
    time_t checkin_time = mktime(&checkin_tm);
    this -> checkin = chrono::system_clock::from_time_t(checkin_time);

    tm checkout_tm = *checkout;
    time_t checkout_time = mktime(&checkout_tm);
    this -> checkout = chrono::system_clock::from_time_t(checkout_time);
    
    this -> estado_reserva = estado;
}

DTReserva::DTReserva(Reserva* reserva){
    this->codigo = reserva->get_codigo();
    this->checkin = reserva->get_checkin_chrono();
    this->checkout = reserva->get_checkout_chrono();
    this->estado_reserva = reserva->get_estado();
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

chrono::system_clock::time_point DTReserva::get_checkin_chrono(){
    return this -> checkin;
}
chrono::system_clock::time_point DTReserva::get_checkout_chrono(){
    return this -> checkout;
}

Estado DTReserva::get_estado(){
    return this -> estado_reserva;
}

ostream& operator << (ostream& salida, DTReserva reserva){
    string estado;

    switch(reserva.get_estado()){
		case 0:{
			estado = "Abierto";
			break;
		}
		case 1:{
			estado = "Cerrada";
			break;
		}
		case 2:{
			estado = "Cancelada";
			break;
		}
	}

    salida << "| Codigo: " << reserva.get_codigo() << " |" << endl 
        << "| Chekin: " << put_time(reserva.get_checkin(), "%d/%m/%Y - %H") << " hs" << " |" << endl 
        << "| Checkout: " << put_time(reserva.get_checkout(), "%d/%m/%Y - %H") << " hs" << " |" << endl<< "| Estado: " 
        << estado << " |" <<endl << endl;

    return salida;
}

#endif // DTRESERVA_H_