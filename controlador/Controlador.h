#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "../iControlador/IControlador.h"

// Acá se deben importar las clases del DCD
#include "../classes/headers/Empleado.h"
//#include "../classes/headers/Habitacion.h"
#include "../classes/headers/Hostal.h"
#include "../classes/headers/Huesped.h"
#include "../classes/headers/Usuario.h"
#include "../ICollection/collections/OrderedDictionary.h"
#include "../ICollection/String.h"

/*datatypes*/
#include "../datatypes/headers/DTUsuario.h"
#include "../datatypes/headers/DTHuesped.h"
#include "../datatypes/headers/DTEmpleado.h"

#include <string.h>

class Controlador: public IControlador{
	private:
        Controlador();
        static Controlador* instance;
        chrono::system_clock::time_point fecha_sistema;

        //Acá pueden ir pseudoatributos a utilizar

        //También colecciones. Ejemplo:
        IDictionary* hostales;
        IDictionary* huespedes;
        IDictionary* empleados;

	public:
        ~Controlador();
        static Controlador* getInstance(); 

        //Modificar fecha del sistema
        tm* get_fecha_sistema();
        void set_fecha_sistema(tm* nueva_fecha);

        //Cabeceras de las opers
        void alta_huesped(DTHuesped nuevo_huesped);
        void alta_empleado(DTEmpleado nuevo_empleado);
        void alta_hostal(DTHostal nuevo_hostal);
        void alta_habitacion(DTHabitacion nueva_habitacion, string nombre_hostal);
        void realizar_reserva_individual(string nom_hostal,int Nhabitacion,string email);
        void realizar_reserva_grupal(string nom_hostal,int Nhabitacion,string emails[]);
        void asignar_empleado_hostal(string nombre_hostal,string email_empleado,Cargo cargo);

        /*funciones auxiliares*/
        bool verificar_email(string entrada);
        void existe_hostal(string nombre);
        void no_existe_hostal(string nombre);
        OrderedDictionary* obtener_hostales();
        OrderedDictionary* obtener_no_empleados_hostal(string nombre_hostal);
};
    
#endif