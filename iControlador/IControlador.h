#ifndef ICONTROLADOR_H
#define ICONTROLADOR_H

#include <iostream>
// #include <ctime>
#include <chrono>

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

		/* En esta sección se definen todas las operaciones que están definidas en el controlador. 
		 * Estas deben ser virtuales e igualadas a 0
        */
        
        //Cambiar fecha del sistema
        virtual tm* get_fecha_sistema() = 0; 
        virtual void set_fecha_sistema(tm* nueva_fecha) = 0;

        virtual void alta_huesped(DTHuesped nuevo_huesped) = 0;
        virtual void alta_empleado(DTEmpleado nuevo_empleado) = 0;
        virtual void alta_hostal(DTHostal nuevo_hostal) = 0;
        virtual void alta_habitacion(DTHabitacion nueva_habitacion, string nombre_habitacion) = 0;
        virtual void asignar_empleado_hostal(string nombre_hostal,string email_empleado,Cargo cargo) = 0;
    
        /*funciones auxiliares*/
        virtual bool verificar_email(string entrada) = 0;
        virtual void existe_hostal(string nombre) = 0;
        virtual void no_existe_hostal(string nombre) = 0;
        virtual OrderedDictionary* obtener_hostales() = 0;
        virtual OrderedDictionary* obtener_no_empleados_hostal(string nombre_hostal) = 0;
};

#endif