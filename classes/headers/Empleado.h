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
        Empleado(string nombre, string email, string contrasena, Cargo cargo);
        Empleado(string nombre, string email, string contrasena, Cargo cargo, Hostal* puntero_hostal);
        Empleado(DTEmpleado nuevo_empleado);
        Empleado(const Empleado &Empleado);
        ~Empleado();
        Hostal* get_puntero_hostal();
        Cargo get_cargo();
        DTEmpleado get_DT();
        void asignar_cargo(Cargo cargo,Hostal* puntero_hostal);
        Hostal* get_hostal();
};


#endif // EMPLEADO_H_