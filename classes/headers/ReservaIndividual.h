#ifndef RESERVAINDIVIDUAL_H_
#define RESERVAINDIVIDUAL_H_
#include "Reserva.h"
class ReservaIndividual: public Reserva{    
    private:
        Huesped* ptr_huesped;
        float costo;
    public:
        ReservaIndividual();  
        ReservaIndividual(int codigo,tm *checkin, tm *checkout, Estado estado_reserva, Habitacion* ptr_habitacion, Huesped* ptr_huesped,bool tipo);
        string get_nombre_huesped();
        float get_costo();
};

#endif // RESERVAINDIVIDUAL_H_