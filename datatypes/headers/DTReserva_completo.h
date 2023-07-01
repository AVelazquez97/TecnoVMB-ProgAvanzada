#ifndef DTRESERVA_COMPLETO_
#define DTRESERVA_COMPLETO_

#include "../../ICollection/interfaces/IDictionary.h"
#include "../../ICollection/collections/OrderedDictionary.h"
#include "../../ICollection/interfaces/ICollectible.h"
#include "../../enums/EnumEstado.h"
#include <iostream>
#include <chrono>
using namespace std;

class ReservaGrupal;
class ReservaIndividual;

class DTReserva_completo: public ICollectible{
    private:
        int codigo_reserva;
        int numero_habitacion;
        chrono::system_clock::time_point checkin;
        chrono::system_clock::time_point checkout;
        Estado estado;
        IDictionary* huespedes;
        float costo;
    public:
        DTReserva_completo();
        DTReserva_completo(int codigo_reserva, int numero_habitacion,tm* checkin,tm* checkout,Estado estado,OrderedDictionary* huespedes,float costo);
        DTReserva_completo(ReservaGrupal* rg);
        DTReserva_completo(ReservaIndividual* ri);
        int get_codigo();
        int get_numero_habitacion();
        tm* get_checkin();
        tm* get_checkout();
        Estado get_estado();
        chrono::system_clock::time_point get_checkin_chrono();
        chrono::system_clock::time_point get_checkout_chrono();
        OrderedDictionary* get_huespedes();
        

};


#endif // DTRESERVA_COMPLETO_