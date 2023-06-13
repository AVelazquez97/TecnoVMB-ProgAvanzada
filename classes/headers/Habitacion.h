#ifndef HABITACION_H_
#define HABITACION_H_
#include "../../datatypes/headers/DTHabitacion.h"
#include "Hostal.h"

class Habitacion {
    private:
        int numero;
        float precio;
        int capacidad;
        Hostal pertenece; //hostal al que pertenece
    public:
        Habitacion();
        Habitacion(int numero, float precio, int capacidad,Hostal pertenece);
        Habitacion(const Habitacion &Habitacion);
        ~Habitacion();
        void set_numero(int numero);
        void set_precio(float precio);
        void set_capacidad(int capacidad);
        void set_pertenece(Hostal pertenece);
        int get_numero();
        float get_precio();
        int get_capacidad();
        Hostal get_pertenece();
        DTHabitacion get_DT();
};

#endif // HABITACION_H_