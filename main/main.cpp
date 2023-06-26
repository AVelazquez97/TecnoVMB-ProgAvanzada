#ifndef MAIN_CPP_
#define MAIN_CPP_

#include "../iControlador/IControlador.h"
#include "../fabrica/Fabrica.h"
#include "functions.h"

// En el main no debería importarse ninguna clase

int main(int argc, char* argv[]){
    int opcion = 0;
    innit_contador();

    while(opcion != 18){
		opcion = eleccion_menu_principal();
		switch (opcion){
			case 1: { //Alta usuario
                alta_usuario();
                press_enter();
                break;
			}
            case 2: { //Alta hostal
                alta_hostal();
                press_enter();
                break;
			}
            case 3: { //Alta habitacion
                alta_habitacion();
                press_enter();
                break;
			}
            case 4: { //Asignar empleado a hostal
                asignar_empleado_hostal();
                press_enter();
                break;
			}
            case 5: { //Realizar reserva
                realizar_reserva();
                press_enter();
                break;
			}
            case 6: { //Consultar top 3 de hostales
                consultar_top_3();
                press_enter();
                break;
            }
            case 7: { //Registrar estadia
                registrar_estadia();
                press_enter();
                break;
            }
            case 8: { //Finalizar estadia
                finalizar_estadia();
                press_enter();
                break;
            }
            case 9: { //Calificar estadia
                calificar_estadia();
                press_enter();
                break;
            }
            case 10: { //Comentar calificacion
                comentar_calificacion();
                press_enter();
                break;
            }
            case 11: { //Consulta de usuario
                consulta_usuario();
                press_enter();
                break;
            }
            case 12: { //Consulta de hostal
                consulta_hostal();
                press_enter();
                break;
            }
            case 13: { //Consulta de reserva
                consulta_reserva();
                press_enter();
                break;
            }
            case 14: { //Consulta de estadia
                consulta_estadia();
                press_enter();
                break;
            }
            case 15: { //Baja de reserva
                baja_reserva();
                press_enter();
                break;
            }
            case 16: { //Modificar fecha del sistema
                modificar_fecha();
                press_enter();
                break;
            }
            case 17: { //Cargar de Datos de Prueba
                datos_prueba();
                press_enter();
                break;
			}
            case 18: { // Salir
                exit();
                return 0;
            }
        }
        system("clear");
    }
    return 0;
}

#endif // MAIN_CPP_