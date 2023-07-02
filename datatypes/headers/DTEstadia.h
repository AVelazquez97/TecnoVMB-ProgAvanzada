#ifndef DTESTADIA_H_
#define DTESTADIA_H_
#include <chrono>
#include <iostream>

#include "../../ICollection/interfaces/ICollectible.h"
#include "../../enums/EnumEstado.h"


using namespace std;

class DTEstadia: public ICollectible{
    private:
        int codigo;
        chrono::system_clock::time_point checkin;
        chrono::system_clock::time_point checkout;
        string email;
        string promo;
    public:
        DTEstadia();
        DTEstadia(int codigo, tm* checkin, string email);
        void set_checkin(tm* checkin);
        void set_checkout(tm* checkout);
        int get_codigo();
        tm* get_checkin();
        tm* get_checkout();
        string get_email();
        string get_promo();
        chrono::system_clock::time_point get_checkout_chrono();
        friend ostream& operator << (ostream& salida, DTEstadia estadia);
};

#endif // DTESTADIA_H_