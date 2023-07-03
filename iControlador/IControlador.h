#ifndef ICONTROLADOR_H
#define ICONTROLADOR_H

#include <iostream>
#include <chrono>

// Se deben importar todos los datatypes a utilizar en las definiciones de las operaciones
#include "../datatypes/headers/DTHabitacion.h"
#include "../datatypes/headers/DTHostal.h"
#include "../datatypes/headers/DTUsuario.h"
#include "../datatypes/headers/DTHuesped.h"
#include "../datatypes/headers/DTEmpleado.h"

#include "../enums/EnumCargo.h"
#include "../enums/EnumEstado.h"
#include "../enums/EnumTipo.h"
#include "../enums/EnumComparacionFecha.h"

using namespace std;

/// @brief interfaz en la que se ofrecen todas las operaciones que realiza el controlador.
/// Todas las operaciones ofrecidas deben ser virtuales y estar igualadas a 0
class IControlador {
    private: 

    public:
        virtual ~IControlador();

        /* Fecha del sistema*/
        virtual tm* get_fecha_sistema() = 0; 
        virtual void set_fecha_sistema(tm* nueva_fecha) = 0;
        virtual ComparacionFecha compararFechas(tm* fechaNueva) = 0;
        /* Fin fecha del sistema*/

        /* Contadores */
        virtual void set_contador_reserva(int numero) = 0;
        virtual int get_contador_reserva() = 0;
        virtual void set_contador_estadia(int numero) = 0;
        virtual int get_contador_estadia() = 0;
        virtual void set_contador_review(int numero) = 0;
        virtual int get_contador_review() = 0;

        /* Operaciones de los casos de uso*/
        virtual void alta_huesped(DTHuesped nuevo_huesped) = 0;
        virtual void alta_empleado(DTEmpleado nuevo_empleado) = 0;
        virtual void alta_hostal(DTHostal nuevo_hostal) = 0;
        virtual void alta_habitacion(DTHabitacion nueva_habitacion, string nombre_habitacion) = 0;
        virtual void asignar_empleado_hostal(string nombre_hostal,string email_empleado,Cargo cargo) = 0;
        virtual void alta_reserva_individual(string nombre_hostal, int numero_Habitacion, string email_huesped, tm* checkin, tm* checkout) = 0;
        virtual void alta_reserva_grupal(string nombre_hostal, int numero_habitacion, OrderedDictionary* lista_huespedes_seleccionados, tm* checkin, tm* checkout) = 0;
        virtual OrderedDictionary* obtener_top_3_hostales() = 0;
        virtual void alta_estadia(int codigo_reserva,string email_huesped /*,string nombre_hostal*/) = 0;
        virtual void finalizar_estadia(int codigo_estadia,string email_huesped) = 0;
        virtual OrderedDictionary* obtener_reservas_hostal(string nombre_hostal) = 0;
        virtual void calificar_estadia(string nombre_hostal,int codigo_estadia,string comentario, int calificacion,string email_huesped) = 0;
        /* Fin operaciones de los casos de uso*/

        /* Operaciones auxiliares*/
        virtual bool verificar_email(string entrada) = 0;
        virtual bool validar_email_huesped(string email_huesped) = 0;
        virtual void existe_hostal(string nombre) = 0;
        virtual void no_existe_hostal(string nombre) = 0;
        virtual bool existe_hostal_bool(string nombre_hostal) = 0;
        virtual OrderedDictionary* obtener_hostales() = 0;
        virtual OrderedDictionary* obtener_no_empleados_hostal(string nombre_hostal) = 0;
        virtual OrderedDictionary* obtener_usuarios() = 0;
        virtual int verificar_email_y_tipo(string email) = 0;
        virtual DTEmpleado obtener_empleado_completo(string email) = 0;
        virtual DTHuesped obtener_huesped_completo(string email) = 0;
        virtual OrderedDictionary* obtener_habitaciones_individuales(string nombre_hostal, string str_tipo, tm *checkin, tm *checkout) = 0;
        virtual OrderedDictionary* obtener_habitaciones_grupales(string nombre_hostal, string str_tipo, tm *checkin, tm *checkout) = 0;
        virtual OrderedDictionary* obtener_huespedes() = 0;
        virtual int obtener_capacidad_habitacion(int numero_habitacion, string nombre_hostal) = 0;
        virtual OrderedDictionary* obtener_reserva_usuario(string nombre_hostal,string email) = 0;
        virtual int existe_estadia(string nombre_hostal, string email_huesped) = 0;
        virtual OrderedDictionary* obtener_estadias_fin_huesped(string nombre_hostal,string email_huesped) = 0;
        

        /* Fin operaciones auxiliares*/
};

#endif