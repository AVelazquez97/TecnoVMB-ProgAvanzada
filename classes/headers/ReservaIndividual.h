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
};

#endif // RESERVAINDIVIDUAL_H_