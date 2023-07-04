#ifndef DTHOSTAL_COMPLETO_CPP_
#define DTHOSTAL_COMPLETO_CPP_

#include "../headers/DTHostal_completo.h"
#include <iostream>

DTHostal_completo::DTHostal_completo(){
    this -> promedio = 0;
}

DTHostal_completo::DTHostal_completo(string nombre, string direccion, string telefono, float promedio){
    this -> nombre = nombre;
    this -> direccion = direccion;
    this -> telefono = telefono;
    this -> promedio = promedio;
}

// DTHostal_completo::DTHostal_completo(string nombre, string direccion, string telefono, float promedio, OrderedDictionary* dt_reviews){

// }

// DTHostal_completo::DTHostal_completo(string nombre, string direccion, string telefono, float promedio, OrderedDictionary* dt_habitaciones){

// }

// DTHostal_completo::DTHostal_completo(string nombre, string direccion, string telefono, float promedio, OrderedDictionary* dt_reviews, OrderedDictionary* dt_habitaciones){

// }


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
    // OrderedDictionary* DT_Reviews = new OrderedDictionary();
	// DT_Reviews = hostal.get_dt_reviews();
	
    salida << "| Nombre: " << hostal.get_nombre() << " |" << endl <<
		"| Direccion: " << hostal.get_direccion() << " |" << endl <<
		"| Telefono: " << hostal.get_telefono() << " |" << endl <<
		"| Calificación Promedio: " << hostal.get_promedio() << " |" << endl 
        << endl;
        // /* cout << "| Lista de habitaciones: << imprimir habitaciones (idealmente con sobrecarga del <<)  << " |" << endl */
        // cout << "| Lista de reviews: " << endl; 
        // for(IIterator* it = DT_Reviews -> getIterator(); it -> hasCurrent(); it -> next()){
        //     DTReview* review = dynamic_cast<DTReview*>(it -> getCurrent());
        //     cout << *review << endl;
        // }
        // cout <<  " |" << endl;
    return salida;
} 


#endif // DTHOSTAL_COMPLETO_CPP_