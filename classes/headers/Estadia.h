#ifndef ESTADIA_H_
#define ESTADIA_H_
#include "../../ICollection/interfaces/ICollectible.h"
#include "../../enums/EnumEstado.h"
#include "Habitacion.h"
#include "Huesped.h"
#include <chrono>
#include <iostream>
using namespace std;

class Estadia: public ICollectible{
    private:
        int codigo;
        chrono::system_clock::time_point checkin;
        chrono::system_clock::time_point checkout;
        Habitacion* ptr_habitacion;
        Huesped* ptr_huesped;
        string promo;
        //FALTA REVIEW
    public:
        Estadia();
        Estadia(int codigo, tm* checkin, Habitacion* habitacion, Huesped* huesped);
        void set_checkin(tm* checkin);
        void set_checkout(tm* checkout);
        int get_codigo();
        tm* get_checkin();
        tm* get_checkout();

};

#endif // ESTADIA_H_