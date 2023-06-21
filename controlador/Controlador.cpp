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
}

void Controlador::alta_empleado(DTEmpleado nuevo_empleado){
    string email = nuevo_empleado.get_email();
    char parce_char[email.length()+1];
    strcpy(parce_char,email.c_str());

    IKey* ik = new String(parce_char);
    Empleado* empleado = new Empleado(nuevo_empleado);
    this -> empleados -> add(ik,empleado);
}

void Controlador::alta_hostal(DTHostal nuevo_hostal){
    string nombre = nuevo_hostal.get_nombre();
    char parce_char[nombre.length()+1];
    strcpy(parce_char,nombre.c_str());

    IKey* ik = new String(parce_char);
    Hostal* hostal = new Hostal(nuevo_hostal);
    this -> hostales -> add(ik,hostal);
}

void Controlador::alta_habitacion(DTHabitacion nueva_habitacion, string nombre_hostal){
    char parce_char[nombre_hostal.length()+1];
    strcpy(parce_char,nombre_hostal.c_str());

    IKey* ik = new String(parce_char);

    Hostal* ptr_hostal = dynamic_cast<Hostal*>(hostales -> find(ik));

    ptr_hostal -> alta_habitacion(nueva_habitacion,ptr_hostal);
}

/* auxiliares*/

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

void Controlador::no_existe_hostal(string nombre){
    char parce_char[nombre.length()+1];
    strcpy(parce_char,nombre.c_str());

    IKey* ik = new String(parce_char);
    
    if(!(this -> hostales -> member(ik))){
        throw invalid_argument("Hostal no existente!");
    }
}

OrderedDictionary* Controlador::obtener_hostales(){
    //por cada iteracion, paso el obj Hostal a DTHostal,
    //lo agrego a la lista y lo devuelvo

    //lista que voy a devolver con los hostales pasados a dt
    OrderedDictionary* DTHostales = new OrderedDictionary(); 

    //1. ciclar en la lista de hostales
    for(IIterator* it = hostales -> getIterator(); it -> hasCurrent(); it -> next()){
        Hostal* hostal = dynamic_cast<Hostal*>(it -> getCurrent());
        
        string cadena = hostal -> get_nombre();
        char parce_char[cadena.length()+1];
        strcpy(parce_char,cadena.c_str());

        IKey* ik = new String(parce_char);

        //2. convertirlo a dt
        DTHostal* hostal_singular = new DTHostal(hostal -> get_DT());

        //3. agregarlo a la lista
        DTHostales -> add(ik, hostal_singular);
    }

    /*
    ¿tendria que hacerle el delete a cada hostal_singular?
    en caso de hacerlo, no pierdo esa informacion de la lista tambien?
    */
   
    //4. devolver la lista
    return DTHostales;
}

OrderedDictionary* Controlador::obtener_no_empleados_hostal(string nombre_hostal){

    OrderedDictionary* DTEmpleados = new OrderedDictionary(); 

    for(IIterator* it = empleados -> getIterator(); it -> hasCurrent(); it -> next()){
        Empleado* empleado = dynamic_cast<Empleado*>(it -> getCurrent());
        
        /*falta comprobar que los empleados no trabajen en el hostal
        de nombre hostal*/
       

        string cadena = empleado -> get_email();
        char parce_char[cadena.length()+1];
         cout << "1" << endl;
        
        strcpy(parce_char,cadena.c_str());
        cout << "2" << endl;
        IKey* ik = new String(parce_char);
        cout << "3" << endl;
        //2. convertirlo a dt
        DTEmpleado* empleado_singular = new DTEmpleado(empleado -> get_DT()); //estamos teniendo un error en esta linea
        cout << "4" << endl;
        //3. agregarlo a la lista
        DTEmpleados -> add(ik, empleado_singular);
        cout << "5" << endl;
    }

    return DTEmpleados;
}