#ifndef RESERVAGRUPAL_CPP_
#define RESERVAGRUPAL_CPP_
#include "../headers/ReservaGrupal.h"
#include "../headers/Huesped.h"
#include "string.h"

ReservaGrupal::ReservaGrupal(){

}

ReservaGrupal::ReservaGrupal(
    int codigo,
    tm* checkin,
    tm* checkout, 
    Estado estado_reserva, 
    Habitacion* ptr_habitacion, 
    OrderedDictionary* huespedes_encontrados
):Reserva(codigo, checkin, checkout, estado_reserva, ptr_habitacion){
    this -> huespedes = new OrderedDictionary();
    for(IIterator* it = huespedes_encontrados -> getIterator(); it -> hasCurrent(); it -> next()){
        /*por cada huesped*/
        Huesped* huesped = dynamic_cast<Huesped*>(it -> getCurrent());

        char parce_email_huesped[huesped -> get_email().length()+1];
        strcpy(parce_email_huesped,huesped -> get_email().c_str());
        /*le creo una ikey*/
        IKey* ik_email_huesped = new String(parce_email_huesped);
        /*lo añado a la lista de huespedes que tiene esta reserva*/
        this -> huespedes -> add(ik_email_huesped,huesped);
        
        /*le agrego al huesped esta reserva*/
        huesped -> asignar_reserva(this);
    }
}


#endif // RESERVAGRUPAL_CPP_