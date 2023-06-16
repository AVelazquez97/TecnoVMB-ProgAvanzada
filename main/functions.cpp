using namespace std;
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <cstring>

#include "functions.h"

#include "../iControlador/IControlador.h"
#include "../fabrica/Fabrica.h"

/*
    Tanto si la fabrica se utiliza acá como en el fichero de funciones se debería utilizar de la siguiente manera:
    Fabrica fab;
    IControlador* controlador = fab.getInterface();
    controlador->operacion
*/

Fabrica fab;
IControlador* controlador = fab.getInterface();

void mostrar_menu_principal() {
	cout << "╔════════════════╗\n";
	cout << "║ Menú principal ║\n";
	cout << "╚════════════════╝\n";
	cout << "  1. Alta usuario\n";
	cout << "  2. Alta hostal\n";
	cout << "  3. Alta habitacion\n";
	cout << "  4. Asignar empleado a hostal\n";
	cout << "  5. Realizar reserva\n";
	cout << "  6. Consultar top 3 de hostales\n";
	cout << "  7. Registrar estadia\n";
	cout << "  8. Finalizar estadia\n";
	cout << "  9. Calificar estadia\n";
	cout << "  10. Comentar calificacion\n";
	cout << "  11. Consulta de usuario\n";
	cout << "  12. Consulta de hostal\n";
	cout << "  13. Consulta de reserva\n";
	cout << "  14. Consulta de estadia\n";
	cout << "  15. Baja de reserva\n";
	cout << "  16. Modificar fecha del sistema\n";
	cout << "  17. Cargar de Datos de Prueba\n";
	cout << "  18. Salir\n";
}

int eleccion_menu_principal() {
	/* 
	Para evitar que el menu entre en bucle cuando el usuario ingrese
	una cadena de texto donde deberia ir un int se toman las siguientes medidas.

	Se crea una 'cadena_inicio' que contiene como base un texto que al ser
	convertido con stoi() da como resultado el valor entero 0.

	La explicacion viene de que cuando agregemos la entrada del usuario,
	si el mismo ingresase solo texto, la funcion stoi() devolveria un
	error, con esto implementado si el usuario ingresa un valor no valido
	se leera siempre el 0 como opcion default
	*/
	string cadena_inicio = "0";
	string cadena_agregada = "";

	mostrar_menu_principal();
	do{
	cout << ("Ingresa una opción(1..18): ");
	cin >> cadena_agregada;

	if (stoi(cadena_inicio + cadena_agregada) < 1 || stoi(cadena_inicio + cadena_agregada) > 18){
		cout << "La opción que has ingresado no es válida. Inténtalo otra vez.\n";
	}
	}

	while(stoi(cadena_inicio + cadena_agregada) < 1 || stoi(cadena_inicio + cadena_agregada) > 18);

	return stoi(cadena_inicio + cadena_agregada);
}

void alta_usuario(){
	bool existe_email = true;
	bool cancelar = false;
	bool continuar = true;
	string entrada;

	while(existe_email && continuar){
		cout << "Ingrese un email o ingrese 'salir' para volver al menu principal: " << endl;
		cin >> entrada;
		existe_email = controlador -> verificar_email(entrada);
		if(entrada == "salir"){continuar = false;}
	}
}