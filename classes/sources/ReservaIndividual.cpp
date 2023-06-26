#ifndef RESERVAINDIVIDUAL_CPP_
#define RESERVAINDIVIDUAL_CPP_
#include "../headers/ReservaIndividual.h"

ReservaIndividual::ReservaIndividual(){

}

ReservaIndividual::ReservaIndividual(
    int codigo,
    tm* checkin,
    tm* checkout, 
    Estado estado_reserva, 
    Habitacion* ptr_habitacion, 
    Huesped* ptr_huesped
):Reserva(codigo,checkin, checkout, estado_reserva, ptr_habitacion){
    this -> ptr_huesped = ptr_huesped;
}

#endif // RESERVAINDIVIDUAL_CPP_