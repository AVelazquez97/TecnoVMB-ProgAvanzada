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
    std::chrono::duration<float, std::ratio<86400>> diff = Reserva::get_checkout_chrono() - Reserva::get_checkin_chrono();
    this -> costo = (ptr_habitacion ->get_precio() * diff.count());

    /*le asigno al huesped responsable esta nueva reserva creada*/
    ptr_huesped -> asignar_reserva(this);
}

 string ReservaIndividual::get_nombre_huesped(){
    return this -> ptr_huesped -> get_nombre();
 }
 float ReservaIndividual::get_costo(){
    return this -> costo;
 }

#endif // RESERVAINDIVIDUAL_CPP_