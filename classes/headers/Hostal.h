#ifndef HOSTAL_H_
#define HOSTAL_H_
//#include "../../classes/headers/Habitacion.h"
#include "../../datatypes/headers/DTHostal.h"
#include "../../datatypes/headers/DTHabitacion.h"
#include "../../ICollection/collections/OrderedDictionary.h"
#include "../../ICollection/Integer.h"
#include <iostream>
using namespace std;

class Hostal: public ICollectible{
    private:
        string nombre;
        string direccion;
        string telefono;
        IDictionary* habitaciones;/*aca va a ir la lista de habitaciones que pertenecen al hostal*/
        IDictionary* reviews; /*lista de reviews en ese hostal*/
        IDictionary* empleados; /*lista de empleados en ese hostal*/
    public:
        Hostal();
        Hostal(DTHostal nuevo_hostal);
        Hostal(string nombre, string direccion, string telefono);
        Hostal(const Hostal &Hostal);
        ~Hostal();
        void set_nombre(string nombre);
        void set_direccion(string direccion);
        void set_telefono(string telefono);
        string get_nombre();
        string get_direccion();
        string get_telefono();
        DTHostal get_DT();
        void alta_habitacion(DTHabitacion hab, Hostal* ptr_hostal);
};

#endif // HOSTAL_H_