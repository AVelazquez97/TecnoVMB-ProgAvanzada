#ifndef HABITACION_H_
#define HABITACION_H_
#include "../../ICollection/interfaces/ICollectible.h"
#include "../../datatypes/headers/DTHabitacion.h"
#include "../../ICollection/interfaces/IDictionary.h"
#include "Hostal.h"
#include "../../classes/headers/ReservaIndividual.h"

class Habitacion: public ICollectible {
    private:
        int numero;
        float precio;
        int capacidad;
        Hostal* puntero_hostal; //hostal al que pertenece
        IDictionary* estadias;
        IDictionary* reservas;
    public:
        Habitacion();
        Habitacion(DTHabitacion nueva_habitacion,Hostal* puntero_hostal);
        Habitacion(int numero, float precio, int capacidad,Hostal* puntero_hostal);
        Habitacion(const Habitacion &Habitacion);
        ~Habitacion();
        void set_numero(int numero);
        void set_precio(float precio);
        void set_capacidad(int capacidad);
        void set_puntero_hostal(Hostal* puntero_hostal);
        int get_numero();
        float get_precio();
        int get_capacidad();
        Hostal* get_puntero_hostal();
        DTHabitacion get_DT();
        OrderedDictionary* get_reservas();
        void crear_reserva(int codigo,Huesped* huesped, tm* checkin, tm* checkout);
};

#endif // HABITACION_H_