#ifndef DTHUESPED_H_
#define DTHUESPED_H_
#include <iostream>
using namespace std;

class DTHuesped{
    private:
        string nombre;
        string email;
        string contrasena;
        bool es_tecno;
    public:
        DTHuesped();
        DTHuesped(string nombre, string email, string contrasena, bool es_tecno);
        string get_nombre();
        string get_email();
        string get_contrasena();
        bool get_es_tecno();
};


#endif // DTHUESPED_H_