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
    this -> respuesta == NULL;
    //this -> ptr_hostal -> asignar_review(this);
}
int Review::get_codigo(){
    return this -> codigo;
}
DTReview Review::get_DT(){
    return DTReview(this -> get_codigo(),this -> get_fecha(),this ->get_calificacion(),this -> get_comentario());
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
bool Review::get_sin_responder(){
    return this -> get_ptr_respuesta() == NULL;
}
void Review::alta_respuesta(Empleado* ptr_empleado,string respuesta){
    Respuesta* ptr_respuesta = new Respuesta(respuesta,ptr_empleado);
    this -> respuesta = ptr_respuesta;
}

void Review::alta_respuesta(Empleado* ptr_empleado,string respuesta,tm* fecha){
    Respuesta* ptr_respuesta = new Respuesta(respuesta,ptr_empleado,fecha);
    this -> respuesta = ptr_respuesta;
}
#endif // REVIEW_CPP_