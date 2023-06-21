#ifndef DTEMPLEADO_H_
#define DTEMPLEADO_H_
#include "../../enums/EnumCargo.h"
#include "../../classes/headers/Hostal.h"
#include "../../ICollection/interfaces/ICollectible.h"
#include <iostream>
using namespace std;

class DTEmpleado: public ICollectible{
    private:
        string nombre;
        string email;
        string contrasena;
        string nombre_hostal;
        Cargo cargo;
    public:
        DTEmpleado();
        DTEmpleado(string nombre, string email, string contrasena, Cargo cargo);
        DTEmpleado(string nombre, string email, string contrasena, string nombre_hostal, Cargo cargo);
        //DTEmpleado(string nombre, string email, string nombre_hostal, Cargo cargo);
        string get_nombre();
        string get_email();
        string get_contrasena();
        string get_nombre_hostal();
        Cargo get_cargo();
};

#endif // DTEMPLEADO_H_