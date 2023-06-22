using namespace std;
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <cstring>
#include <limits>

/*datatypes*/
#include "../datatypes/headers/DTHuesped.h"
#include "../datatypes/headers/DTEmpleado.h"
#include "../enums/EnumCargo.h"

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
	system("clear");
	cout << GREEN "╔════════════════╗" << endl;
	cout << "║ Menú principal ║" << endl;
	cout << "╚════════════════╝" << endl;
	cout << "  1. Alta usuario" << endl;
	cout << "  2. Alta hostal" << endl;
	cout << "  3. Alta habitacion" << endl;
	cout << "  4. Asignar empleado a hostal" << endl;
	cout << "  5. Realizar reserva" << endl;
	cout << "  6. Consultar top 3 de hostales" << endl;
	cout << "  7. Registrar estadia" << endl;
	cout << "  8. Finalizar estadia" << endl;
	cout << "  9. Calificar estadia" << endl;
	cout << "  10. Comentar calificacion" << endl;
	cout << "  11. Consulta de usuario" << endl;
	cout << "  12. Consulta de hostal" << endl;
	cout << "  13. Consulta de reserva" << endl;
	cout << "  14. Consulta de estadia" << endl;
	cout << "  15. Baja de reserva" << endl;
	cout << "  16. Modificar fecha del sistema" << endl;
	cout << "  17. Cargar de Datos de Prueba" << endl;
	cout << "  18. Salir" NC << endl;
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
		cout << GREEN "Ingresa una opción(1..18): " NC;
		cin >> cadena_agregada;

		if (stoi(cadena_inicio + cadena_agregada) < 1 || stoi(cadena_inicio + cadena_agregada) > 18){
			cout << endl << REDB "La opción que has ingresado no es válida. Inténtalo otra vez." NC << endl << endl;
		}
	}
	while(stoi(cadena_inicio + cadena_agregada) < 1 || stoi(cadena_inicio + cadena_agregada) > 18);

	system("clear");
	return stoi(cadena_inicio + cadena_agregada);
}

void press_enter(){
	cout << endl << CYAN "Presiona ENTER para continuar..." NC;
	getchar();
}

/*esta funcion va hasta el controlador
trae los DTHostales y los imprime, sirve tenerla como
funcion ya que se pide en distintas operaciones*/
void obtener_hostales(){
	OrderedDictionary* DTHostales = new OrderedDictionary();
	DTHostales = controlador -> obtener_hostales();

	cout << endl << "| Lista de hostales |" << endl << endl;

	for(IIterator* it = DTHostales -> getIterator(); it -> hasCurrent(); it -> next()){
        DTHostal* hostal = dynamic_cast<DTHostal*>(it -> getCurrent());
        cout << "| " << hostal->get_nombre() << " | " <<
		hostal -> get_direccion() << " | " <<
		hostal -> get_telefono() << " |" << endl << endl;
    }
}

void obtener_no_empleados_hostal(string nombre_hostal){
	OrderedDictionary* DTEmpleados = new OrderedDictionary();
	DTEmpleados = controlador -> obtener_no_empleados_hostal(nombre_hostal);

	cout << endl << "| Lista de no empleados del hostal: " << nombre_hostal << " |" << endl << endl;

	for(IIterator* it = DTEmpleados -> getIterator(); it -> hasCurrent(); it -> next()){
        DTEmpleado* empleado = dynamic_cast<DTEmpleado*>(it -> getCurrent());
        cout << "| " << empleado->get_nombre() << "|" <<
		empleado -> get_email() << "|" << endl << endl;
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

	cout << CYAN "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." NC << endl;
	
	cout << "Ingrese el nombre: " << endl;
	getline(cin,nombre);
	if(nombre == "salir"){return;} /* en caso de que desee salir*/

	while(existe_email){
		cout << "Ingrese el email: " << endl;
		getline(cin,email);
		if(email == "salir"){return;} /* en caso de que desee salir*/
		existe_email = controlador -> verificar_email(email);
		if(existe_email){
			cout << endl << REDB "Ya existe un usuario registrado con ese email. Intenta de nuevo... " NC << endl;
		}
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
		cout << "Huesped ingresado correctamente!" << endl;
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
		cout << "Empleado ingresado correctamente!" << endl;
	}
}

void alta_hostal(){
	string nombre;
	string direccion; 
	string telefono;
	bool existe_hostal;
	string limpiar_buffer; 
	getline(cin,limpiar_buffer);

	cout << CYAN "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." NC << endl;
	
	cout << "Ingrese el nombre del hostal: " << endl;
	getline(cin,nombre);
	if(nombre == "salir"){return;} /* en caso de que desee salir*/
	
	/*
	si existe el hostal => tira excepcion
	si no existe hostal => no tira excepcion
	*/
	try{
		controlador -> existe_hostal(nombre);

		cout << "Ingrese la direccion del hostal: " << endl;
		getline(cin,direccion);
		if(direccion == "salir"){return;} /* en caso de que desee salir*/

		cout << "Ingrese el telefono del hostal: " << endl;
		getline(cin,telefono);
		if(telefono == "salir"){return;} /* en caso de que desee salir*/

		DTHostal nuevo_hostal(nombre,direccion,telefono);
		controlador -> alta_hostal(nuevo_hostal);
		cout << "Hostal ingresado correctamente!" << endl;
	}catch(invalid_argument const& Excepcion){
		cout << endl << REDB "ERROR: " << Excepcion.what() << NC << endl;
	}
}

void alta_habitacion(){
	string nombre_hostal;
	string str_numero_hab;
	string str_precio_hab;
	string str_capacidad_hab;
	int numero_hab;
	float precio_hab;
	int capacidad_hab;
	string limpiar_buffer; 
	getline(cin,limpiar_buffer);

	obtener_hostales(); // Luego hay que eliminar este llamado

	cout << CYAN "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." NC << endl;
	
	cout << "Ingrese el nombre del hostal al que pertenece la habitacion: " << endl;
	getline(cin,nombre_hostal);
	if(nombre_hostal == "salir"){return;} /* en caso de que desee salir*/

	try{
		controlador -> no_existe_hostal(nombre_hostal);

		cout << "Ingrese el numero de la habitacion: " << endl;
		getline(cin,str_numero_hab);
		if(str_numero_hab == "salir"){return;} /* en caso de que desee salir*/
		numero_hab = stoi(str_numero_hab); /*parceo la entrada de str a int*/

		cout << "Ingrese el precio de la habitacion: " << endl;
		getline(cin,str_precio_hab);
		if(str_precio_hab == "salir"){return;} /* en caso de que desee salir*/
		precio_hab = stof(str_precio_hab); /*parceo la entrada de str a float*/

		cout << "Ingrese la capacidad de la habitacion: " << endl;
		getline(cin,str_capacidad_hab);
		if(str_capacidad_hab == "salir"){return;} /* en caso de que desee salir*/
		capacidad_hab = stoi(str_capacidad_hab); /*parceo la entrada de str a float*/

		controlador -> alta_habitacion(DTHabitacion(numero_hab, precio_hab, capacidad_hab),nombre_hostal);
		cout << "Habitacion ingresada correctamente" << endl;
	}catch(invalid_argument const& Excepcion){
		cout << endl << REDB "ERROR: " << Excepcion.what() << NC << endl;
	}
}

void asignar_empleado_hostal(){
	string nombre_hostal;
	string email_empleado;
	Cargo cargo;
	string limpiar_buffer;
	string entrada;
	getline(cin,limpiar_buffer);
	
	obtener_hostales();

	cout << CYAN "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." NC << endl;
	
	cout << "Ingrese el nombre del hostal al que sera asignado el empleado: " << endl;
	getline(cin,nombre_hostal);
	if(nombre_hostal == "salir"){return;} /* en caso de que desee salir*/
	
	try{
		controlador -> no_existe_hostal(nombre_hostal);
		obtener_no_empleados_hostal(nombre_hostal);

		cout << CYAN "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." NC << endl;
		cout << "Ingrese el email del empleado al que le sera asignado el hostal: "  << endl;
		getline(cin,email_empleado);
		cout << CYAN "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." NC << endl;
		cout << "Ingrese el cargo que se le asignara al empleado: "  << endl;
		
		while(entrada != "0" && entrada != "1" && entrada != "2" && entrada != "3"){
			cout << RED "Indique el cargo del empleado: 0 = Administracion | 1 = Limpieza | 2 = Recepcion | 3 = Infraestructura " NC<< endl;
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
		
		controlador -> Asignar_empleado_hostal(nombre_hostal,email_empleado,cargo);
	}catch(invalid_argument const& Excepcion){
		cout << endl << REDB "ERROR: " << Excepcion.what() << NC << endl;
	}
}

void realizar_reserva(){
	string nombre_hostal;
	string email_huesped;
	string limpiar_buffer;
	int numero_habitacion;
	getline(cin,limpiar_buffer);
	
	obtener_hostales();

	cout << CYAN "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." NC << endl;
	
	cout << "Ingrese el nombre del hostal al que deseas realizar la reserva: " << endl;
	getline(cin,nombre_hostal);

}

void consultar_top_3(){
	getchar(); //Si al llegar a esta línea, pide el enter, eliminar línea
}

void registrar_estadia(){
	getchar(); //Si al llegar a esta línea, pide el enter, eliminar línea
}

void finalizar_estadia(){
	getchar(); //Si al llegar a esta línea, pide el enter, eliminar línea
}

void calificar_estadia(){
	getchar(); //Si al llegar a esta línea, pide el enter, eliminar línea
}

void comentar_calificacion(){
	getchar(); //Si al llegar a esta línea, pide el enter, eliminar línea
}

void consulta_usuario(){
	getchar(); //Si al llegar a esta línea, pide el enter, eliminar línea
}

void consulta_hostal(){
	getchar(); //Si al llegar a esta línea, pide el enter, eliminar línea
}

void consulta_reserva(){
	getchar(); //Si al llegar a esta línea, pide el enter, eliminar línea
}

void consulta_estadia(){
	getchar(); //Si al llegar a esta línea, pide el enter, eliminar línea
}

void baja_reserva(){
	getchar(); //Si al llegar a esta línea, pide el enter, eliminar línea
}

void modificar_fecha(){
	getchar(); //Si al llegar a esta línea, pide el enter, eliminar línea
}

void datos_prueba(){
	/*Empleados*/
	controlador -> alta_empleado(DTEmpleado("Emilia","emilia@mail.com","123",Cargo::Recepcion));
	controlador -> alta_empleado(DTEmpleado("Leonardo","leo@mail.com","123",Cargo::Recepcion));
	controlador -> alta_empleado(DTEmpleado("Alina","alina@mail.com","123",Cargo::Administracion));
	controlador -> alta_empleado(DTEmpleado("Barliman","barli@mail.com","123",Cargo::Recepcion));
	// /*Huespedes*/
	controlador -> alta_huesped(DTHuesped("Sofia","sofia@mail.com","123",true));
	controlador -> alta_huesped(DTHuesped("Frodo","frodo@mail.com","123",true));
	controlador -> alta_huesped(DTHuesped("Sam","sam@mail.com","123",false));
	controlador -> alta_huesped(DTHuesped("Merry","merry@mail.com","123",false));
	controlador -> alta_huesped(DTHuesped("Pippin","pippin@mail.com","123",false));
	controlador -> alta_huesped(DTHuesped("Seba","seba@mail.com","123",true));
	// /*Hostales*/
	controlador -> alta_hostal(DTHostal("La posada del finger","Av de la playa 123,Maldonado","099111111"));
	controlador -> alta_hostal(DTHostal("Mochileros","Rambla Costanera 333,Rocha","42579512"));
	controlador -> alta_hostal(DTHostal("El Pony Pisador","Bree (preguntar por Gandalf)","000"));
	controlador -> alta_hostal(DTHostal("Altos del Fing","Av del Toro 1424","099892992"));
	controlador -> alta_hostal(DTHostal("Caverna Lujosa","Amaya 2515","233233235"));
	// /*Habitaciones*/
	controlador -> alta_habitacion(DTHabitacion(1,40,2),"La posada del finger");
	controlador -> alta_habitacion(DTHabitacion(2,10,7),"La posada del finger");
	controlador -> alta_habitacion(DTHabitacion(3,30,3),"La posada del finger");
	controlador -> alta_habitacion(DTHabitacion(4,5,12),"La posada del finger");
	controlador -> alta_habitacion(DTHabitacion(1,3,2),"Caverna Lujosa");
	controlador -> alta_habitacion(DTHabitacion(1,9,5),"El Pony Pisador");

	/* Asignación de empleados a hostales */
		// Empleado Hostel  Cargo
		// E1       HO1 	Recepción
		// E2       HO2 	Recepción
		// E3   	HO2 	Administración
		// E4 		HO3 	Recepción

 	/* Reservas */
		// Ref Hostel Habitación  Tipo 		  CheckIn 		  CheckOut 			Huespedes
		// R1  HO1 	  HA1 		  Individual  01/05/22 - 2pm  10/05/22 - 10am   H1
		// R2  HO3    HA6 		  Grupal      04/01/01 - 8pm  05/01/01 - 2am    H2,H3,H4,H5
		// R3  HO1    HA3 		  Individual  7/06/22 - 2pm   30/06/22 - 11am   H1
		// R4  HO5    HA5 		  Individual  10/06/22 - 2pm  30/06/22 - 11am   H6

	/* Estadías */
		// Ref  Reserva  Huesped Check in
		// ES1	R1	     H1      01/05/22 - 6pm
		// ES2	R2	     H2      04/01/01 - 9pm
		// ES3	R2	     H3      04/01/01 - 9pm
		// ES4	R2	     H4      04/01/01 - 9pm
		// ES5	R2	     H5      04/01/01 - 9pm
		// ES6	R4	     H6      07/06/22 - 6pm

	/* Finalización de estadías */
		// Estadía  Huesped   Check out
		// ES1 		H1 		  10/05/22 - 9am
		// ES2 		H2 		  05/01/01 - 2am
		// ES6 		H6 		  15/06/22 - 10pm

	/* Calificar estadía */
		/* Ref Estadía Huesped Comentario Calificación Fecha */
		
		/* C1  ES1     H1 
			Un poco caro para lo que ofrecen. 
			El famoso gimnasio era una caminadora (que hacía tremendo ruido) y 2 pesas, la piscina parecía
			el lago del Parque Rodó y el desayuno eran 2 tostadas con mermelada. Internet se pasaba cayendo. No vuelvo.
			3 11/05/22 - 6pm
		*/

		/* C2 ES2 H2 Se pone peligroso de noche, no recomiendo. Además no hay caja fuerte para guardar anillos.
			2 05/01/01 - 3am 
		*/
		
	    /* C3 ES6 H6 Había pulgas en la habitación. Que lugar más mamarracho!! 1 15/06/22 - 11pm */

	/* Comentar calificación */
		// Calificación Empleado Respuesta 						Fecha
		// C2 			 E4 	  Desapareció y se fue sin pagar.   06/01/01 - 3pm

	cout << GREEN "Datos de prueba cargados correctamente!" NC << endl;
	getchar(); //Si al llegar a esta línea, pide el enter, eliminar línea
}

void exit(){
	cout << endl << endl<< CYAN "Has terminado la ejecución del programa." NC << endl << endl;
}