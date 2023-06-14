#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "../iControlador/IControlador.h"

// Acá se deben importar las clases del DCD
#include "../classes/headers/Habitacion.h"


class Controlador: public IControlador{
	private:
        Controlador();
        static Controlador* instance;
        time_t fecha_sistema = time(NULL);

        //Acá pueden ir pseudoatributos a utilizar

        //También colecciones. Ejemplo:
	//IDictionary* usuarios = new OrderedDictionary();

	public:
        ~Controlador();
        static Controlador* getInstance(); 

        //Modificar fecha del sistema
        time_t* getFechaSistema();
        void setFechaSistema(tm*);
};
    
#endif