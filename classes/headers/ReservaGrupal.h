#ifndef RESERVAGRUPAL_H_
#define RESERVAGRUPAL_H_
#include "../../ICollection/interfaces/IKey.h"
#include "../../ICollection/collections/OrderedDictionary.h"
#include "Reserva.h"

class ReservaGrupal: public Reserva{
    private:
        OrderedDictionary* huespedes;
    public:
        ReservaGrupal();
};

#endif // RESERVAGRUPAL_H_