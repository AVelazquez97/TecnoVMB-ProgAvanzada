#ifndef HOSTAL_CPP_
#define HOSTAL_CPP_

#include <iostream>
#include <stdlib.h>
#include "string.h" 

#include "../headers/Hostal.h"
#include "../../classes/headers/Habitacion.h"
#include "../../classes/headers/Review.h"
#include "../../ICollection/String.h"
#include "../headers/Empleado.h" 

using namespace std;
Hostal::Hostal(){
    this -> promedio = 0;
    this -> habitaciones = new OrderedDictionary();
    this -> reviews = new OrderedDictionary();
    this -> empleados = new OrderedDictionary();
}

Hostal::Hostal(DTHostal nuevo_hostal){
    this -> nombre = nuevo_hostal.get_nombre();
    this -> direccion = nuevo_hostal.get_direccion();
    this -> telefono = nuevo_hostal.get_telefono();
    this -> habitaciones = new OrderedDictionary();
    this -> reviews = new OrderedDictionary();
    this -> empleados = new OrderedDictionary();
    this -> promedio = nuevo_hostal.get_promedio();
}

Hostal::Hostal(string nombre, string direccion, string telefono){
    this -> nombre = nombre;
    this -> direccion = direccion;
    this -> telefono = telefono;
    this -> habitaciones = new OrderedDictionary();
    this -> reviews = new OrderedDictionary();
    this -> empleados = new OrderedDictionary();
    this -> promedio = 0;
}

Hostal::Hostal(const Hostal& original){
    nombre = original.nombre;
    direccion = original.direccion;
    telefono = original.telefono;
    habitaciones = original.habitaciones;
    reviews = original.reviews;
    empleados = original.empleados;
    promedio = original.promedio;
}

Hostal::~Hostal(){

}

void Hostal::set_nombre(string nombre){
    this -> nombre = nombre;
}

void Hostal::set_direccion(string direccion){
    this -> direccion = direccion;
}

void Hostal::set_telefono(string telefono){
    this -> telefono = telefono;
}

string Hostal::get_nombre(){
    return this -> nombre;
}

string Hostal::get_direccion(){
    return this -> direccion;
}

string Hostal::get_telefono(){
    return this -> telefono;
}

float Hostal::get_promedio(){
    float suma_total = 0;
    float cantidad_dividir = 0;
    for(IIterator* it = this -> reviews -> getIterator(); it -> hasCurrent(); it -> next()){
        Review* review = dynamic_cast<Review*>(it -> getCurrent());
        suma_total += review -> get_calificacion();
        cantidad_dividir += 1;
    }
    /*si no tiene reviews, no puede dividir entre 0 porque da excepcion,
    por lo que directamente se devuelve 0*/
    if(cantidad_dividir == 0){
        return this -> promedio;
    }else{
        return suma_total/cantidad_dividir;
    }
}

DTHostal Hostal::get_DT(){
    return DTHostal(this -> get_nombre(),this -> get_direccion(), this -> get_telefono(), this -> get_promedio());
}

DTHostal_completo Hostal::get_DTCompleto(){
    OrderedDictionary* DTHabitaciones = new OrderedDictionary(); 
    OrderedDictionary* DTReviews = new OrderedDictionary(); 

    /* Se recorren todas las habitaciones y se obtiene su DT para almacenarlo en la lista de DTHabitacion*/
    for(IIterator* it = this->get_habitaciones()->getIterator(); it -> hasCurrent(); it -> next()){
        Habitacion* habitacion = dynamic_cast<Habitacion*>(it -> getCurrent());

        DTHabitacion* dt_habitacion = new DTHabitacion(habitacion->get_DT());

        // Se agrega a la lista
        DTHabitaciones -> add(new Integer(habitacion->get_numero()), dt_habitacion);
    }

    /* Se recorren todas las reviews y se obtiene su DT para almacenarlo en la lista de DTReview*/
    for(IIterator* it = this->get_reviews()->getIterator(); it -> hasCurrent(); it -> next()){
        Review* review = dynamic_cast<Review*>(it -> getCurrent());

        DTReview* dt_review = new DTReview(review->get_DT());

        // Se agrega a la lista
        DTReviews -> add(new Integer(review->get_codigo()), dt_review);
    }
    
    return DTHostal_completo(this->get_nombre(), this->get_direccion(), this->get_telefono(), this->get_promedio(), DTReviews, DTHabitaciones);
}

void Hostal::alta_habitacion(DTHabitacion hab, Hostal* ptr_hostal){
    Habitacion* nueva_habitacion = new Habitacion(hab,ptr_hostal);

    IKey* ik = new Integer(nueva_habitacion -> get_numero());

    this -> habitaciones -> add(ik,nueva_habitacion);
}

 bool Hostal::no_es(string email){
    char parce_char[email.length()+1];
    strcpy(parce_char,email.c_str());

    IKey* ik = new String(parce_char);
    return this -> empleados -> member(ik);
 }

void Hostal::asignar_empleado(Empleado* puntero_empleado){
    
    string email = puntero_empleado -> get_email();
    char parce_email[email.length()+1];
    strcpy(parce_email,email.c_str());

    IKey* ik = new String(parce_email);
    this -> empleados -> add(ik,puntero_empleado);
}
void Hostal::asignar_review(Review* ptr_review){
    int codigo = ptr_review -> get_codigo();
    IKey* ik_review = new Integer(codigo);
    this -> reviews -> add(ik_review,ptr_review);
}

void Hostal::agregar_reserva(int codigo,int numero_habitacion, Huesped* huesped, tm* checkin, tm* checkout, bool tipo){ 
    IKey* ik_habitacion = new Integer(numero_habitacion);
    Habitacion* habitacion = dynamic_cast<Habitacion*>( this -> habitaciones -> find(ik_habitacion));
    habitacion -> crear_reserva(codigo,huesped, checkin, checkout, tipo);
}

void Hostal::agregar_reserva(int codigo, int numero_habitacion, OrderedDictionary* huespedes_encontrados, tm* checkin, tm* checkout, bool tipo){
    IKey* ik_habitacion = new Integer(numero_habitacion);
    Habitacion* habitacion = dynamic_cast<Habitacion*>( this -> habitaciones -> find(ik_habitacion));
    habitacion -> crear_reserva(codigo,huespedes_encontrados, checkin, checkout, tipo);
}

OrderedDictionary* Hostal::get_habitaciones(){
    return dynamic_cast<OrderedDictionary*>(habitaciones);
}

OrderedDictionary* Hostal::get_reviews(){
    return dynamic_cast<OrderedDictionary*>(reviews);
}


#endif // HOSTAL_CPP_