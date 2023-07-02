#ifndef HOSTAL_H_
#define HOSTAL_H_
//#include "../../classes/headers/Habitacion.h"
#include "../../datatypes/headers/DTHostal.h"
//#include "Empleado.h"
#include "../../datatypes/headers/DTHabitacion.h"
#include "../../ICollection/collections/OrderedDictionary.h"
#include "../../ICollection/Integer.h"
#include <iostream>
using namespace std;
class Empleado;
class Huesped;

class Hostal: public ICollectible{
    private:
        string nombre;
        string direccion;
        string telefono;
        IDictionary* habitaciones;/*aca va a ir la lista de habitaciones que pertenecen al hostal*/
        IDictionary* reviews; /*lista de reviews en ese hostal*/
        IDictionary* empleados; /*lista de empleados en ese hostal*/
        float promedio;

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
        float get_promedio();
        DTHostal get_DT();
        bool no_es(string email);
        void alta_habitacion(DTHabitacion hab, Hostal* ptr_hostal);
        void asignar_empleado(Empleado* puntero_empleado);
        void agregar_reserva(int codigo,int numero_habitacion, Huesped* huesped, tm* checkin, tm* checkout, bool tipo);
        void agregar_reserva(int codigo, int numero_habitacion, OrderedDictionary* huespedes_encontrados, tm* checkin, tm* checkout, bool tipo);
        OrderedDictionary* get_habitaciones();
};

#endif // HOSTAL_H_