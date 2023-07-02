#ifndef DTESTADIA_CPP_
#define DTESTADIA_CPP_
#include "../headers/DTEstadia.h"

#include <iomanip>

DTEstadia::DTEstadia(){}


DTEstadia::DTEstadia(int codigo, tm* checkin, string email){
    this -> codigo = codigo;
   
    tm checkin_tm = *checkin;
    time_t checkin_time = mktime(&checkin_tm);
    this -> checkin = chrono::system_clock::from_time_t(checkin_time);

    this -> email = email;
    this -> promo = " ";
}

void DTEstadia::set_checkin(tm* checkin){
    tm checkin_tm = *checkin;
    time_t checkin_time = mktime(&checkin_tm);
    this -> checkin = chrono::system_clock::from_time_t(checkin_time);
}

void DTEstadia::set_checkout(tm* checkout){
    tm checkout_tm = *checkout;
    time_t checkout_time = mktime(&checkout_tm);
    this -> checkout = chrono::system_clock::from_time_t(checkout_time);
}

int DTEstadia::get_codigo(){
    return this -> codigo;
}

tm* DTEstadia::get_checkin(){
    time_t checkin = chrono::system_clock::to_time_t(this->checkin);
    tm* checkin_tm = localtime(&checkin);
    return checkin_tm;
}

tm* DTEstadia::get_checkout(){
    time_t checkout = chrono::system_clock::to_time_t(this->checkout);
    tm* checkout_tm = localtime(&checkout);
    return checkout_tm;
}
chrono::system_clock::time_point DTEstadia::get_checkout_chrono(){
    return this -> checkout;
}
string DTEstadia::get_email(){
    return this-> email;
}
string DTEstadia::get_promo(){
    return this-> promo;
}
ostream& operator << (ostream& salida, DTEstadia estadia){
    salida << "| Codigo: " << estadia.get_codigo() << " |" << endl 
        << "| Chekin: " << put_time(estadia.get_checkin(), "%d/%m/%y - %H") << " hs" << " |" << endl 
        << "| Checkout: " << put_time(estadia.get_checkout(), "%d/%m/%y - %H") << " hs" << " |" << endl<< "| Empleado: " 
        << estadia.get_email() << " |" <<endl <<"|" <<"promo:"<<estadia.get_promo() << endl << endl;

    return salida;
}
#endif // ESTADIA_CPP_