#ifndef RESERVA_H_
#define RESERVA_H_
#include "../../ICollection/interfaces/ICollectible.h"
#include "../../enums/EnumEstado.h"
#include <chrono>
#include <iostream>
using namespace std;
class Habitacion;
class Hostal;

class Reserva: public ICollectible{
    private:
        int codigo;
        chrono::system_clock::time_point checkin;
        chrono::system_clock::time_point checkout;
        Habitacion* ptr_habitacion;
        Estado estado_reserva;
    public:
        Reserva();
        Reserva(int codigo,tm *checkin, tm *checkout, Estado estado_reserva, Habitacion* ptr_habitacion);
        void set_checkin(tm* checkin);
        void set_checkout(tm* checkout);
        int get_codigo();
        tm* get_checkin();
        /*devuelve el atributo checkin en otro tipo de dato, como no podia 
        tener el mismo nombre de 'get_checkin' se le agrega chrono ya que el tipo
        de dato que devuelve le pertenece a esa libreria*/
        chrono::system_clock::time_point get_checkin_chrono();
        tm* get_checkout();
        chrono::system_clock::time_point get_checkout_chrono();
        Estado get_estado();
};

#endif // RESERVA_H_