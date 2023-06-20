#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "../iControlador/IControlador.h"

// Acá se deben importar las clases del DCD
#include "../classes/headers/Empleado.h"
#include "../classes/headers/Habitacion.h"
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
        time_t fecha_sistema = time(NULL);

        //Acá pueden ir pseudoatributos a utilizar

        //También colecciones. Ejemplo:

        IDictionary* hostales;
        IDictionary* huespedes;
        IDictionary* empleados;

	public:
        ~Controlador();
        static Controlador* getInstance(); 

        //Modificar fecha del sistema
        time_t* getFechaSistema();
        void setFechaSistema(tm*);

        //Cabeceras de las opers
        void alta_huesped(DTHuesped nuevo_huesped);
        void alta_huesped(string nombre, string email, string contrasena, bool es_tecno);
        void alta_empleado(DTEmpleado nuevo_empleado);
        void alta_empleado(string nombre, string email, string contrasena, Cargo cargo);
        bool verificar_email(string entrada);
};
    
#endif