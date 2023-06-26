#ifndef FABRICA_H
#define FABRICA_H
#include "../iControlador/IControlador.h"
#include "../controlador/Controlador.h"

class Fabrica {
	public:
		Fabrica();
		~Fabrica();
		IControlador* getInterface();
	private:
};

#endif