#ifndef DTREVIEW_CPP_
#define DTREVIEW_CPP_
#include "../headers/DTReview.h"
#include "../../classes/headers/Review.h"
#include <iomanip>
DTReview::DTReview(){}

DTReview::DTReview(int codigo, tm* fecha, int calificacion, string comentario){
    this -> codigo = codigo;
    
    tm fecha_tm = *fecha;
    time_t fecha_time = mktime(&fecha_tm);
    this -> fecha = chrono::system_clock::from_time_t(fecha_time);

    this -> calificacion = calificacion;
    this -> comentario = comentario;
}
DTReview::DTReview(Review* review){
    this -> codigo = review ->get_codigo();
    
    tm fecha_tm = *review -> get_fecha();
    time_t fecha_time = mktime(&fecha_tm);
    this -> fecha = chrono::system_clock::from_time_t(fecha_time);

    this -> calificacion = review-> get_calificacion();
    this -> comentario = review -> get_comentario();
}
int DTReview::get_codigo(){
    return this -> codigo;
}

tm* DTReview::get_fecha(){
    time_t fecha = chrono::system_clock::to_time_t(this->fecha);
    tm* fecha_tm = localtime(&fecha);
    return fecha_tm;
}
int DTReview::get_calificacion(){
    return this -> calificacion;
}
string DTReview::get_comentario(){
    return this -> comentario;
}
ostream& operator << (ostream& salida, DTReview review){
    salida << "| Codigo: " << review.get_codigo() << " |" << endl 
        << "| Fecha: " << put_time(review.get_fecha(), "%d/%m/%y - %H") << " hs" << " |" << endl 
        << "| Comentario: " << review.get_comentario() << " hs" << " |" << endl<< "| Calificacion: " 
        << review.get_calificacion() << " |" << endl  << endl;

    return salida;
}
#endif // DTREVIEW_CPP_