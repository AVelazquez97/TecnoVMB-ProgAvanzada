#ifndef RESERVAGRUPAL_H_
#define RESERVAGRUPAL_H_
#include "../../ICollection/interfaces/IKey.h"
#include "../../ICollection/collections/OrderedDictionary.h"
#include "../../ICollection/String.h"
#include "Reserva.h"
class Huesped;

class ReservaGrupal: public Reserva{
    private:
        IDictionary* huespedes;
    public:
        ReservaGrupal();
        ReservaGrupal(int codigo, tm* checkin,tm* checkout,Estado estado,Habitacion* ptr_habitacion,OrderedDictionary* huespedes_encontrados);
};

#endif // RESERVAGRUPAL_H_