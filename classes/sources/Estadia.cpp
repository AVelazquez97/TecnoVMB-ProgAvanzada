#ifndef ESTADIA_CPP_
#define ESTADIA_CPP_
#include "../headers/Estadia.h"
#include "../../iControlador/IControlador.h"
#include "../../fabrica/Fabrica.h"

Fabrica fab_estadia;
IControlador* controlador_estadia = fab_estadia.getInterface();

Estadia::Estadia(){}

Estadia::Estadia(int codigo, tm* checkin, Habitacion* ptr_habitacion, Huesped* ptr_huesped){
    this -> codigo = codigo;
   
    tm checkin_tm = *checkin;
    time_t checkin_time = mktime(&checkin_tm);
    this -> checkin = chrono::system_clock::from_time_t(checkin_time);

    this -> ptr_habitacion = ptr_habitacion;

    this -> ptr_huesped = ptr_huesped;

    ptr_huesped -> asignar_estadia_usuario(this);

    this -> ptr_review = NULL;
}
Habitacion* Estadia::get_ptr_habitacion(){
    return this -> ptr_habitacion;
}
void Estadia::set_checkin(tm* checkin){
    tm checkin_tm = *checkin;
    time_t checkin_time = mktime(&checkin_tm);
    this -> checkin = chrono::system_clock::from_time_t(checkin_time);
}

void Estadia::set_checkout(tm* checkout){
    tm checkout_tm = *checkout;
    time_t checkout_time = mktime(&checkout_tm);
    this -> checkout = chrono::system_clock::from_time_t(checkout_time);
}

int Estadia::get_codigo(){
    return this -> codigo;
}

tm* Estadia::get_checkin(){
    time_t checkin = chrono::system_clock::to_time_t(this->checkin);
    tm* checkin_tm = localtime(&checkin);
    return checkin_tm;
}

tm* Estadia::get_checkout(){
    time_t checkout = chrono::system_clock::to_time_t(this->checkout);
    tm* checkout_tm = localtime(&checkout);
    return checkout_tm;
}
chrono::system_clock::time_point Estadia::get_checkout_chrono(){
    return this -> checkout;
}
bool Estadia::perteneceA(string nombre_hostal){
    return ptr_habitacion -> pertenece_a_hostal(nombre_hostal);
}
void Estadia::finalizar(){
    tm checkout_tm = *controlador_estadia -> get_fecha_sistema();
    time_t checkout_time = mktime(&checkout_tm);
    this -> checkout = chrono::system_clock::from_time_t(checkout_time);
}
string Estadia::get_email(){
    return this -> ptr_huesped -> get_email();
}
bool Estadia::finalizo(string nombre_hostal){
    if(get_checkout_chrono().time_since_epoch() != decltype(get_checkout_chrono())::duration::zero()){
        return this -> ptr_habitacion -> pertenece_a_hostal(nombre_hostal);
        //return (this -> ptr_habitacion -> get_puntero_hostal() -> get_nombre() == nombre_hostal);
    }else{
        return false;
    }
}

bool Estadia::no_finalizo(){
    if(get_checkout_chrono().time_since_epoch() == decltype(get_checkout_chrono())::duration::zero()){
        return true;
    }else{
        return false;
    }
}

bool Estadia::no_finalizo(string nombre_hostal){
     if(get_checkout_chrono().time_since_epoch() == decltype(get_checkout_chrono())::duration::zero()){
        return this -> ptr_habitacion -> pertenece_a_hostal(nombre_hostal);
        //return (this -> ptr_habitacion -> get_puntero_hostal() -> get_nombre() == nombre_hostal);
    }else{
        return false;
    }
}

void Estadia::agregarCalificacion(Hostal* ptr_hostal,string comentario,int calificacion){
    Review* review = new Review(controlador_estadia ->get_contador_review(),controlador_estadia ->get_fecha_sistema(),calificacion,comentario,ptr_hostal);
    this -> ptr_review = review;
    ptr_hostal -> asignar_review(review);
    
    int nuevo_valor_contador = controlador_estadia ->get_contador_review();
    nuevo_valor_contador += 1;
    controlador_estadia -> set_contador_review(nuevo_valor_contador);
}
bool Estadia::tenes_review(){
    return this -> ptr_review == NULL;
}
DTReview Estadia::darDTReview(){
    return this -> ptr_review -> get_DT();
}
Review* Estadia::get_review(){
    return this->ptr_review;
}
Review* Estadia::get_review_sin_responder(){
    if(this->ptr_review -> get_ptr_respuesta() == NULL){
        return this->ptr_review;
    }    
}
bool Estadia::coincide(int codigo_review){
    if(this -> ptr_review != NULL){
        if(this -> ptr_review -> get_codigo() == codigo_review){
            return true;
        }else{
            return false;
            }
    }else{
        return false;
    }

}
void Estadia::alta_respuesta(Empleado* ptr_empleado,string respuesta){
    this -> ptr_review -> alta_respuesta(ptr_empleado,respuesta);
}
#endif // ESTADIA_CPP_