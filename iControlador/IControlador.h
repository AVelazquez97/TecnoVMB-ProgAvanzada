#ifndef ICONTROLADOR_H
#define ICONTROLADOR_H
#include <ctime>
#include <iostream>

// Se deben importar todos los datatypes a utilizar en las definiciones de las operaciones
#include "../datatypes/headers/DTHabitacion.h"
#include "../datatypes/headers/DTHostal.h"
#include "../datatypes/headers/DTUsuario.h"

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
        virtual void alta_huesped() = 0;
        virtual void alta_empleado() = 0;
        virtual bool verificar_email(string entrada) = 0;
};

#endif