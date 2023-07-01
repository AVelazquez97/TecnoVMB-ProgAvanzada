#ifndef RESERVAINDIVIDUAL_CPP_
#define RESERVAINDIVIDUAL_CPP_
#include "../headers/ReservaIndividual.h"
#include "../headers/Habitacion.h"
#include "../headers/Huesped.h"
ReservaIndividual::ReservaIndividual(){

}

ReservaIndividual::ReservaIndividual(
    int codigo,
    tm* checkin,
    tm* checkout, 
    Estado estado_reserva, 
    Habitacion* ptr_habitacion, 
    Huesped* ptr_huesped,
    bool tipo
):Reserva(codigo,checkin, checkout, estado_reserva, ptr_habitacion,tipo){
    this -> ptr_huesped = ptr_huesped;
    /*le asigno al huesped responsable esta nueva reserva creada*/
    ptr_huesped -> asignar_reserva(this);
}

 string ReservaIndividual::get_nombre_huesped(){
    return this -> ptr_huesped -> get_nombre();
 }

#endif // RESERVAINDIVIDUAL_CPP_