#ifndef RESPUESTA_CPP_
#define RESPUESTA_CPP_
#include "../headers/Respuesta.h"
Respuesta::Respuesta(){}

Respuesta::Respuesta(string comentario, Empleado* ptr_empleado){
    this -> comentario = comentario;
    this -> ptr_empleado = ptr_empleado;
}
string Respuesta::get_comentario(){
    return this -> comentario;
}
Empleado* Respuesta::get_ptr_empleado(){
    return this -> ptr_empleado;
}
#endif // RESPUESTA_CPP_