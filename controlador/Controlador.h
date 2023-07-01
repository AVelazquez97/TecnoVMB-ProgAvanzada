#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <iostream>
#include <string.h>

#include "../iControlador/IControlador.h"

// Acá se deben importar las clases del DCD
#include "../classes/headers/Empleado.h"
//#include "../classes/headers/Habitacion.h"
#include "../classes/headers/Hostal.h"
#include "../classes/headers/Huesped.h"
#include "../classes/headers/Usuario.h"
#include "../classes/headers/Reserva.h"
#include "../ICollection/collections/OrderedDictionary.h"
#include "../ICollection/String.h"

/*datatypes*/
#include "../datatypes/headers/DTUsuario.h"
#include "../datatypes/headers/DTHuesped.h"
#include "../datatypes/headers/DTEmpleado.h"


/// @brief el controlador realiza todas las operaciones del sistema.
/// Como utiliza el patrón singleton, se define el constructor como privado y se puede instanciar una única vez
class Controlador: public IControlador {
	private:
        Controlador();
        static Controlador* instance;
        chrono::system_clock::time_point fecha_sistema;
        int contador_reserva;
        int contador_estadia;

        //Acá pueden ir pseudoatributos a utilizar. También colecciones. Ejemplo:
        IDictionary* hostales;
        IDictionary* huespedes;
        IDictionary* empleados;

	public:
        ~Controlador();
        static Controlador* getInstance();        

        /* Fecha del sistema*/
        tm* get_fecha_sistema();
        void set_fecha_sistema(tm* nueva_fecha);
        ComparacionFecha compararFechas(tm* fechaNueva);
        bool comparar_fechas_reserva(Reserva* r, tm* fecha_deseada_checkin, tm* fecha_deseada_checkout);
		/* Fin fecha del sistema*/

        /* Contadores */
        void set_contador(int numero);
        int get_contador();

        void set_contador_estadia(int numero);
        int get_contador_estadia();

        /* Operaciones de los casos de uso*/
        void alta_huesped(DTHuesped nuevo_huesped);
        void alta_empleado(DTEmpleado nuevo_empleado);
        void alta_hostal(DTHostal nuevo_hostal);
        void alta_habitacion(DTHabitacion nueva_habitacion, string nombre_hostal);
        void asignar_empleado_hostal(string nombre_hostal,string email_empleado,Cargo cargo);
        void alta_reserva_individual(string nombre_hostal, int numero_Habitacion, string email_huesped, tm* checkin, tm* checkout);
        void alta_reserva_grupal(string nombre_hostal, int numero_habitacion, OrderedDictionary* lista_huespedes_seleccionados, tm* checkin, tm* checkout);
        OrderedDictionary* obtener_top_3_hostales();
        void alta_estadia(int codigo_reserva,string email_huesped, string nombre_hostal);
        void finalizar_estadia(int codigo_estadia,string email_huesped);
		/* Fin operaciones de los casos de uso*/

        /* Operaciones auxiliares*/
        bool verificar_email(string entrada);
        void existe_hostal(string nombre);
        void no_existe_hostal(string nombre);
        bool existe_hostal_bool(string nombre_hostal);
        OrderedDictionary* obtener_hostales();
        OrderedDictionary* obtener_no_empleados_hostal(string nombre_hostal);
        OrderedDictionary* obtener_usuarios();
        int verificar_email_y_tipo(string email);
        DTHuesped obtener_huesped_completo(string email);
        DTEmpleado obtener_empleado_completo(string email);
        OrderedDictionary* obtener_habitaciones_individuales(string nombre_hostal, string str_tipo, tm *checkin, tm *checkout);
        OrderedDictionary* obtener_habitaciones_grupales(string nombre_hostal, string str_tipo, tm *checkin, tm *checkout);
        OrderedDictionary* obtener_huespedes();
        int obtener_capacidad_habitacion(int numero_habitacion, string nombre_hostal);
        OrderedDictionary* obtener_reserva_usuario(string nombre_hostal,string email);
        int existe_estadia(string nombre_hostal, string email_huesped);
        /* Fin operaciones auxiliares*/
};
    
#endif