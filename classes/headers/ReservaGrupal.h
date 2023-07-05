#ifndef RESERVAGRUPAL_H_
#define RESERVAGRUPAL_H_
#include "../../ICollection/interfaces/IKey.h"
#include "../../ICollection/collections/OrderedDictionary.h"
#include "../../ICollection/String.h"
#include "Reserva.h"
class ReservaGrupal: public Reserva{
    private:
        IDictionary* huespedes;
        int cantidad_huespedes;
        float costo;
    public:
        ReservaGrupal();
        ReservaGrupal(int codigo, tm* checkin,tm* checkout,Estado estado,Habitacion* ptr_habitacion,OrderedDictionary* huespedes_encontrados);
        ReservaGrupal(int codigo, tm* checkin,tm* checkout,Estado estado,Habitacion* ptr_habitacion,OrderedDictionary* huespedes_encontrados, bool tipo);
        OrderedDictionary* get_huespedes();
        float get_costo();
};

#endif // RESERVAGRUPAL_H_