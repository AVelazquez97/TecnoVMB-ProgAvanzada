#ifndef USUARIO_H_
#define USUARIO_H_

#include "../../ICollection/interfaces/ICollectible.h"
#include<iostream>
using namespace std;

class Usuario: public ICollectible{
    protected:
        string nombre;
        string email;
        string contrasena;
    public:
        Usuario();
        Usuario(string nombre, string email, string contrasena);
        void set_nombre(string nombre);
        void set_email(string email);
        void set_contrasena(string contrasena);
        string get_nombre();
        string get_email();
        string get_contrasena();
};

#endif // USUARIO_H_