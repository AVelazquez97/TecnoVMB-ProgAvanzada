#ifndef DTHOSTAL_H_
#define DTHOSTAL_H_
#include "../../ICollection/interfaces/ICollectible.h"
#include <iostream>
using namespace std;

class DTHostal: public ICollectible{
    private:
        string nombre;
        string direccion;
        string telefono;
        float promedio;
    public:
        DTHostal();
        DTHostal(string nombre, string direccion, string telefono);
        DTHostal(string nombre, string direccion, string telefono, float promedio);
        string get_nombre();
        string get_direccion();
        string get_telefono();
        float get_promedio();
        friend ostream& operator << (ostream& salida, DTHostal hostal);
};

#endif // DTHOSTAL_H_