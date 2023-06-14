#ifndef FABRICA_H
#define FABRICA_H
#include "../iControlador/IControlador.h"
#include "../controlador/Controlador.h"

#pragma once // En discord, en la sección de documentos, queda explicado esto en el archivo pragma-once.MD

class Fabrica {
	public:
		Fabrica();
		~Fabrica();
		IControlador* getInterface();
	private:
};

#endif