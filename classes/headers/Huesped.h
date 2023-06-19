#ifndef HUESPED_H_
#define HUESPED_H_
#include "Usuario.h"
#include "../../datatypes/headers/DTHuesped.h"

class Huesped: public Usuario{
    private:
        bool es_tecno;
    public:
        Huesped();
        Huesped(string nombre, string email, string contrasena, bool es_tecno);
        Huesped(DTHuesped nuevo_huesped);
        bool get_es_tecno();
        DTHuesped get_DT();
};


#endif // HUESPED_H_