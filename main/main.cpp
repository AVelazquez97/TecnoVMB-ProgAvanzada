#ifndef MAIN_CPP_
#define MAIN_CPP_

#include "../iControlador/IControlador.h"
#include "../fabrica/Fabrica.h"
#include "functions.h"

/*Tanto si la fabrica se utiliza acá como en el fichero de funciones se debería utilizar de la siguiente manera:
    Fabrica fab;
    IControlador* controlador = fab.getInterface();
    controlador->operacion
*/

// En el main no debería importarse ninguna clase
#include "../datatypes/headers/DTHabitacion.h" // Esto debería importarse en IControlador.h
#include "../classes/headers/Habitacion.h" // Esto debería importarse en Controlador.h

int main(int argc, char* argv[]){
    int opcion = 0;
    while(opcion != 7){
		opcion = eleccion_menu_principal();
		switch (opcion){
			case 1: { //Gestión de Usuarios
                break;
			}
            case 2: { //Gestión de Hostales
                break;
			}
            case 3: { //Gestión de Reservas
                break;
			}
            case 4: { //Gestión de Estadías
                break;
			}
            case 5: { //Modificar fecha del sistema
                break;
			}
            case 6: { //Cargar de Datos de Prueba
                break;
			}
            case 7: { // Salir
                return 0;
            }
        }
    }
    return 0;
}

#endif // MAIN_CPP_