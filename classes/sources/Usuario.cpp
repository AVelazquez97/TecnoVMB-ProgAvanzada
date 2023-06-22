#ifndef USUARIO_CPP_
#define USUARIO_CPP_
#include "../headers/Usuario.h"

Usuario::Usuario(){

}

Usuario::Usuario(string nombre, string email, string contrasena){
    this -> nombre = nombre;
    this -> email = email;
    this -> contrasena = contrasena;
}

void Usuario::set_nombre(string nombre){
    this -> nombre = nombre;
}

void Usuario::set_email(string email){
    this -> email = email;
}

void Usuario::set_contrasena(string contrasena){

    this -> contrasena = contrasena;
}

string Usuario::get_email(){
    
    return this -> email;
}

string Usuario::get_nombre(){
    
    return this -> nombre;
}

string Usuario::get_contrasena(){
    
    return this -> contrasena;
}

#endif // USUARIO_CPP_