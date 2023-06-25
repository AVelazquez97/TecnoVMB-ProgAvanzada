#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <cmath>
#include <cstring>
#include <limits>

/*Librerías necesarias para la gestión de la fecha y hora*/
#include <chrono>
#include <iomanip>
#include <sstream>

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define CYAN "\e[0;36m"
#define REDB "\e[41m"

/*datatypes*/
#include "../datatypes/headers/DTHuesped.h"
#include "../datatypes/headers/DTEmpleado.h"
#include "../enums/EnumCargo.h"

#include "../iControlador/IControlador.h"
#include "../fabrica/Fabrica.h"

/* Funciones auxiliares*/
void mostrar_menu_principal();
int eleccion_menu_principal();
void press_enter();
Cargo switch_cargo(string str_cargo);
void imprimir_fecha(tm* fecha);
bool verificar_fecha(string fecha_hora_str, tm* nueva_fecha);
void obtener_hostales();
void obtener_hostales_con_promedio();
void obtener_no_empleados_hostal(string nombre_hostal);
void obtener_habitaciones_entre(string nombre_hostal,string str_checkin,string str_checkout);
void obtener_usuarios();
void obtener_huesped_completo(string email);
void obtener_empleado_completo(string email);
/* Fin funciones auxiliares*/

/*Funciones del menu principal*/
void alta_usuario();
void alta_hostal();
void alta_habitacion();
void asignar_empleado_hostal();
void realizar_reserva();
void consultar_top_3();
void registrar_estadia();
void finalizar_estadia();
void calificar_estadia();
void comentar_calificacion();
void consulta_usuario();
void consulta_hostal();
void consulta_reserva();
void consulta_estadia();
void baja_reserva();
void modificar_fecha();
void datos_prueba();
void exit();
/*Fin funciones del menu principal*/

#endif // FUNCTIONS_H_