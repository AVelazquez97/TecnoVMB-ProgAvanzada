#ifndef HABITACION_H_
#define HABITACION_H_
#include "../../datatypes/headers/DTHabitacion.h"
class Habitacion {
    private:
        int numero;
        float precio;
        int capacidad;
    public:
        Habitacion();
        Habitacion(int numero, float precio, int capacidad);
        Habitacion(const Habitacion &Habitacion);
        ~Habitacion();
        void set_numero(int numero);
        void set_precio(float precio);
        void set_capacidad(int capacidad);
        int get_numero();
        float get_precio();
        int get_capacidad();
        DTHabitacion get_DT();
};

#endif // HABITACION_H_