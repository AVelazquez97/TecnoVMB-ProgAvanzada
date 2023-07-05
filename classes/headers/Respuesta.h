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
        chrono::system_clock::time_point fecha;
    public:
        Respuesta();
        Respuesta(string comentario, Empleado* ptr_empleado);
        Respuesta(string comentario, Empleado* ptr_empleado, tm* fecha);
        string get_comentario();
        Empleado* get_ptr_empleado();
};


#endif // RESPUESTA_H_