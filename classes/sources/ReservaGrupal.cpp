#ifndef RESERVAGRUPAL_CPP_
#define RESERVAGRUPAL_CPP_
#include "../headers/ReservaGrupal.h"
#include "../headers/Habitacion.h"
#include "../headers/Huesped.h"
#include "string.h"

ReservaGrupal::ReservaGrupal(){
    this -> huespedes = new OrderedDictionary();
}

ReservaGrupal::ReservaGrupal(
    int codigo,
    tm* checkin,
    tm* checkout, 
    Estado estado_reserva, 
    Habitacion* ptr_habitacion, 
    OrderedDictionary* huespedes_encontrados
):Reserva(codigo, checkin, checkout, estado_reserva, ptr_habitacion){
    int contador_finger = 0;

    std::chrono::duration<float, std::ratio<86400>> diff = Reserva::get_checkout_chrono() - Reserva::get_checkin_chrono();
    cout<<"huespedes_encontrado:" << huespedes_encontrados -> getSize()<< "diff cout"<< diff.count() << endl;
    getchar();
    this -> costo = ptr_habitacion ->get_precio() * diff.count() * huespedes_encontrados -> getSize();

    this -> huespedes = new OrderedDictionary();
    for(IIterator* it = huespedes_encontrados -> getIterator(); it -> hasCurrent(); it -> next()){
        /*por cada huesped*/
        Huesped* huesped = dynamic_cast<Huesped*>(it -> getCurrent());

        if(huesped ->get_es_tecno()){
            contador_finger += 1;
        }
        
        char parce_email_huesped[huesped -> get_email().length()+1];
        strcpy(parce_email_huesped,huesped -> get_email().c_str());
        /*le creo una ikey*/
        IKey* ik_email_huesped = new String(parce_email_huesped);
        /*lo añado a la lista de huespedes que tiene esta reserva*/
        this -> huespedes -> add(ik_email_huesped,huesped);
        
        /*le agrego al huesped esta reserva*/
        huesped -> asignar_reserva(this);
    }
    
    this -> cantidad_huespedes = huespedes -> getSize();
}

ReservaGrupal::ReservaGrupal(
    int codigo,
    tm* checkin,
    tm* checkout, 
    Estado estado_reserva, 
    Habitacion* ptr_habitacion, 
    OrderedDictionary* huespedes_encontrados,
    bool tipo
):Reserva(codigo, checkin, checkout, estado_reserva, ptr_habitacion,tipo){
    this -> huespedes = new OrderedDictionary();
    int contador_finger = 0;
    std::chrono::duration<float, std::ratio<86400>> diff = Reserva::get_checkout_chrono() - Reserva::get_checkin_chrono();
    this -> costo = ptr_habitacion ->get_precio() * diff.count() * huespedes_encontrados -> getSize();

    for(IIterator* it = huespedes_encontrados -> getIterator(); it -> hasCurrent(); it -> next()){

        /*por cada huesped*/
        Huesped* huesped = dynamic_cast<Huesped*>(it -> getCurrent());

        if(huesped ->get_es_tecno()){
            contador_finger += 1;
        }

        char parce_email_huesped[huesped -> get_email().length()+1];
        strcpy(parce_email_huesped,huesped -> get_email().c_str());
        /*le creo una ikey*/
        IKey* ik_email_huesped = new String(parce_email_huesped);
        /*lo añado a la lista de huespedes que tiene esta reserva*/
        this -> huespedes -> add(ik_email_huesped,huesped);
        
        /*le agrego al huesped esta reserva*/
        huesped -> asignar_reserva(this);
    }

    if(contador_finger >= 2){
        this -> costo == costo *0.30;
    }

}

OrderedDictionary* ReservaGrupal::get_huespedes(){
    return dynamic_cast<OrderedDictionary*>(huespedes);
}
float ReservaGrupal::get_costo(){
    return this->costo;
}
#endif // RESERVAGRUPAL_CPP_