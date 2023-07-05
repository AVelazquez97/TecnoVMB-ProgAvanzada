#ifndef ESTADIA_H_
#define ESTADIA_H_
#include <chrono>
#include <iostream>

#include "../../ICollection/interfaces/ICollectible.h"
#include "../../enums/EnumEstado.h"
#include "../../datatypes/headers/DTReview.h"
#include "Habitacion.h"
#include "Huesped.h"
#include "Review.h"

using namespace std;

class Estadia: public ICollectible{
    private:
        int codigo;
        chrono::system_clock::time_point checkin;
        chrono::system_clock::time_point checkout;
        Habitacion* ptr_habitacion;
        Huesped* ptr_huesped;
        string promo;
        Review* ptr_review;
        //FALTA REVIEW
    public:
        Estadia();
        Estadia(int codigo, tm* checkin, Habitacion* habitacion, Huesped* huesped);
        void set_checkin(tm* checkin);
        void set_checkout(tm* checkout);
        int get_codigo();
        tm* get_checkin();
        tm* get_checkout();
        Habitacion* get_ptr_habitacion(); 
        string get_email();
        chrono::system_clock::time_point get_checkout_chrono();
        chrono::system_clock::time_point get_checkin_chrono();
        bool perteneceA(string nombre_hostal);
        void finalizar();
        void finalizar(tm* checkout);
        bool finalizo(string nombre_hostal);
        void agregarCalificacion(Hostal* ptr_hostal,string comentario,int calificacion);
        void agregarCalificacion(Hostal* ptr_hostal,string comentario,int calificacion,tm* fecha);
        bool tenes_review();
        DTReview darDTReview();
        Review* get_review();
        Review* get_review_sin_responder();
        bool coincide(int codigo_review);
        void alta_respuesta(Empleado* ptr_empleado,string respuesta);
        void alta_respuesta(Empleado* ptr_empleado,string respuesta, tm* fecha);
        bool no_finalizo();
        bool no_finalizo(string email);
};

#endif // ESTADIA_H_