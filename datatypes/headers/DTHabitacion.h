#ifndef DTHABITACION_H_
#define DTHABITACION_H_

class DTHabitacion{
    private:
        int numero;
        float precio;
        int capacidad;
    public:
        DTHabitacion();
        DTHabitacion(int numero, float precio, int capacidad);
        int get_numero();
        float get_precio();
        int get_capacidad();
};


#endif // DTHABITACION_H_