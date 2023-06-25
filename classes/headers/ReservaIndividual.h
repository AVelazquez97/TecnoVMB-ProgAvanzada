#ifndef RESERVAINDIVIDUAL_H_
#define RESERVAINDIVIDUAL_H_
#include "Reserva.h"
class Huesped;

class ReservaIndividual: public Reserva{    
    private:
        Huesped* ptr_huesped;
        float costo;
    public:
        ReservaIndividual();
        ReservaIndividual(tm *checkin, tm *checkout, Estado estado_reserva, Habitacion* ptr_habitacion, Huesped* ptr_huesped);
};

#endif // RESERVAINDIVIDUAL_H_