#ifndef HUESPED_CPP_
#define HUESPED_CPP_
#include "../headers/Huesped.h"
#include "../../classes/headers/ReservaIndividual.h"
#include "../../classes/headers/ReservaGrupal.h"
#include "../../classes/headers/Estadia.h"
Huesped::Huesped():Usuario(){

}

Huesped::Huesped(string nombre, string email, string contrasena, bool es_tecno):Usuario(nombre, email, contrasena){
    this -> es_tecno = es_tecno;
    this -> reservas_grupales = new OrderedDictionary();
    this -> reservas_individuales = new OrderedDictionary();
    this -> estadias = new OrderedDictionary();
}

Huesped::Huesped(DTHuesped nuevo_huesped):Usuario(nuevo_huesped.get_nombre(), nuevo_huesped.get_email(),nuevo_huesped.get_contrasena()){
    this -> es_tecno = nuevo_huesped.get_es_tecno();
     this -> reservas_grupales = new OrderedDictionary();
    this -> reservas_individuales = new OrderedDictionary();
    this -> estadias = new OrderedDictionary();
}

bool Huesped::get_es_tecno(){
    return this -> es_tecno;
}
OrderedDictionary* Huesped::get_reservas_individuales(){
    return dynamic_cast<OrderedDictionary*>(reservas_individuales);
}
OrderedDictionary* Huesped::get_reservas_grupales(){
    return dynamic_cast<OrderedDictionary*>(reservas_grupales);
}

DTHuesped Huesped::get_DT(){
    return DTHuesped(this -> get_nombre(), this -> get_email(), this -> get_contrasena(), this -> get_es_tecno());
}

void Huesped::asignar_reserva(ReservaGrupal* rg){
    IKey* ik_rg = new Integer(rg -> get_codigo());
    this -> reservas_grupales -> add(ik_rg,rg);
}

void Huesped::asignar_reserva(ReservaIndividual* ri){
    IKey* ik_ri = new Integer(ri -> get_codigo());
    this -> reservas_individuales -> add(ik_ri,ri);
}
void Huesped::alta_estadia(Huesped* ptr_huesped,int codigo_reserva){
    IKey* Ik_reserva = new Integer(codigo_reserva);
    if(reservas_individuales -> member(Ik_reserva)){
        ReservaIndividual* ri = static_cast<ReservaIndividual*>(reservas_individuales -> find(Ik_reserva));
        ri ->alta_estadia(ptr_huesped);
    }else if(reservas_grupales -> member(Ik_reserva)){
        ReservaGrupal* rg = static_cast<ReservaGrupal*>(reservas_grupales -> find(Ik_reserva));
        rg ->alta_estadia(ptr_huesped);
    }
}
void Huesped::asignar_estadia_usuario(Estadia* ptr_estadia){
    IKey* ik_estadia = new Integer(ptr_estadia -> get_codigo());
    this -> estadias -> add(ik_estadia,ptr_estadia);
}
#endif // HUESPED_CPP_