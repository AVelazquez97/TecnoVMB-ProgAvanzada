#ifndef ICONTROLADOR_H
#define ICONTROLADOR_H
#include <ctime>
#include <iostream>

// Se deben importar todos los datatypes a utilizar en las definiciones de las operaciones
#include "../datatypes/headers/DTHabitacion.h"
#include "../datatypes/headers/DTHostal.h"
#include "../datatypes/headers/DTUsuario.h"
#include "../datatypes/headers/DTHuesped.h"
#include "../datatypes/headers/DTEmpleado.h"

#include "../enums/EnumCargo.h"
#include "../enums/EnumEstado.h"
#include "../enums/EnumTipo.h"

using namespace std;

// Esta sería la interfaz
class IControlador {
    private: 

    public:
        virtual ~IControlador();

		// En esta sección se definen todas las operaciones que están definidas en el controlador. 
		// Deben ser virtuales e igualadas a 0

        // Usuarios
        
        // Hostales
        
        // Reservas
        
        // Estadías

        //Cambiar fecha del sistema
        virtual void setFechaSistema(tm*) = 0;
        virtual time_t* getFechaSistema() = 0; 
        virtual void alta_huesped(DTHuesped nuevo_huesped) = 0;
        virtual void alta_huesped(string nombre, string email, string contrasena, bool es_tecno) = 0;
        virtual void alta_empleado(DTEmpleado nuevo_empleado) = 0;
        virtual void alta_empleado(string nombre, string email, string contrasena, Cargo cargo) = 0;
        virtual bool verificar_email(string entrada) = 0;
};

#endif