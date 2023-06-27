#ifndef HUESPED_CPP_
#define HUESPED_CPP_
#include "../headers/Huesped.h"
#include "../../classes/headers/ReservaIndividual.h"

Huesped::Huesped():Usuario(){

}

Huesped::Huesped(string nombre, string email, string contrasena, bool es_tecno):Usuario(nombre, email, contrasena){
    this -> es_tecno = es_tecno;
    this -> reservas = new OrderedDictionary();
}

Huesped::Huesped(DTHuesped nuevo_huesped):Usuario(nuevo_huesped.get_nombre(), nuevo_huesped.get_email(),nuevo_huesped.get_contrasena()){
    this -> es_tecno = nuevo_huesped.get_es_tecno();
    this -> reservas = new OrderedDictionary();
}

bool Huesped::get_es_tecno(){
    return this -> es_tecno;
}

DTHuesped Huesped::get_DT(){
    return DTHuesped(this -> get_nombre(), this -> get_email(), this -> get_contrasena(), this -> get_es_tecno());
}

void Huesped::asignar_reserva(ReservaGrupal* rg){
    IKey* ik_rg = new Integer(rg -> get_codigo());
    this -> reservas -> add(ik_rg,rg);
}

void Huesped::asignar_reserva(ReservaIndividual* ri){
    IKey* ik_ri = new Integer(ri -> get_codigo());
    this -> reservas -> add(ik_ri,ri);
}

#endif // HUESPED_CPP_