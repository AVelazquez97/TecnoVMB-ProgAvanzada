#include "Controlador.h"
#include <iostream>
#include <stdlib.h>
using namespace std;


Controlador *Controlador::instance = nullptr;

Controlador::~Controlador() {
}

Controlador::Controlador() {
}

/// @brief implementación del singleton.
/// Si la clase aún no se ha instanciado, se instancia por primera vez.
/// @return siempre retorna la misma instancia del controlador 
Controlador *Controlador::getInstance() {
    if (instance == nullptr) {
        instance = new Controlador();
    }
    return instance;
}

time_t *Controlador::getFechaSistema() {
    return &this->fecha_sistema;
}

void Controlador::setFechaSistema(tm* fecha) {
    this->fecha_sistema = time(NULL);
    this->fecha_sistema = mktime(fecha);
}