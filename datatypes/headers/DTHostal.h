#ifndef DTHOSTAL_H_
#define DTHOSTAL_H_
#include <iostream>
using namespace std;

class DTHostal{
    private:
        string nombre;
        string direccion;
        string telefono;
    public:
        DTHostal();
        DTHostal(string nombre, string direccion, string telefono);
        string get_nombre();
        string get_direccion();
        string get_telefono();
};

#endif // DTHOSTAL_H_