#ifndef DTREVIEW_CPP_
#define DTREVIEW_CPP_
#include "../headers/DTReview.h"
DTReview::DTReview(){}

DTReview::DTReview(int codigo, tm* fecha, int calificacion, string comentario){
    this -> codigo = codigo;
    
    tm fecha_tm = *fecha;
    time_t fecha_time = mktime(&fecha_tm);
    this -> fecha = chrono::system_clock::from_time_t(fecha_time);

    this -> calificacion = calificacion;
    this -> comentario = comentario;
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

#endif // DTREVIEW_CPP_