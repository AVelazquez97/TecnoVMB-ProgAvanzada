#ifndef RESPUESTA_CPP_
#define RESPUESTA_CPP_
#include "../headers/Respuesta.h"
#include "../../iControlador/IControlador.h"
#include "../../fabrica/Fabrica.h"

Fabrica fab_respuesta;
IControlador* controlador_respuesta = fab_respuesta.getInterface();

Respuesta::Respuesta(){}

Respuesta::Respuesta(string comentario, Empleado* ptr_empleado){
    this -> comentario = comentario;
    this -> ptr_empleado = ptr_empleado;
    controlador_respuesta -> get_fecha_sistema();
}

Respuesta::Respuesta(string comentario, Empleado* ptr_empleado, tm* fecha){
    this -> comentario = comentario;
    this -> ptr_empleado = ptr_empleado;
    tm fecha_tm = *fecha;
    time_t fecha_time = mktime(&fecha_tm);
    this -> fecha = chrono::system_clock::from_time_t(fecha_time);
}

string Respuesta::get_comentario(){
    return this -> comentario;
}
Empleado* Respuesta::get_ptr_empleado(){
    return this -> ptr_empleado;
}
#endif // RESPUESTA_CPP_