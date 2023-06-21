#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define CYAN "\e[0;36m"
#define REDB "\e[41m"

void mostrar_menu_principal();
int eleccion_menu_principal();
void press_enter();
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
 
#endif // FUNCTIONS_H_