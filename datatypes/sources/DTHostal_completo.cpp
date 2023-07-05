#ifndef DTHOSTAL_COMPLETO_CPP_
#define DTHOSTAL_COMPLETO_CPP_

#include "../headers/DTHostal_completo.h"
#include <iostream>

DTHostal_completo::DTHostal_completo(){
    this -> promedio = 0;
}

DTHostal_completo::DTHostal_completo(string nombre, string direccion, string telefono, float promedio, OrderedDictionary* dt_reviews, OrderedDictionary* dt_habitaciones){
    this -> nombre = nombre;
    this -> direccion = direccion;
    this -> telefono = telefono;
    this -> promedio = promedio;

    this -> dt_reviews = new OrderedDictionary();
    for(IIterator* it = dt_reviews->getIterator(); it -> hasCurrent(); it -> next()){
        DTReview* review = dynamic_cast<DTReview*>(it -> getCurrent());
        this->dt_reviews->add(new Integer(review -> get_codigo()), review);
    }

    this -> dt_habitaciones = new OrderedDictionary();
    for(IIterator* it = dt_habitaciones->getIterator(); it -> hasCurrent(); it -> next()){
        DTHabitacion* habitacion = dynamic_cast<DTHabitacion*>(it -> getCurrent());
        this->dt_habitaciones->add(new Integer(habitacion -> get_numero()), habitacion);
    }
}

string DTHostal_completo::get_nombre(){
    return this -> nombre;
}

string DTHostal_completo::get_direccion(){
    return this -> direccion;
}

string DTHostal_completo::get_telefono(){
    return this -> telefono;
}

float DTHostal_completo::get_promedio(){
    return this -> promedio;
}

OrderedDictionary* DTHostal_completo::get_dt_reviews(){
    return dynamic_cast<OrderedDictionary*>(dt_reviews);
}

OrderedDictionary* DTHostal_completo::get_dt_habitaciones(){
    return dynamic_cast<OrderedDictionary*>(dt_habitaciones);
}

ostream& operator << (ostream& salida, DTHostal_completo hostal) {
    salida << "Nombre: " << hostal.get_nombre() << endl <<
		"Direccion: " << hostal.get_direccion() << endl <<
		"Telefono: " << hostal.get_telefono() << endl <<
		"Calificación Promedio: " << hostal.get_promedio() << endl;
        if(!hostal.get_dt_reviews()->isEmpty()){
            cout << endl << "Lista de reviews: " << endl; 
            for(IIterator* it = hostal.get_dt_reviews()-> getIterator(); it -> hasCurrent(); it -> next()){
                DTReview* review = dynamic_cast<DTReview*>(it -> getCurrent());
                cout << GREEN << *review << NC << endl;
            }
        } else{
            cout << endl << "Reviews: Aún no tiene reviews" << endl;
        }
        if(!hostal.get_dt_habitaciones()->isEmpty()){
            cout << endl << "Lista de habitaciones: " << endl; 
            for(IIterator* it = hostal.get_dt_habitaciones()-> getIterator(); it -> hasCurrent(); it -> next()){
                DTHabitacion* habitacion = dynamic_cast<DTHabitacion*>(it -> getCurrent());
                cout << CYAN << *habitacion << NC << endl;
            }
        } else{
            cout << endl << "Habitaciones: Aún no tiene habitaciones" << endl;
        }
    return salida;
} 


#endif // DTHOSTAL_COMPLETO_CPP_