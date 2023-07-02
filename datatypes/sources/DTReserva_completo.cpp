#ifndef DTRESERVA_COMPLETO_CPP_
#define DTRESERVA_COMPLETO_CPP_
#include "../headers/DTReserva_completo.h"
#include "../../classes/headers/ReservaIndividual.h"
#include "../../classes/headers/ReservaGrupal.h"
#include "../../classes/headers/Habitacion.h"
#include "../../classes/headers/Huesped.h"
#include <string.h>

DTReserva_completo::DTReserva_completo(){}

DTReserva_completo::DTReserva_completo(int codigo_reserva, int numero_habitacion,tm* checkin,tm* checkout,Estado estado,OrderedDictionary* huespedes,float costo){
    
}

DTReserva_completo::DTReserva_completo(ReservaGrupal* rg){
    this -> huespedes = new OrderedDictionary();

    this -> codigo_reserva = rg -> get_codigo();
    this -> numero_habitacion = rg -> get_puntero_habitacion() -> get_numero();
    this -> checkin = rg -> get_checkin_chrono();
    this -> checkout = rg -> get_checkout_chrono();
    this -> estado = rg -> get_estado();

    for(IIterator* it = rg -> get_huespedes() -> getIterator(); it -> hasCurrent(); it -> next()){
        Huesped* huesped = dynamic_cast<Huesped*>(it -> getCurrent());

        string cadena = huesped -> get_nombre();
        char parce_char[cadena.length()+1];
        strcpy(parce_char,cadena.c_str());

        IKey* ik = new String(parce_char);
        String* huesped_email = new String(parce_char);

        this -> huespedes -> add(ik, huesped_email); 
    }

    this -> costo = 0;
}

DTReserva_completo::DTReserva_completo(ReservaIndividual* ri){
    this -> huespedes = new OrderedDictionary();

    this -> codigo_reserva = ri -> get_codigo();
    this -> numero_habitacion = ri -> get_puntero_habitacion() -> get_numero();
    this -> checkin = ri -> get_checkin_chrono();
    this -> checkout = ri -> get_checkout_chrono();
    this -> estado = ri -> get_estado();

    string cadena = ri -> get_nombre_huesped();
    char parce_char[cadena.length()+1];
    strcpy(parce_char,cadena.c_str());

    IKey* ik = new String(parce_char);
    String* huesped_email = new String(parce_char);

    this -> huespedes -> add(ik, huesped_email);

    this -> costo = 0;
}

int DTReserva_completo::get_codigo(){
    return this -> codigo_reserva;
}

int DTReserva_completo::get_numero_habitacion(){
    return this -> numero_habitacion;
}

tm* DTReserva_completo::get_checkin(){
    time_t checkin = chrono::system_clock::to_time_t(this->checkin);
    tm* checkin_tm = localtime(&checkin);
    return checkin_tm;
}
    
tm* DTReserva_completo::get_checkout(){
    time_t checkout = chrono::system_clock::to_time_t(this->checkout);
    tm* checkout_tm = localtime(&checkout);
    return checkout_tm;
}
    
Estado DTReserva_completo::get_estado(){
    return this -> estado;
}

chrono::system_clock::time_point DTReserva_completo::get_checkin_chrono(){
    return this -> checkin;
}
chrono::system_clock::time_point DTReserva_completo::get_checkout_chrono(){
    return this -> checkout;
}

OrderedDictionary* DTReserva_completo::get_huespedes(){
    return dynamic_cast<OrderedDictionary*>(huespedes);
}

ostream& operator << (ostream& salida, DTReserva_completo r_c){

}

#endif // DTRESERVA_COMPLETO_CPP_