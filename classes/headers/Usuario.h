#ifndef USUARIO_H_
#define USUARIO_H_

#include "../../ICollection/interfaces/ICollectible.h"
#include<iostream>
using namespace std;

class Usuario: public ICollectible{
    protected:
        string nombre;
        string email;
        string password;
    public:
        void set_nombre(string nombre);
        void set_email(string email);
        void set_password(string password);
        string get_nombre();
        string get_email();
        string get_password();
};

#endif // USUARIO_H_