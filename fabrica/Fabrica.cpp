#include "Fabrica.h"

Fabrica::Fabrica() {

}

Fabrica::~Fabrica() {

}

/// @brief Implementación del patrón Factory
/// @return retorna la instancia del controlador. La cual es única y global
IControlador* Fabrica::getInterface() {
    return Controlador::getInstance();
}