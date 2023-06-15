#ifndef HABITACION_H_
#define HABITACION_H_
#include "../../ICollection/interfaces/ICollectible.h"
#include "../../datatypes/headers/DTHabitacion.h"
#include "Hostal.h"

class Habitacion: public ICollectible {
    private:
        int numero;
        float precio;
        int capacidad;
        Hostal* puntero_hostal; //hostal al que pertenece
    public:
        Habitacion();
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
};

#endif // HABITACION_H_