#ifndef DTHABITACION_H_
#define DTHABITACION_H_

class DTHabitacion{
    private:
        int numero;
        float precio;
        int capacidad;
        string pertenece; //el nombre del hostal al que pertenece
    public:
        DTHabitacion();
        DTHabitacion(int numero, float precio, int capacidad, Hostal pertenece);
        int get_numero();
        float get_precio();
        int get_capacidad();
        string get_pertenece();
};


#endif // DTHABITACION_H_