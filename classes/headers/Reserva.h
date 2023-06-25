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
        int codigo = 1;
        chrono::system_clock::time_point checkin;
        chrono::system_clock::time_point checkout;
        Habitacion* ptr_habitacion;
        Estado estado_reserva;
    public:
        Reserva();
        Reserva(tm *checkin, tm *checkout, Estado estado_reserva, Habitacion* ptr_habitacion);
        void set_checkin(tm* checkin);
        void set_checkout(tm* checkout);
        int get_codigo();
        tm* get_checkin();
        tm* get_checkout();
        Estado get_estado();
};


#endif // RESERVA_H_