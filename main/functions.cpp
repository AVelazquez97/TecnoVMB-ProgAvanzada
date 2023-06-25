using namespace std;
#include "functions.h"

/*
    La fábrica y el controlador se deberían instanciar de la siguiente manera:
    Fabrica fab;
    IControlador* controlador = fab.getInterface();
    controlador->operacion
*/

Fabrica fab;
IControlador* controlador = fab.getInterface();


/* Funciones auxiliares*/

/// @brief muestra las opciones disponibles del menu principal
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

/// @brief permite seleccionar una opción de las presentadas en el menú y controla que no se ingrese una equivocada
/// @return entero mayor o igual a 1 y menor o igual a 18
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
	do {
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

/// @brief permite pausar el sistema hasta que se presione enter
void press_enter() {
	cout << endl << CYAN "Presiona ENTER para continuar..." NC;
	getchar();
}

/// @brief recibe un cargo en string con valor ["0","1","2","3"] y lo castea a int
/// @return el cargo que coincida con el string recibido 
Cargo switch_cargo(string str_cargo) {
	Cargo cargo;
	switch(stoi(str_cargo)){
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
	return cargo;
}

/// @brief Imprime una fecha en un formato específico
void imprimir_fecha(tm* fecha) { 
    // Imprimir la fecha y hora en un formato legible
	cout << CYAN "" << put_time(fecha, "%d/%m/%y - %H") << " hs" NC << endl << endl;
}

/// @brief verifica si la fecha ingresada cumple con el formato establecido
/// @return true si el formato es correo, de lo contrario false 
bool verificar_fecha(string fecha_hora_str, tm* nueva_fecha) {
	/* Se crea un objeto istringstream utilizando la cadena fecha_hora_str para poder extraer los valores
	 individuales de la fecha y hora. Obviando las barras y guión */
	istringstream iss(fecha_hora_str);

	/* Se intenta extraer los valores de fecha y hora de iss y almacenarlos en la estructura nueva_fecha, 
	 utilizando el formato especificado. Si la extracción tiene éxito, los valores se asignan correctamente a 
	 nueva_fecha. Si falla, se establece el estado de falla en iss.*/
	iss >> get_time(nueva_fecha, "%d/%m/%y - %H");
	if (iss.fail()) {
		cout << endl << REDB "Formato de fecha y hora incorrecto. Por favor, intente nuevamente..." NC << endl;
		iss.clear();
		return false;
	}
	return true;
} 

/// @brief va hasta el controlador y trae los DTHostales. Luego los imprime.
/// Sirve tenerla como auxiliar ya que se pide en distintos casos de uso
void obtener_hostales() {
	OrderedDictionary* DTHostales = new OrderedDictionary();
	DTHostales = controlador -> obtener_hostales();

	cout << endl << GREEN << "| Lista de hostales |" << NC << endl << endl;

	for(IIterator* it = DTHostales -> getIterator(); it -> hasCurrent(); it -> next()){
        DTHostal* hostal = dynamic_cast<DTHostal*>(it -> getCurrent());
        cout << "| Nombre: " << hostal->get_nombre() << " |" << endl <<
		"| Direccion: " << hostal -> get_direccion() << " |" << endl <<
		"| Telefono: " << hostal -> get_telefono() << " |" << endl << endl;
    }
}

/// @brief lo mismo que obtener_hostales pero adicionalmente muestra el promedio de calificación de cada hostal
void obtener_hostales_con_promedio() {
	OrderedDictionary* DTHostales = new OrderedDictionary();
	DTHostales = controlador -> obtener_hostales();

	cout << endl << GREEN << "| Lista de hostales |" << NC << endl << endl;

	for(IIterator* it = DTHostales -> getIterator(); it -> hasCurrent(); it -> next()){
        DTHostal* hostal = dynamic_cast<DTHostal*>(it -> getCurrent());
        cout << "| Nombre: " << hostal->get_nombre() << " |" << endl <<
		"| Direccion: " << hostal -> get_direccion() << " |" << endl <<
		"| Telefono: " << hostal -> get_telefono() << " |" << endl <<
		"| Promedio: " << hostal -> get_promedio() << " |" << endl << endl;
    }
}

/// @brief imprime todos los empleados que no trabajan para un hostal en específico 
void obtener_no_empleados_hostal(string nombre_hostal) {
	OrderedDictionary* DTEmpleados = new OrderedDictionary();
	DTEmpleados = controlador -> obtener_no_empleados_hostal(nombre_hostal);

	cout << endl << GREEN "| Lista de empleados que no son del hostal: " << nombre_hostal << " |" NC << endl << endl;

	for(IIterator* it = DTEmpleados -> getIterator(); it -> hasCurrent(); it -> next()){
        DTEmpleado* empleado = dynamic_cast<DTEmpleado*>(it -> getCurrent());
        cout << "| " << empleado->get_nombre() << "|" <<
		empleado -> get_email() << "|" << endl << endl;
    }
}

/// @brief permite listar las habitaciones de un hostal determinado, pero que esten disponibles
///  en un determinado rango de fechas
void obtener_habitaciones_entre(string nombre_hostal,string str_checkin,string str_checkout) {
	/* La idea es implementar una funcion en controlador que liste las habitaciones de un hostal que estan 
	 disponibles dentro de un rango de fecha*/
}

/// @brief permita listar todos los usuarios registrados del sistema
void obtener_usuarios() {
	OrderedDictionary* emails = controlador -> obtener_usuarios();
	
	cout << endl << GREEN << "| Lista de usuarios registrados en el sistema: " << NC << endl << endl;
	
	for(IIterator* it = emails -> getIterator(); it -> hasCurrent(); it -> next()){
        String* email_usuario = dynamic_cast<String*>(it -> getCurrent());
        cout << "| " << email_usuario->getValue() << " |" << endl;
    }	
}

void obtener_huespedes(){
	OrderedDictionary* emails = controlador -> obtener_huespedes();
	
	cout << endl << GREEN << "| Lista de huespedes registrados en el sistema: |" << NC << endl << endl;
	
	for(IIterator* it = emails -> getIterator(); it -> hasCurrent(); it -> next()){
        String* email_huesped = dynamic_cast<String*>(it -> getCurrent());
        cout << "| " << email_huesped->getValue() << " |" << endl;
    }
}

/// @brief permite listar la información detallada de un huesped determinado 
void obtener_huesped_completo(string email) {
	DTHuesped huesped_completo = controlador -> obtener_huesped_completo(email);
	cout << endl << GREEN << "Mostrando informacion sobre el huesped con el email: " << email << NC << endl <<
	"| Nombre: " << huesped_completo.get_nombre() << " |" << endl <<
	"| Email: " << huesped_completo.get_email() << " |" << endl <<
	"| ¿Es tecno?(0 = no | 1 = si):" << huesped_completo.get_es_tecno() << " |" << endl;
}

/// @brief permite listar la información detallada de un empleado determinado
void obtener_empleado_completo(string email) {
	DTEmpleado empleado_completo = controlador -> obtener_empleado_completo(email);

	cout << endl << GREEN << "Mostrando informacion sobre el empleado con el email: " << email << NC << endl <<
	"| Nombre: " << empleado_completo.get_nombre() << " |" << endl <<
	"| Email: " << empleado_completo.get_email() << " |" << endl <<
	"| Trabaja para el hostal de nombre: " << empleado_completo.get_nombre_hostal() << " |" << endl <<
	"| Cargo (0 = Administracion | 1 = Limpieza | 2 = Recepcion | 3 = Infraestructura): " 
	<< empleado_completo.get_cargo() << endl;
}
/* Fin funciones auxiliares*/

/* Funciones del menu principal*/
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
		cargo = switch_cargo(entrada);
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

	obtener_hostales();

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
		cargo = switch_cargo(entrada);
		
		controlador -> asignar_empleado_hostal(nombre_hostal,email_empleado,cargo);
	}catch(invalid_argument const& Excepcion){
		cout << endl << REDB "ERROR: " << Excepcion.what() << NC << endl;
	}
}

void realizar_reserva(){
	string nombre_hostal;
	string email_huesped;
	string str_checkin;
	string str_checkout;
	tm checkin = {};
	tm checkout = {};
	string str_tipo = "";
	bool tipo;
	bool habitacion_valida = false;
	int numero_habitacion;
	string str_numero_habitacion;
	string limpiar_buffer;
	bool fecha_valida_checkin = false;
	bool fecha_valida_checkout = false;
	getline(cin,limpiar_buffer);
	
	
	obtener_hostales_con_promedio();

	cout << CYAN "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." NC << endl;
	
	cout << "Ingrese el nombre del hostal en el cual desea realizar la reserva: " << endl;
	getline(cin,nombre_hostal);
	if(nombre_hostal == "salir"){return;} /* en caso de que desee salir*/

	try{
		controlador -> no_existe_hostal(nombre_hostal);
		
		while(!fecha_valida_checkin) {
			cout << "Ingrese la fecha y hora del checkin con el siguiente formato de ejemplo " << RED "'12/12/24 - 18'" NC ": ";
			getline(cin,str_checkin);

			fecha_valida_checkin = verificar_fecha(str_checkin, &checkin);
		}

		while(!fecha_valida_checkout){
			cout << "Ingrese la fecha y hora del checkout con el siguiente formato de ejemplo " << RED "'12/12/24 - 18'" NC ": ";
			getline(cin,str_checkout);

			fecha_valida_checkout = verificar_fecha(str_checkout, &checkout);
		}

		while(str_tipo != "0" && str_tipo != "1"){
			cout << "Ingrese el tipo de reserva 0 = Individual 1 = Grupal: " << endl;
			getline(cin,str_tipo);
		}
		
		if(str_tipo == "0"){
			tipo = false;

			OrderedDictionary* habitaciones = controlador -> obtener_habitaciones(nombre_hostal, str_tipo, &checkin, &checkout);
			cout << endl << GREEN << "Mostrando informacion sobre las habitaciones individuales del hostal: " << nombre_hostal << NC << endl;
			
			for(IIterator* it = habitaciones -> getIterator(); it -> hasCurrent(); it -> next()){
				DTHabitacion* habitacion = dynamic_cast<DTHabitacion*>(it -> getCurrent());
				cout << "| Habitacion nro. " << habitacion -> get_numero() << " |" << endl 
				<< "| Precio: " << habitacion -> get_precio() << " |" << endl << endl;
    		}

			while(!habitacion_valida){
			cout << "Ingrese el numero de la habitacion deseada" << endl;
			getline(cin,str_numero_habitacion);
			IKey* ik_habitacion = new Integer(stoi(str_numero_habitacion));
			habitacion_valida = habitaciones -> member(ik_habitacion);
			}
			numero_habitacion = stoi(str_numero_habitacion);

			//listar los huespedes
			do{
				obtener_huespedes();
				cout << "Ingrese huesped que realiza la reserva:" << endl;
				getline(cin,email_huesped);
			}while(!controlador -> verificar_email(email_huesped));

			controlador -> alta_reserva_individual(nombre_hostal, numero_habitacion, email_huesped, &checkin, &checkout);
		}else if(str_tipo == "1"){
			tipo = true;

			//abro un for que vaya hasta la capacidad de la habitacion
				//mostrar los huespedes
				//y adentro del for voy recibiendo emails de huespedes
				//hasta que el usuario quiera continuar y salgo con un break
			//llamar a reserva grupal
		}
		
	}catch(invalid_argument const& Excepcion){
		cout << endl << REDB "ERROR: " << Excepcion.what() << NC << endl;
	}
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
	string email;
	int existe_email = -2;
	string limpiar_buffer;
	getline(cin,limpiar_buffer);

	obtener_usuarios();

	while(existe_email != -1 && existe_email != 0 && existe_email != 1 ){
		cout << "Ingrese el email: " << endl;
		getline(cin,email);
		if(email == "salir"){return;} /* en caso de que desee salir*/
		existe_email = controlador -> verificar_email_y_tipo(email);

		if(existe_email == 0){
			obtener_huesped_completo(email);
		}else if(existe_email == 1){
			obtener_empleado_completo(email);
		}else if(existe_email == -1){
			cout << endl << REDB "Email erroneo. Intenta de nuevo... " NC << endl;
		}
	}
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

void modificar_fecha() {
	string fecha_hora_str;
	/* Se crea una estructura tm y se inicializan todos sus miembros a cero. */
	tm nueva_fecha = {};
	bool fecha_valida = false;
	string limpiar_buffer; 
	getline(cin,limpiar_buffer);

	cout << "Fecha actual del sistema: ";
	imprimir_fecha(controlador->get_fecha_sistema());
    
	while(!fecha_valida) {
		cout << "Ingrese la fecha y hora con el siguiente formato de ejemplo " << RED "'12/12/24 - 18'" NC ": ";
		/* Se ingresa una nueva fecha por teclado */
		getline(cin, fecha_hora_str); 

		fecha_valida = verificar_fecha(fecha_hora_str, &nueva_fecha);	
	}
    controlador->set_fecha_sistema(&nueva_fecha);

	cout << endl << "Nueva fecha del sistema: ";
	imprimir_fecha(controlador->get_fecha_sistema());
}

void datos_prueba(){
	/*Empleados*/
	controlador -> alta_empleado(DTEmpleado("Emilia","emilia@mail.com","123",Cargo::Recepcion));
	controlador -> alta_empleado(DTEmpleado("Leonardo","leo@mail.com","123",Cargo::Recepcion));
	controlador -> alta_empleado(DTEmpleado("Alina","alina@mail.com","123",Cargo::Administracion));
	controlador -> alta_empleado(DTEmpleado("Barliman","barli@mail.com","123",Cargo::Recepcion));
	/*Huespedes*/
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
	controlador -> alta_hostal(DTHostal("Altos del Fing","Av del Toro 1424","099892992"));
	controlador -> alta_hostal(DTHostal("Caverna Lujosa","Amaya 2515","233233235"));
	/*Habitaciones*/
	controlador -> alta_habitacion(DTHabitacion(1,40,2),"La posada del finger");
	controlador -> alta_habitacion(DTHabitacion(2,10,7),"La posada del finger");
	controlador -> alta_habitacion(DTHabitacion(89,30,1),"La posada del finger"); // hay que borrarlo despues XD
	controlador -> alta_habitacion(DTHabitacion(3,30,3),"La posada del finger"); 
	controlador -> alta_habitacion(DTHabitacion(4,5,12),"La posada del finger");
	controlador -> alta_habitacion(DTHabitacion(1,3,2),"Caverna Lujosa");
	controlador -> alta_habitacion(DTHabitacion(1,9,5),"El Pony Pisador");

	/*Asignación de empleados a hostales*/
	controlador -> asignar_empleado_hostal("La posada del finger","emilia@mail.com",Recepcion);
	controlador -> asignar_empleado_hostal("Mochileros","leo@mail.com",Recepcion);
	controlador -> asignar_empleado_hostal("Mochileros","alina@mail.com",Administracion);
	controlador -> asignar_empleado_hostal("El Pony Pisador","barli@mail.com",Recepcion);
	

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
/*Fin funciones del menu principal*/