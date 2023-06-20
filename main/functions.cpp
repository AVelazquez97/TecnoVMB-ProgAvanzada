using namespace std;
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <cstring>

/*datatypes*/
#include "../datatypes/headers/DTHuesped.h"
#include "../datatypes/headers/DTEmpleado.h"

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

/*esta funcion va hasta el controlador
trae los DTHostales y los imprime, sirve tenerla como
funcion ya que se pide en distintas operaciones*/
void obtener_hostales(){
	OrderedDictionary* DTHostales = new OrderedDictionary();
	DTHostales = controlador -> obtener_hostales();

	cout << "| Lista de hostales |" << endl;

	for(IIterator* it = DTHostales -> getIterator(); it -> hasCurrent(); it -> next()){
        DTHostal* hostal = dynamic_cast<DTHostal*>(it -> getCurrent());
        cout << hostal->get_nombre() << "|" <<
		hostal -> get_direccion() << "|" <<
		hostal -> get_telefono() << "|" << endl;
    }
}

void alta_usuario(){
	bool existe_email = true;
	bool cancelar = false;
	bool es_tecno;
	string entrada = "";
	string email;
	string nombre;
	string contrasena;
	string tipo = "";
	Cargo cargo;
	/*el unico proposito de esta variable es guardar
	en ella lo que sea que traiga el buffer asi nos evitamos que se salte
	pedir por el nombre*/
	string limpiar_buffer; 
	getline(cin,limpiar_buffer);

	cout << "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." << endl;
	
	cout << "Ingrese el nombre: " << endl;
	getline(cin,nombre);
	if(nombre == "salir"){return;} /* en caso de que desee salir*/

	while(existe_email){
		cout << "Ingrese el email: " << endl;
		getline(cin,email);
		if(email == "salir"){return;} /* en caso de que desee salir*/
		existe_email = controlador -> verificar_email(email); //! manejar una excepcion aca
	}

	cout << "Ingrese la contraseña: " << endl;
	getline(cin,contrasena);
	if(contrasena == "salir"){return;} /* en caso de que desee salir*/

	while(tipo != "0" && tipo != "1"){
	cout << "Ingrese el tipo de usuario que quiere registrar: 0 = Huesped | 1 = Empleado" << endl;
	getline(cin,tipo);
	if(tipo == "salir"){return;} /* en caso de que desee salir*/
	}

	if(tipo == "0"){
		while(entrada != "0" && entrada != "1"){
			cout << "El Huesped es Tecno?: 0 = No | 1 = Si" << endl;
			getline(cin,entrada);
			if(entrada == "salir"){return;} /* en caso de que desee salir*/
				if(entrada == "0"){
					es_tecno = false;
				}else{
					es_tecno = true;
				}
		}
		/*hacer la llamada al sistema con el DTHuesped*/
		DTHuesped nuevo_huesped(nombre, email, contrasena, es_tecno);
		controlador -> alta_huesped(nuevo_huesped);
	}else{
		while(entrada != "0" && entrada != "1" && entrada != "2" && entrada != "3"){
		cout << "Indique el cargo del empleado: 0 = Administracion | 1 = Limpieza | 2 = Recepcion | 3 = Infraestructura " << endl;
		getline(cin,entrada);
		if(entrada == "salir"){return;} /* en caso de que desee salir*/
		}
			switch(stoi(entrada)){
				case 0:{
					cargo = Cargo::Administracion;
					break;
				}
				case 1:{
					cargo = Cargo::Limpieza;
					break;
				}
				case 2:{
					cargo = Cargo::Recepcion;
					break;
				}
				case 3:{
					cargo = Cargo::Infraestructura;
					break;
				}
			}
		/*hacer la llamada al sistema con el DTEmpleado*/
		DTEmpleado nuevo_empleado(nombre, email, contrasena, cargo);
		controlador -> alta_empleado(nuevo_empleado);
	}
}

void alta_hostal(){
	string nombre;
	string direccion; 
	string telefono;
	bool existe_hostal;
	string limpiar_buffer; 
	getline(cin,limpiar_buffer);

	cout << "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." << endl;
	
	cout << "Ingrese el nombre: " << endl;
	getline(cin,nombre);
	if(nombre == "salir"){return;} /* en caso de que desee salir*/
	
	/*
	si existe el hostal => tira excepcion
	si no existe hostal => no tira excepcion
	*/
	try{
		controlador -> existe_hostal(nombre);

		cout << "Ingrese la direccion: " << endl;
		getline(cin,direccion);
		if(direccion == "salir"){return;} /* en caso de que desee salir*/

		cout << "Ingrese el telefono: " << endl;
		getline(cin,telefono);
		if(telefono == "salir"){return;} /* en caso de que desee salir*/

		DTHostal nuevo_hostal(nombre,direccion,telefono);
		controlador -> alta_hostal(nuevo_hostal);

	}catch(invalid_argument const& Excepcion){
		cout << endl << "ERROR:" << Excepcion.what() << endl;
	}
	
}

void alta_habitacion(){
	obtener_hostales();
}

void asignar_empleado_hostal(){

}

void realizar_reserva(){

}

void consultar_top_3(){

}

void registrar_estadia(){

}

void finalizar_estadia(){

}

void comentar_calificacion(){

}

void consulta_usuario(){

}

void consulta_hostal(){

}

void consulta_reserva(){

}

void consulta_estadia(){

}

void baja_reserva(){
	
}

void modificar_fecha(){

}

void datos_prueba(){
	/*empleados*/
	controlador -> alta_empleado(DTEmpleado("Emilia","emilia@mail.com","123",Recepcion));
	controlador -> alta_empleado(DTEmpleado("Leonardo","leo@mail.com","123",Recepcion));
	controlador -> alta_empleado(DTEmpleado("Alina","alina@mail.com","123",Administracion));
	controlador -> alta_empleado(DTEmpleado("Barliman","barli@mail.com","123",Recepcion));
	/*huespedes*/
	controlador -> alta_huesped(DTHuesped("Sofia","sofia@mail.com","123",true));
	controlador -> alta_huesped(DTHuesped("Frodo","frodo@mail.com","123",true));
	controlador -> alta_huesped(DTHuesped("Sam","sam@mail.com","123",false));
	controlador -> alta_huesped(DTHuesped("Merry","merry@mail.com","123",false));
	controlador -> alta_huesped(DTHuesped("Pippin","pippin@mail.com","123",false));
	controlador -> alta_huesped(DTHuesped("Seba","seba@mail.com","123",true));
	/*Hostales*/
	controlador -> alta_hostal(DTHostal("La posada del finger","Av de la playa 123,Maldonado","099111111"));
	controlador -> alta_hostal(DTHostal("Mochileros","Rambla Costanera 333,Rocha","42579512"));
	controlador -> alta_hostal(DTHostal("El Pony Pisador","Bree (preguntar por Gandalf)","000"));
	controlador -> alta_hostal(DTHostal("Altos del FIng","Av del Toro 1424","099892992"));
	controlador -> alta_hostal(DTHostal("Caverna Lujosa","Amaya 2515","233233235"));
}

