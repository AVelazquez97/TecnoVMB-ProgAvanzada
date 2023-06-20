#include "Controlador.h"
#include "../ICollection/String.h"
#include <iostream>
#include <stdlib.h>
using namespace std;


Controlador *Controlador::instance = nullptr;

Controlador::~Controlador() {
}

Controlador::Controlador() {
    this -> hostales = new OrderedDictionary();
    this -> huespedes = new OrderedDictionary();
    this -> empleados = new OrderedDictionary();
    this -> fecha_sistema = time(0); //!inicializar la fecha del sistema
}

/// @brief implementación del singleton.
/// Si la clase aún no se ha instanciado, se instancia por primera vez.
/// @return siempre retorna la misma instancia del controlador 
Controlador *Controlador::getInstance() {
    if (instance == nullptr) {
        instance = new Controlador();
    }
    return instance;
}

//para imprimir la fecha del sistema hay que pasarla a string
time_t *Controlador::getFechaSistema() {
    return &this->fecha_sistema;
}

void Controlador::setFechaSistema(tm* fecha) {
    this->fecha_sistema = time(NULL);
    this->fecha_sistema = mktime(fecha);
}

void Controlador::alta_huesped(DTHuesped nuevo_huesped){
    string email = nuevo_huesped.get_email();
    char parce_char[email.length()+1];
    strcpy(parce_char,email.c_str());

    IKey* ik = new String(parce_char);
    Huesped* huesped = new Huesped(nuevo_huesped);
    this -> huespedes -> add(ik,huesped);

    cout << "Huesped ingresado correctamente!" << endl;
}

void Controlador::alta_empleado(DTEmpleado nuevo_empleado){
    string email = nuevo_empleado.get_email();
    char parce_char[email.length()+1];
    strcpy(parce_char,email.c_str());

    IKey* ik = new String(parce_char);
    Empleado* empleado = new Empleado(nuevo_empleado);
    this -> empleados -> add(ik,empleado);

    cout << "Empleado ingresado correctamente!" << endl;
}

void Controlador::alta_hostal(DTHostal nuevo_hostal){
    string nombre = nuevo_hostal.get_nombre();
    char parce_char[nombre.length()+1];
    strcpy(parce_char,nombre.c_str());

    IKey* ik = new String(parce_char);
    Hostal* hostal = new Hostal(nuevo_hostal);
    this -> hostales -> add(ik,hostal);

    cout << "Hostal ingresado correctamente!" << endl;
}

bool Controlador::verificar_email(string entrada){

    /*
    parceamos la entrada de string a un array de caracteres
    porque es lo que recibe como parametro la String que proporciona
    ICollections.
    */

    char parce_char[entrada.length()+1];
    strcpy(parce_char,entrada.c_str());

    IKey* ik = new String(parce_char);
    
    if(this -> huespedes -> member(ik)){
        return true;
    }else if(this -> empleados -> member(ik)){
        return true;
    }else{
        return false;
    }

}

void Controlador::existe_hostal(string nombre){
    char parce_char[nombre.length()+1];
    strcpy(parce_char,nombre.c_str());

    IKey* ik = new String(parce_char);
    
    if(this -> hostales -> member(ik)){
        throw invalid_argument("Hostal ya existente!");
    }
}