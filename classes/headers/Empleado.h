#ifndef EMPLEADO_H_
#define EMPLEADO_H_
#include "Usuario.h"
#include "../../enums/EnumCargo.h"
#include "../../datatypes/headers/DTEmpleado.h"
#include "Hostal.h"

class Empleado: public Usuario{
    private:
        Hostal* puntero_hostal;
        Cargo cargo;
    public:
        Empleado();
        Empleado(string nombre, string email, string contrasena, Cargo cargo, Hostal* puntero_hostal);
        Empleado(DTEmpleado nuevo_empleado);
        Empleado(const Empleado &Empleado);
        ~Empleado();
        Hostal* get_puntero_hostal();
        Cargo get_cargo();
        DTEmpleado get_DT();
};


#endif // EMPLEADO_H_