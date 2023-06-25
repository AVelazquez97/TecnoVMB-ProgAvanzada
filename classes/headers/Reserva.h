#ifndef RESERVA_H_
#define RESERVA_H_
#include "../../ICollection/interfaces/ICollectible.h"
#include "../../enums/EnumEstado.h"
#include <chrono>
#include <iostream>
using namespace std;
class Habitacion;

class Reserva: public ICollectible{
    private:
        int codigo;
        chrono::system_clock::time_point checkin;
        chrono::system_clock::time_point checkout;
        Habitacion* ptr_habitacion;
        Estado estado_reserva;
    public:
        Reserva();
        Reserva(int codigo, tm *checkin, tm *checkout, Estado estado_reserva);
        void set_checkin(tm* checkin);
        void set_checkout(tm* checkout);
        int get_codigo();
        tm* get_checkin();
        tm* get_checkout();
        Estado get_estado();
};


#endif // RESERVA_H_