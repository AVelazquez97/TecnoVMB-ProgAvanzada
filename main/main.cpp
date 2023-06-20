#ifndef MAIN_CPP_
#define MAIN_CPP_

#include "../iControlador/IControlador.h"
#include "../fabrica/Fabrica.h"
#include "functions.h"

// En el main no debería importarse ninguna clase

int main(int argc, char* argv[]){
    int opcion = 0;

    while(opcion != 18){
		opcion = eleccion_menu_principal();
		switch (opcion){
			case 1: { //Alta usuario
                alta_usuario();
                break;
			}
            case 2: { //Alta hostal
            
                break;
			}
            case 3: { //Alta habitacion
                break;
			}
            case 4: { //Asignar empleado a hostal
                break;
			}
            case 5: { //Realizar reserva
                break;
			}
            case 6: { //Consultar top 3 de hostales
                break;
            }
            case 7: { //Registrar estadia
                break;
            }
            case 8: { //Finalizar estadia
                break;
            }
            case 9: { //Calificar estadia
                break;
            }
            case 10: { //Comentar calificacion
                break;
            }
            case 11: { //Consulta de usuario
                break;
            }
            case 12: { //Consulta de hostal
                break;
            }
            case 13: { //Consulta de reserva
                break;
            }
            case 14: { //Consulta de estadia
                break;
            }
            case 15: { //Baja de reserva
                break;
            }
            case 16: { //Modificar fecha del sistema
                break;
            }
            case 17: { //Cargar de Datos de Prueba
                datos_prueba();
                break;
			}
            case 18: { // Salir
                return 0;
            }
        }
    }
    return 0;
}

#endif // MAIN_CPP_