#ifndef REVIEW_CPP_
#define REVIEW_CPP_
#include "../headers/Review.h"
Review::Review(){}

Review::Review(int codigo, tm* fecha, int calificacion, string comentario,Hostal* ptr_hostal){
    this -> codigo = codigo;
    
    tm fecha_tm = *fecha;
    time_t fecha_time = mktime(&fecha_tm);
    this -> fecha = chrono::system_clock::from_time_t(fecha_time);

    this -> calificacion = calificacion;
    this -> comentario = comentario;
    this -> ptr_hostal = ptr_hostal;
}
int Review::get_codigo(){
    return this -> codigo;
}

tm* Review::get_fecha(){
    time_t fecha = chrono::system_clock::to_time_t(this->fecha);
    tm* fecha_tm = localtime(&fecha);
    return fecha_tm;
}
int Review::get_calificacion(){
    return this -> calificacion;
}
string Review::get_comentario(){
    return this -> comentario;
}
Hostal* Review::get_ptr_hostal(){
    return this -> ptr_hostal;
}
Respuesta* Review::get_ptr_respuesta(){
    return this -> respuesta;
}
#endif // REVIEW_CPP_