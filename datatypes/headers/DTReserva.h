#ifndef DTRESERVA_H_
#define DTRESERVA_H_
#include "../../ICollection/interfaces/ICollectible.h"
#include "../../enums/EnumEstado.h"
#include <iostream>
#include <chrono>
using namespace std;

class DTReserva: public ICollectible{
    private:
        int codigo;
        chrono::system_clock::time_point checkin;
        chrono::system_clock::time_point checkout;
        Estado estado_reserva;
    public:
        DTReserva();
        DTReserva(int codigo,tm* checkin, tm* checkout,Estado estado);
        //DTEmpleado(string nombre, string email, string nombre_hostal, Cargo cargo);
        int get_codigo();
        tm* get_checkin();
        tm* get_checkout();
        Estado get_estado();
        chrono::system_clock::time_point get_checkin_chrono();
        chrono::system_clock::time_point get_checkout_chrono();
        };

#endif // DTRESERVA_H_