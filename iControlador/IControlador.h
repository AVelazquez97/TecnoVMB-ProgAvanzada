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
        virtual OrderedDictionary* obtener_usuarios() = 0;
        virtual int verificar_email_y_tipo(string email) = 0;
        virtual DTEmpleado obtener_empleado_completo(string email) = 0;
        virtual DTHuesped obtener_huesped_completo(string email) = 0;
};

#endif