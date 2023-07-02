#ifndef RESPUESTA_H_
#define RESPUESTA_H_
#include <iostream>
#include "Empleado.h"
#include "../../ICollection/collections/OrderedDictionary.h"
using namespace std;

class Respuesta: public ICollectible{
    private:
        string comentario;
        Empleado* ptr_empleado;
    public:
        Respuesta();
        Respuesta(string comentario, Empleado* ptr_empleado);
        string get_comentario();
        Empleado* get_ptr_empleado();
};


#endif // RESPUESTA_H_