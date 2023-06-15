#ifndef USUARIO_CPP_
#define USUARIO_CPP_
#include "../headers/Usuario.h"

void Usuario::set_nombre(string nombre){
    this -> nombre = nombre;
}

void Usuario::set_email(string email){
    this -> email = email;
}

void Usuario::set_password(string password){
    this -> password = password;
}

string Usuario::get_email(){
    return this -> email;
}

string Usuario::get_nombre(){
    return this -> nombre;
}

string Usuario::get_password(){
    return this -> password;
}

#endif // USUARIO_CPP_