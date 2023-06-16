#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "../iControlador/IControlador.h"

// Acá se deben importar las clases del DCD
#include "../classes/headers/Empleado.h"
#include "../classes/headers/Habitacion.h"
#include "../classes/headers/Hostal.h"
#include "../classes/headers/Huesped.h"
#include "../classes/headers/Usuario.h"


class Controlador: public IControlador{
	private:
        Controlador();
        static Controlador* instance;
        time_t fecha_sistema = time(NULL);

        //Acá pueden ir pseudoatributos a utilizar

        //También colecciones. Ejemplo:
	//IDictionary* usuarios = new OrderedDictionary();
        /*diccionarios de hoteles*/
        /*diccionarios de usuarios*/
        /*diccionarios de empleado*/

	public:
        ~Controlador();
        static Controlador* getInstance(); 

        //Modificar fecha del sistema
        time_t* getFechaSistema();
        void setFechaSistema(tm*);

        //Cabeceras de las opers
        //void alta_huesped();
        //void alta_empleado();
};
    
#endif