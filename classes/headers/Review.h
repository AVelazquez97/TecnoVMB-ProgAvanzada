#ifndef REVIEW_H_
#define REVIEW_H_
#include "../../ICollection/collections/OrderedDictionary.h"
#include "../../datatypes/headers/DTReview.h"
#include "Hostal.h"
#include "Respuesta.h"
#include <iostream>
#include <chrono>
using namespace std;

class Review: public ICollectible{
    private:
        int codigo;
        chrono::system_clock::time_point fecha;
        int calificacion;
        string comentario;
        Hostal* ptr_hostal;
        Respuesta* respuesta;
    public:
        Review();
        Review(int codigo, tm* fecha, int calificacion,string comentario,Hostal* ptr_hostal);
        int get_codigo();
        tm* get_fecha();
        int get_calificacion();
        string get_comentario();
        Hostal* get_ptr_hostal();
        DTReview get_DT();
        void destruir_review_respuesta();
        Respuesta* get_ptr_respuesta();
        bool get_sin_responder();
};


#endif // REVIEW_H_