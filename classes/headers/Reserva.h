#ifndef RESERVA_H_
#define RESERVA_H_
#include "../../ICollection/interfaces/ICollectible.h"
#include "../../ICollection/collections/OrderedDictionary.h"
#include "../../datatypes/headers/DTReserva.h"
#include "../../enums/EnumEstado.h"
#include <chrono>
#include <iostream>
using namespace std;
class Habitacion;
class Hostal;
class Huesped;
class Reserva: public ICollectible{
    private:
        int codigo;
        chrono::system_clock::time_point checkin;
        chrono::system_clock::time_point checkout;
        Habitacion* ptr_habitacion;
        Estado estado_reserva;
        IDictionary* estadias;
        //indica si es 0 = individual | 1 = grupal
        bool tipo;
    public:
        Reserva();
        Reserva(int codigo,tm *checkin, tm *checkout, Estado estado_reserva, Habitacion* ptr_habitacion);
        Reserva(int codigo,tm *checkin, tm *checkout, Estado estado_reserva, Habitacion* ptr_habitacion, bool tipo);
        void set_checkin(tm* checkin);
        void set_checkout(tm* checkout);
        int get_codigo();
        tm* get_checkin();
        bool get_tipo();
        DTReserva getDT();
        bool pertenece_a_hostal(string nombre_hostal);
        Habitacion* get_puntero_habitacion();
        /*devuelve el atributo checkin en otro tipo de dato, como no podia 
        tener el mismo nombre de 'get_checkin' se le agrega chrono ya que el tipo
        de dato que devuelve le pertenece a esa libreria*/
        
        tm* get_checkout();
        chrono::system_clock::time_point get_checkin_chrono();
        chrono::system_clock::time_point get_checkout_chrono();
        Estado get_estado();
        void alta_estadia(Huesped* ptr_huesped);
        int get_cantidad_estadias();
        void set_estado(Estado estado);
};

#endif // RESERVA_H_