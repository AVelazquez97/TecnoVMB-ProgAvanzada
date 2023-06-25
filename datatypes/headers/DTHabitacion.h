#ifndef DTHABITACION_H_
#define DTHABITACION_H_
//#include "../../classes/headers/Hostal.h"
#include "../../ICollection/interfaces/ICollectible.h"
#include <iostream>
using namespace std;

class DTHabitacion: public ICollectible{
    private:
        int numero;
        float precio;
        int capacidad;
        string nombre_hostal; //el nombre del hostal al que pertenece la hab
    public:
        DTHabitacion();
        DTHabitacion(int numero, float precio, int capacidad);
        int get_numero();
        float get_precio();
        int get_capacidad();
        string get_nombre_hostal();
};


#endif // DTHABITACION_H_