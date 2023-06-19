#ifndef HUESPED_CPP_
#define HUESPED_CPP_
#include "../headers/Huesped.h"

Huesped::Huesped():Usuario(){

}

Huesped::Huesped(string nombre, string email, string contrasena, bool es_tecno):Usuario(nombre, email, contrasena){
    this -> es_tecno = es_tecno;
}

Huesped::Huesped(DTHuesped nuevo_huesped):Usuario(nuevo_huesped.get_nombre(), nuevo_huesped.get_email(),nuevo_huesped.get_contrasena()){
    this -> es_tecno = nuevo_huesped.get_es_tecno();
}

bool Huesped::get_es_tecno(){

}

DTHuesped Huesped::get_DT(){

}


#endif // HUESPED_CPP_