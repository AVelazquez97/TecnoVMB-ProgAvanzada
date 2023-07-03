#ifndef HUESPED_CPP_
#define HUESPED_CPP_
#include "../headers/Huesped.h"
#include "../../datatypes/headers/DTEstadia.h"
#include "../../datatypes/headers/DTReview.h"
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
void Huesped::alta_estadia(Huesped* ptr_huesped, int codigo_reserva){
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
int Huesped::existe_estadia_activa(string nombre_hostal){
    IIterator* it = estadias -> getIterator();
    while(it -> hasCurrent()){
        Estadia* ptr_estadia = dynamic_cast<Estadia*>(it -> getCurrent());
        auto ocupada_checkout = chrono::system_clock::to_time_t(ptr_estadia -> get_checkout_chrono());
        if(ptr_estadia -> get_checkout_chrono().time_since_epoch() == decltype(ptr_estadia -> get_checkout_chrono())::duration::zero()){
            if(ptr_estadia-> perteneceA(nombre_hostal)){
                return ptr_estadia -> get_codigo();
            }
            
        }
    }
}
void Huesped::existe_estadia_activa(int codigo_estadia){
    IKey* ik_estadia = new Integer(codigo_estadia);   
    Estadia* ptr_estadia = dynamic_cast<Estadia*>(estadias -> find(ik_estadia));
    ptr_estadia -> finalizar();
}
OrderedDictionary* Huesped::estadia_fin(string nombre_hostal){
    OrderedDictionary* estadias_a_devolver = new OrderedDictionary();
    for(IIterator* it = estadias -> getIterator(); it -> hasCurrent(); it -> next()){
        Estadia* estadia = dynamic_cast<Estadia*>(it -> getCurrent());
        if(estadia -> finalizo(nombre_hostal)){
            IKey* ik_estadia = new Integer(estadia -> get_codigo());
            DTEstadia* DT_Estadia = new DTEstadia(estadia -> get_codigo(),estadia -> get_checkin(),estadia -> get_email());
            estadias_a_devolver -> add(ik_estadia,DT_Estadia);
        }
    }
    return estadias_a_devolver;
}
void Huesped::calificarHostal(Hostal* ptr_hostal,int codigo_estadia,string comentario, int calificacion){
    IKey* ik_estadia = new Integer(codigo_estadia);
    Estadia* ptr_estadia = dynamic_cast<Estadia*>(estadias -> find(ik_estadia));
    ptr_estadia -> agregarCalificacion(ptr_hostal,comentario,calificacion);
}
OrderedDictionary* Huesped::listar_comentarios_sin_resp(string nombre_hostal){
    OrderedDictionary* reviews_a_devolver = new OrderedDictionary();
    for(IIterator* it = estadias->getIterator(); it -> hasCurrent(); it -> next()){
        Estadia* estadia = dynamic_cast<Estadia*>(it -> getCurrent());
        if(estadia -> get_ptr_habitacion() -> pertenece_a_hostal(nombre_hostal)){
            if(estadia -> get_review() != NULL){
                DTReview* review = new DTReview(estadia->get_review_sin_responder() -> get_DT());
                IKey* Ik_review = new Integer(review ->get_codigo());
                reviews_a_devolver->add(Ik_review,review);
            }
        }
    }
    return reviews_a_devolver;
}
#endif // HUESPED_CPP_