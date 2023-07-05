#include "functions.h"
#include "../datatypes/headers/DTEstadia.h"
#include "../datatypes/headers/DTReview.h"
using namespace std;

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

/// @brief recibe un cargo en string con valor ["0","1","2","3"] y lo castea a su correspondiente cargo
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
	cout << CYAN "" << put_time(fecha, "%d/%m/%Y - %H") << " hs" NC;
}

/// @brief verifica si la fecha ingresada cumple con el formato establecido.
/// Si lo cumple, se modifica la estructura que recibe por parámetro 
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

/// @brief valida que el formato de la fecha sea correcto y ademas que tengan sentido
/// es decir, que una fecha checkin no sea anterior a la fecha actual
/// @return 
bool verificar_fecha_checkin(string fecha_hora_str, tm* nueva_fecha){
	int flag_valida = 0;

	istringstream iss(fecha_hora_str);

	/* verifica el formato */
	iss >> get_time(nueva_fecha, "%d/%m/%y - %H");
	if (iss.fail()) {
		cout << endl << REDB "Formato de fecha y hora incorrecto. Por favor, intente nuevamente..." NC << endl;
		iss.clear();
		flag_valida += 1;
	}
	/*verifica que la fecha que entra por parametro no sea anterior a la fecha sistema*/
	if(controlador -> compararFechas(nueva_fecha) == 0){
		cout << endl << REDB "La fecha de checkin no puede ser anterior a la fecha actual del sistema. Por favor, intente nuevamente..." NC << endl;
		iss.clear();
		flag_valida += 1;
	}

	if(flag_valida == 0){
		iss.clear();
		return true;
	}else{
		iss.clear();
		return false;
	}

}

/// @brief valida que el formato de la fecha sea correcto y ademas que tengan sentido
/// es decir, que una fecha checkin no sea anterior a la fecha actual
/// @return 
bool verificar_fecha_checkout(string fecha_hora_str, tm* fecha_checkout, tm* fecha_checkin){
	int flag_valida = 0;

	istringstream iss(fecha_hora_str);

	/* verifica el formato */
	iss >> get_time(fecha_checkout, "%d/%m/%y - %H");
	if (iss.fail()) {
		cout << endl << REDB "Formato de fecha y hora incorrecto. Por favor, intente nuevamente..." NC << endl;
		iss.clear();
		flag_valida += 1;
	}
	/*verifica que la fecha que entra por parametro no sea anterior a la fecha sistema*/
	if(controlador -> comparar_fechas_generico(fecha_checkout, fecha_checkin) == 0){
		cout << endl << REDB "La fecha de checkout no puede ser anterior a la fecha de checkin. Por favor, intente nuevamente..." NC << endl;
		iss.clear();
		flag_valida += 1;
	}

	if(flag_valida == 0){
		iss.clear();
		return true;
	}else{
		iss.clear();
		return false;
	}

}

/// @brief va hasta el controlador y trae los DTHostales. Luego los imprime.
/// Sirve tenerla como auxiliar ya que se pide en distintos casos de uso
OrderedDictionary* obtener_hostales() {
	OrderedDictionary* DTHostales = new OrderedDictionary();
	DTHostales = controlador -> obtener_hostales();

	cout << endl << GREEN << "| Lista de hostales |" << NC << endl << endl;

	for(IIterator* it = DTHostales -> getIterator(); it -> hasCurrent(); it -> next()){
        DTHostal* hostal = dynamic_cast<DTHostal*>(it -> getCurrent());
        cout << "| Nombre: " << hostal->get_nombre() << " |" << endl <<
		"| Direccion: " << hostal -> get_direccion() << " |" << endl <<
		"| Telefono: " << hostal -> get_telefono() << " |" << endl << endl;
    }
	return DTHostales;
}

int obtener_estadias_huesped_fin(string nombre_hostal,string email_huesped){
	OrderedDictionary* DT_Estadia = new OrderedDictionary();
	DT_Estadia = controlador -> obtener_estadias_fin_huesped(nombre_hostal,email_huesped);
	cout << endl << GREEN << "| Lista de estadias finalizadas |" << NC << endl << endl;

	for(IIterator* it = DT_Estadia -> getIterator(); it -> hasCurrent(); it -> next()){
        DTEstadia* estadia = dynamic_cast<DTEstadia*>(it -> getCurrent());
        cout << *estadia << endl;
    }
	return DT_Estadia -> getSize();
}

OrderedDictionary* listar_comentarios_sr(string email_empleado){
	OrderedDictionary* DT_Reviews = new OrderedDictionary();
	DT_Reviews = controlador -> listar_comentarios_sin_responder(email_empleado);
	
	cout << endl << GREEN << "| Lista de comentarios sin responder |" << NC << endl << endl;

	for(IIterator* it = DT_Reviews -> getIterator(); it -> hasCurrent(); it -> next()){
        DTReview* review = dynamic_cast<DTReview*>(it -> getCurrent());
        cout << *review << endl;
    }
}

void mostrar_reserva_usuario(OrderedDictionary* dt_reserva) {
	cout << endl << GREEN << "| Lista de reservas no canceladas |" << NC << endl << endl;

	for(IIterator* it = dt_reserva -> getIterator(); it -> hasCurrent(); it -> next()){
        DTReserva* reserva = dynamic_cast<DTReserva*>(it -> getCurrent());
        cout << *reserva;
    }
}

void mostrar_reservas_hostal(OrderedDictionary* dt_reserva, string nombre_hostal) {
	cout << endl << GREEN << "| Lista de reservas del hostal: " << nombre_hostal << " |" NC << endl << endl;

	for(IIterator* it = dt_reserva -> getIterator(); it -> hasCurrent(); it -> next()){
        DTReserva* reserva = dynamic_cast<DTReserva*>(it -> getCurrent());
        cout << *reserva;
    }
}

/// @brief lo mismo que obtener_hostales pero adicionalmente muestra el promedio de calificación de cada hostal
OrderedDictionary* obtener_hostales_con_promedio() {
	OrderedDictionary* DTHostales = new OrderedDictionary();
	DTHostales = controlador -> obtener_hostales();

	cout << endl << GREEN << "| Lista de hostales |" << NC << endl << endl;

	for(IIterator* it = DTHostales -> getIterator(); it -> hasCurrent(); it -> next()){
        DTHostal* hostal = dynamic_cast<DTHostal*>(it -> getCurrent());
		cout << *hostal;
    }
	return DTHostales;
}

/// @brief imprime todos los empleados que no trabajan para un hostal en específico 
OrderedDictionary* obtener_no_empleados_hostal(string nombre_hostal) {
	OrderedDictionary* DTEmpleados = new OrderedDictionary();
	DTEmpleados = controlador -> obtener_no_empleados_hostal(nombre_hostal);

	cout << endl << GREEN "| Lista de empleados que no son del hostal: " << nombre_hostal << " |" NC << endl << endl;

	for(IIterator* it = DTEmpleados -> getIterator(); it -> hasCurrent(); it -> next()){
        DTEmpleado* empleado = dynamic_cast<DTEmpleado*>(it -> getCurrent());
        cout << "| " << empleado->get_nombre() << "|" <<
		empleado -> get_email() << "|" << endl << endl;
    }
	return DTEmpleados;
}

/// @brief permita listar todos los usuarios registrados del sistema
OrderedDictionary* obtener_usuarios() {
	OrderedDictionary* emails = controlador -> obtener_usuarios();
	
	cout << endl << GREEN << "Lista de usuarios registrados en el sistema: " << NC << endl << endl;
	
	for(IIterator* it = emails -> getIterator(); it -> hasCurrent(); it -> next()){
        String* email_usuario = dynamic_cast<String*>(it -> getCurrent());
        cout << "| " << email_usuario->getValue() << " |" << endl;
    }	

	return emails;
}

void obtener_huespedes(){
	OrderedDictionary* emails = controlador -> obtener_huespedes();
	
	cout << endl << GREEN << "| Lista de huespedes registrados en el sistema: |" << NC << endl << endl;
	
	for(IIterator* it = emails -> getIterator(); it -> hasCurrent(); it -> next()){
        String* email_huesped = dynamic_cast<String*>(it -> getCurrent());
        cout << "| " << email_huesped->getValue() << " |" << endl;
    }
}

OrderedDictionary* obtener_huespedes_con_return(){
	OrderedDictionary* emails = controlador -> obtener_huespedes();
	return emails;
}

/// @brief permite listar la información detallada de un huesped determinado 
void obtener_huesped_completo(string email) {
	DTHuesped huesped_completo = controlador -> obtener_huesped_completo(email);
	cout << endl << GREEN << "Mostrando informacion sobre el huesped con el email: " << email << NC << endl;
	cout << huesped_completo;
}

/// @brief permite listar la información detallada de un empleado determinado
void obtener_empleado_completo(string email) {
	DTEmpleado empleado_completo = controlador -> obtener_empleado_completo(email);
	cout << endl << GREEN << "Mostrando informacion sobre el empleado con el email: " << email << NC << endl;
	cout << empleado_completo;
}

/// @brief obtiene un tipo de estado
/// @param tipo_estado 
/// @return devuelve la su correspondiente nombre en string
string obtener_estado_reserva(Estado tipo_estado){
	string estado;
	switch(tipo_estado){
		case 0:{
			estado = "Abierta";
			break;
		}
		case 1:{
			estado = "Cerrada";
			break;
		}
		case 2:{
			estado = "Cancelada";
			break;
		}
	}
	return estado;
}

/// @brief permite listar la información detallada de un hostal.
void obtener_hostal_completo(string nombre_hostal) {
	DTHostal_completo hostal_completo = controlador -> obtener_hostal_completo(nombre_hostal);
	cout << endl << GREEN << "| Detalles sobre el hostal: " << nombre_hostal << " |" NC << endl << endl;
	cout << hostal_completo;
}
/* Fin funciones auxiliares*/

/* Funciones del menu principal*/
void alta_usuario(){
	bool existe_email = true, cancelar = false, es_tecno;
	string entrada = "", email, nombre, contrasena, tipo = "";
	Cargo cargo;

	/*el unico proposito de esta variable es guardar
	en ella lo que sea que traiga el buffer asi nos evitamos que se salte
	pedir por el nombre*/
	string limpiar_buffer; 
	getline(cin,limpiar_buffer);

	cout << CYAN "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." NC << endl;
	
	cout << endl << "Ingrese el nombre: ";
	getline(cin,nombre);
	if(nombre == "salir"){return;} /* en caso de que desee salir*/

	while(existe_email){
		cout << endl << "Ingrese el email: ";
		getline(cin, email);
		if(email == "salir"){return;} /* en caso de que desee salir*/
		existe_email = controlador -> verificar_email(email);
		if(existe_email){
			cout << endl << REDB "Ya existe un usuario registrado con ese email. Intenta de nuevo... " NC << endl;
		}
	}

	cout << endl << "Ingrese la contraseña: ";
	getline(cin,contrasena);
	if(contrasena == "salir"){return;} /* en caso de que desee salir*/

	while(tipo != "0" && tipo != "1"){
		cout << endl << "Ingrese el tipo de usuario que quiere registrar (0 = Huesped | 1 = Empleado): ";
		getline(cin,tipo);
		if(tipo == "salir"){return;} /* en caso de que desee salir*/
		if(tipo != "0" && tipo != "1" ){
			cout << endl << REDB "Debes ingresar un tipo válido." NC << endl;
		}
	}

	if(tipo == "0"){
		while(entrada != "0" && entrada != "1"){
			cout << endl << "¿El Huesped es Tecno? (0 = No | 1 = Si): ";
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
		cout << endl << GREEN "Huesped ingresado correctamente!" NC << endl;
	}else{
		while(entrada != "0" && entrada != "1" && entrada != "2" && entrada != "3"){
			cout << endl << "Indique el cargo del empleado (0 = Administracion | 1 = Limpieza | 2 = Recepcion | 3 = Infraestructura): ";
			getline(cin,entrada);
			if(entrada == "salir"){return;} /* en caso de que desee salir*/
			if(entrada != "0" && entrada != "1" && entrada != "2" && entrada != "3"){
				cout << endl << REDB "Debes ingresar un cargo válido." NC << endl;
			}
		}
		cargo = switch_cargo(entrada);
		/*hacer la llamada al sistema con el DTEmpleado*/
		DTEmpleado nuevo_empleado(nombre, email, contrasena, cargo);
		controlador -> alta_empleado(nuevo_empleado);
		cout << endl << GREEN "Empleado ingresado correctamente!" NC << endl;
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
	int numero_hab, capacidad_hab;
	float precio_hab;
	OrderedDictionary* hostales;
	string limpiar_buffer; 
	getline(cin,limpiar_buffer);

	hostales = obtener_hostales();
	
	if (hostales->isEmpty()){
		cout << endl << REDB "No hay hostales registrados en el sistema." NC << endl;
		return;
	}

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
		cout << endl << GREEN "HABITACIÓN INGRESADA CON ÉXITO! " NC << endl;
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
	OrderedDictionary* lista_empleados_sin_hostal;
	OrderedDictionary*  hostales;
	bool es_miembro = false;
	getline(cin,limpiar_buffer);
	
	hostales = obtener_hostales();
	
	if (hostales->isEmpty()){
		cout << endl << REDB "No hay hostales registrados en el sistema." NC << endl;
		return;
	}

	cout << CYAN "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." NC << endl;
	
	try{
		cout << "Ingrese el nombre del hostal al que sera asignado el empleado: " << endl;
		getline(cin,nombre_hostal);
		if(nombre_hostal == "salir"){return;} /* en caso de que desee salir*/
		controlador -> no_existe_hostal(nombre_hostal);
	}catch(invalid_argument const& Excepcion){
		cout << endl << REDB "ERROR: " << Excepcion.what() << NC << endl;
		return;
	}

	lista_empleados_sin_hostal = obtener_no_empleados_hostal(nombre_hostal);

	if(lista_empleados_sin_hostal->isEmpty()){
		cout << endl << REDB "No hay ningún empleado para asignar al hostal." NC << endl;
		return;
	}

	while (!es_miembro) { // Por defecto, es miembro viene con false para entrar en el while
		cout << endl << "Ingresa el nombre del empleado que deseas asignar al hostal: ";
		getline(cin, email_empleado);

		if(email_empleado == "salir"){return;}

		char parce_char[email_empleado.length()+1];
		strcpy(parce_char, email_empleado.c_str());
		if(lista_empleados_sin_hostal->member(new String(parce_char))){
			es_miembro = true;
		} else{
			cout << endl << REDB "Error: Debes ingresar un mail que forme parte de la lista de empleados." NC << endl;
		}
	}
	
	while(entrada != "0" && entrada != "1" && entrada != "2" && entrada != "3"){
		cout << endl << RED "Indique el cargo del empleado (0 = Administracion | 1 = Limpieza | 2 = Recepcion | 3 = Infraestructura): " NC << endl;
		getline(cin,entrada);
		if(entrada == "salir"){return;} /* en caso de que desee salir*/
	}
	
	cargo = switch_cargo(entrada);
	controlador -> asignar_empleado_hostal(nombre_hostal, email_empleado, cargo);
	cout << endl << GREEN "El empleado con el email " << email_empleado << " fue asignado al hostal " << nombre_hostal << NC << endl;
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
	bool fecha_valida_checkin = false;
	bool fecha_valida_checkout = false;
	OrderedDictionary* hostales;

	string limpiar_buffer;
	getline(cin,limpiar_buffer);
	
	
	hostales = obtener_hostales_con_promedio();
	
	if (hostales->isEmpty()){
		cout << endl << REDB "No hay hostales registrados en el sistema." NC << endl;
		return;
	}

	cout << CYAN "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." NC << endl;
	
	cout << "Ingrese el nombre del hostal en el cual desea realizar la reserva: " << endl;
	getline(cin,nombre_hostal);
	if(nombre_hostal == "salir"){return;} /* en caso de que desee salir*/

	try{
		controlador -> no_existe_hostal(nombre_hostal);
		
		while(!fecha_valida_checkin) {
			cout << "Ingrese la fecha y hora del checkin con el siguiente formato de ejemplo " << RED "'25/07/2023 - 18'" NC ": ";
			getline(cin,str_checkin);

			fecha_valida_checkin = verificar_fecha_checkin(str_checkin, &checkin);
		}

		while(!fecha_valida_checkout){
			cout << "Ingrese la fecha y hora del checkout con el siguiente formato de ejemplo " << RED "'25/07/2023 - 18'" NC ": ";
			getline(cin,str_checkout);

			fecha_valida_checkout = verificar_fecha_checkout(str_checkout, &checkout, &checkin);
		}

		while(str_tipo != "0" && str_tipo != "1"){
			cout << "Ingrese el tipo de reserva 0 = Individual 1 = Grupal: " << endl;
			getline(cin,str_tipo);
		}
		
		if(str_tipo == "0"){ //Reserva Individual
			tipo = false;
			/* en obtener_habitaciones se tiene que implementar el filtro de habitaciones segun fecha */
			OrderedDictionary* habitaciones = controlador -> obtener_habitaciones_individuales(nombre_hostal, str_tipo, &checkin, &checkout);
			if(habitaciones -> getSize() >= 1){
				cout << endl << GREEN << "Mostrando informacion sobre las habitaciones individuales del hostal: " << nombre_hostal << NC << endl;
			
				for(IIterator* it = habitaciones -> getIterator(); it -> hasCurrent(); it -> next()){
					DTHabitacion* habitacion = dynamic_cast<DTHabitacion*>(it -> getCurrent());
					cout << *habitacion << endl;
				}

				while(!habitacion_valida){
					cout << "Ingrese el numero de la habitacion deseada: ";
					getline(cin,str_numero_habitacion);
					IKey* ik_habitacion = new Integer(stoi(str_numero_habitacion));
					habitacion_valida = habitaciones -> member(ik_habitacion);
				}
				numero_habitacion = stoi(str_numero_habitacion);
			}else{
				cout << RED << "Este hostal no tiene habitaciones ingresadas, intente con otro o ingrese habitaciones a dicho hostal." << NC << endl;
				return;
			}
			
			do{
				obtener_huespedes();
				cout << "Ingrese huesped que realiza la reserva:" << endl;
				getline(cin,email_huesped);
				if(!controlador -> validar_email_huesped(email_huesped)){
					cout << endl << REDB "No existe un huésped registrado con ese email. Intenta de nuevo... " NC << endl;
				}
			}while(!controlador -> validar_email_huesped(email_huesped));

			controlador -> alta_reserva_individual(nombre_hostal, numero_habitacion, email_huesped, &checkin, &checkout);
			cout << GREEN << "Reserva Individual realizada correctamente" << NC << endl;
		}else if(str_tipo == "1"){ //Reserva Grupal
			tipo = true;

			OrderedDictionary* habitaciones = controlador -> obtener_habitaciones_grupales(nombre_hostal, str_tipo, &checkin, &checkout);
			if(habitaciones -> getSize() >= 1){
				cout << endl << GREEN << "Mostrando informacion sobre las habitaciones grupales del hostal: " << nombre_hostal << NC << endl << endl;
				
					for(IIterator* it = habitaciones -> getIterator(); it -> hasCurrent(); it -> next()){
						DTHabitacion* habitacion = dynamic_cast<DTHabitacion*>(it -> getCurrent());
						cout << *habitacion << endl;
					}

						while(!habitacion_valida){
							cout << "Ingrese el numero de la habitacion deseada: ";
							getline(cin,str_numero_habitacion);
							IKey* ik_habitacion = new Integer(stoi(str_numero_habitacion));
							habitacion_valida = habitaciones -> member(ik_habitacion);
						}
				numero_habitacion = stoi(str_numero_habitacion);
			}else{
				cout << RED << "Este hostal no tiene habitaciones ingresadas, intente con otro o ingrese habitaciones a dicho hostal." << NC << endl;
				return;
			}
			
			/*lista con los emails de los huespedes seleccionados para la reserva*/
			OrderedDictionary* lista_huespedes_disponibles = obtener_huespedes_con_return();
			/*si no hay huespedes registrados no se le da la opcion de ingresar huespedes*/
			if(lista_huespedes_disponibles -> getSize() <= 0){
				cout << endl << REDB << "No existen huespedes registrados para poder agregar a la reserva, intente de nuevo!" << NC << endl << endl;
				return;
			}
			OrderedDictionary* lista_huespedes_seleccionados = new OrderedDictionary();
			bool seguir_ingresando = true;
			for (int i = 0; i < controlador -> obtener_capacidad_habitacion(numero_habitacion, nombre_hostal); i++){
					do{
						/*si no quedan huespedes que mostrar se va del for y hace la reserva grupal con los que tenga ingresados
						hasta el momento*/
						if(lista_huespedes_disponibles -> getSize() <= 0){
							cout << endl << GREEN << "| Todos los huespedes disponibles fueron registrados en la reserva! |" << NC << endl << endl;
							email_huesped = "parar";
						}else{
							cout << endl << GREEN << "| Lista de huespedes registrados en el sistema: |" << NC << endl << endl;
		
								for(IIterator* it = lista_huespedes_disponibles -> getIterator(); it -> hasCurrent(); it -> next()){
									String* email_huesped = dynamic_cast<String*>(it -> getCurrent());
									cout << "| " << email_huesped->getValue() << " |" << endl;
								}

							cout << "Ingrese un huesped o ingrese 'parar' para dejar de ingresar huespedes:" << endl;
							getline(cin,email_huesped);
						}
						

						//si quiere dejar de ingresar huespedes pero no tiene ninguno registrado
						if(email_huesped == "parar" && lista_huespedes_seleccionados -> getSize() < 1){
							cout << RED << "Debe ingresar al menos un huesped, intente denuevo." << NC << endl;
							seguir_ingresando = true;
							press_enter();
						//si quiere dejar de ingresar huespedes y tiene al menos uno registrado
						}else if(email_huesped == "parar" && lista_huespedes_seleccionados -> getSize() >= 1){
							seguir_ingresando = false;
							i = controlador -> obtener_capacidad_habitacion(numero_habitacion, nombre_hostal); //me aseguro que el for pare
						}
						if(!controlador -> validar_email_huesped(email_huesped) && email_huesped != "parar"){
							cout << endl << REDB "No existe un huésped registrado con ese email. Intenta de nuevo... " NC << endl;
						}
					}while(!controlador ->validar_email_huesped(email_huesped) && seguir_ingresando);
				/*en caso de que haya salido del while y no haya sido porque puso parar*/
				if(email_huesped != "parar"){
					cout << endl << CYAN << "Huesped con el mail: "<< email_huesped << " ingresado a la reserva correctamente" << NC << endl;
					
					char parce_email_huesped[email_huesped.length()+1];
					strcpy(parce_email_huesped,email_huesped.c_str());

					IKey* ik_huesped = new String(parce_email_huesped); //creo la IK

					String* email_huesped = new String(parce_email_huesped); //creo un icollectible con el email_huesped

					lista_huespedes_seleccionados -> add(ik_huesped,email_huesped);	
					lista_huespedes_disponibles -> remove(ik_huesped);
				}
			}
			controlador -> alta_reserva_grupal(nombre_hostal, numero_habitacion, lista_huespedes_seleccionados, &checkin, &checkout);
			cout << GREEN << "Reserva Grupal realizada correctamente" << NC << endl;
		}
	}catch(invalid_argument const& Excepcion){
		cout << endl << REDB "ERROR: " << Excepcion.what() << NC << endl;
	}
}

void consultar_top_3() {
	OrderedDictionary* lista_top_3 = controlador -> obtener_top_3_hostales();
	if(lista_top_3 -> getSize() == 0){
		cout << REDB << "No hay hoteles registrados en el sistema!" << NC << endl;
	}else{
		cout << GREEN << "Mostrando el top 3 de hostales" << NC << endl << endl; 
		int puesto = 1;
		for(IIterator* it = lista_top_3 -> getIterator(); it -> hasCurrent(); it -> next()){
			DTHostal* dt_hostal = dynamic_cast<DTHostal*>(it -> getCurrent());
			cout << GREEN << "|posicion: " << puesto << " |" << NC << endl
			<< "|nombre: " << dt_hostal->get_nombre() << " |" << endl <<
			"|promedio: " << dt_hostal->get_promedio() << " |" << endl << endl;
			puesto += 1;
		}
	}
	
	getchar(); //Si al llegar a esta línea, pide el enter, eliminar línea
}

void registrar_estadia(){
	string email_huesped;
	string nombre_hostal;
	string entrada_codigo_reserva;
	int codigo_reserva;
	bool int_casteado = false, es_miembro = false;
	OrderedDictionary* lista_reservas_usuario;
	OrderedDictionary* hostales;

	string limpiar_buffer;
	getline(cin,limpiar_buffer);

	hostales = obtener_hostales();
	if (hostales->isEmpty()){
		cout << endl << REDB "No hay hostales registrados en el sistema." NC << endl;
		return;
	}
	
	cout << CYAN "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." NC << endl;
	
	do { // Ingreso del nombre del hostal
		cout << endl << "Ingrese el nombre del hostal al que pertenece la habitacion: " << endl;
		getline(cin, nombre_hostal);
		if(nombre_hostal == "salir"){return;} /* en caso de que desee salir*/

		if(!(controlador->existe_hostal_bool(nombre_hostal))){ 
			cout << endl << REDB << "El nombre de hostal que ingresaste no existe. Intenta de nuevo..." NC << endl; 
		}
	} while (!(controlador->existe_hostal_bool(nombre_hostal)));
	
	do { // Ingreso del email del huesped
		cout << endl << "Ingrese el email del huesped que hizo la reserva para registrar la estadia: " << endl;
		getline(cin, email_huesped);
		if(email_huesped == "salir"){return;} /* en caso de que desee salir*/

		if(!controlador -> validar_email_huesped(email_huesped)){
			cout << endl << REDB "No existe un huésped registrado con ese email. Intenta de nuevo... " NC << endl;
		}
	} while(!controlador ->validar_email_huesped(email_huesped));
	if(controlador -> contar_estadias_activas(email_huesped) != 0){
		cout << RED << "Este huesped ya tiene una estadia activa, en caso de querer registrar otra, finalicela." << NC << endl;
		return;
	}
	/* Se obtienen las reservas para el hostal y de un huesped determinado*/
	lista_reservas_usuario = controlador -> obtener_reserva_usuario(nombre_hostal, email_huesped);

	if(lista_reservas_usuario->isEmpty()) { 
		cout << REDB "No hay reservas para el huesped seleccionado" NC << endl;
		return;
	}
	
	mostrar_reserva_usuario(lista_reservas_usuario);

	// Si valida que si o si ingrese un número entero y que sea un código del listado de reservas del usuario
    while (!int_casteado && !es_miembro) {
        cout << endl << "Ingrese el numero de la reserva de la que se quiere registrar la estadia: ";
        getline(cin, entrada_codigo_reserva);

		if(entrada_codigo_reserva == "salir"){return;}

        try {
            codigo_reserva = stoi(entrada_codigo_reserva);
			int_casteado = true;
        } catch (const exception& e) {
            cout << endl << REDB "Error: No has ingresado un número entero." NC << endl;
        }

		if(lista_reservas_usuario->member(new Integer(codigo_reserva))){
			es_miembro = true;
		} else{
			cout << endl << REDB "Error: Debes ingresar un código que forme parte de la lista de reservas." NC << endl;
			int_casteado = false;
		}
		
    }

	controlador -> alta_estadia(codigo_reserva, email_huesped /* ,nombre_hostal */);
	
	cout << endl << GREEN "ESTADIA REGISTRADA CON EXITO! " NC << endl;
}

void finalizar_estadia(){
	string nombre_hostal;
	string email_huesped;
	int estadia_a_finalizar;
	OrderedDictionary* hostales;

	string limpiar_buffer;
	getline(cin,limpiar_buffer);
	
	hostales = obtener_hostales();
	if (hostales->isEmpty()){
		cout << endl << REDB "No hay hostales registrados en el sistema." NC << endl;
		return;
	}

	cout << CYAN "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." NC << endl;
	
	cout << "Ingrese el nombre del hostal al que está asignada la estadía: " << endl;
	getline(cin,nombre_hostal);
	if(nombre_hostal == "salir"){return;} /* en caso de que desee salir*/
	
	try{
		controlador -> no_existe_hostal(nombre_hostal);
		do{
			cout << "Ingrese el email del huesped para finalizar la estadía activa: " << endl;
			getline(cin,email_huesped);
			if(email_huesped == "salir"){return;}
			if(!controlador -> validar_email_huesped(email_huesped)){
				cout << endl << REDB "No existe un huésped registrado con ese email. Intenta de nuevo... " NC << endl;
			}
		}while(!controlador ->validar_email_huesped(email_huesped));
			if(controlador -> contar_estadias_activas(email_huesped,nombre_hostal) == 0){
			cout << RED << "Este huesped no tiene ninguna estadia activa en este hostal." << NC << endl;
			return;
			}
		estadia_a_finalizar = controlador ->existe_estadia(nombre_hostal,email_huesped);
		controlador -> finalizar_estadia(estadia_a_finalizar,email_huesped);
	}catch(invalid_argument const& Excepcion){
		cout << endl << REDB "ERROR: " << Excepcion.what() << NC << endl;
	}
	cout << endl << GREEN "ESTADIA FINALIZADA CON EXITO! " NC << endl;
}

void calificar_estadia(){
	string nombre_hostal;
	string email_huesped;
	string comentario;
	string calificacion;
	string codigo_estadia;
	OrderedDictionary* hostales;

	string limpiar_buffer;
	getline(cin,limpiar_buffer);
	
	
	hostales = obtener_hostales();
	if (hostales->isEmpty()){
		cout << endl << REDB "No hay hostales registrados en el sistema." NC << endl;
		return;
	}

	cout << CYAN "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." NC << endl;
	
	cout << "Ingrese el nombre del hostal al que está asignada la estadía: " << endl;
	getline(cin,nombre_hostal);
	if(nombre_hostal == "salir"){return;} /* en caso de que desee salir*/
	
	try{
		controlador -> no_existe_hostal(nombre_hostal);
		do{
			cout << "Ingrese el nombre del huesped al que está asignada la estadía: " << endl;
			getline(cin,email_huesped);
			if(email_huesped == "salir"){return;}
		}while(!controlador -> validar_email_huesped(email_huesped));
		
		if(obtener_estadias_huesped_fin(nombre_hostal,email_huesped) == 0){
			cout<< REDB "Este huesped no tiene estadias finalizadas/registradas para hacer una calificacion en este hostal" NC << endl;
			return;
		}

		//queda pendiente meter un control al numero de estadia ingresado
		cout << "Seleccione la estadia que desea calificar: " << endl;
		getline(cin,codigo_estadia);
		if(codigo_estadia == "salir"){return;}

		cout << "Por favor ingrese su opinion" << endl;
		getline(cin,comentario);
		if(comentario == "salir"){return;}

		do{
			cout << "Por favor ingrese una calificacion del 1 al 5" << endl;
			getline(cin,calificacion);
			if(calificacion == "salir"){return;}
		}while(stoi(calificacion) < 1 || stoi(calificacion) > 5  );
		
		controlador -> calificar_estadia(nombre_hostal,stoi(codigo_estadia),comentario,stoi(calificacion),email_huesped);
		cout << "ESTADIA CALIFICADA CON EXITO!" << endl;
	}catch(invalid_argument const& Excepcion){
		cout << endl << REDB "ERROR: " << Excepcion.what() << NC << endl;
	}
	getchar(); //Si al llegar a esta línea, pide el enter, eliminar línea
}

void comentar_calificacion(){
	string nombre_hostal, email_empleado, codigo_review, respuesta;
	bool existe_email = false;
	OrderedDictionary* DT_reviews = new OrderedDictionary();
	OrderedDictionary* empleados; 

	string limpiar_buffer;
	getline(cin,limpiar_buffer);

	if(controlador->obtener_empelados()->isEmpty()){
		cout << endl << REDB "Para poder comentar una calificación debes registrar empleados en el sistema." << NC << endl;
		return;
	}

	cout << CYAN "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." NC << endl;
	
	while(!existe_email){
		cout << endl <<  "Ingresa el email del empleado que va a responder la review: ";
		getline(cin, email_empleado);
		if(email_empleado == "salir"){return;} /* en caso de que desee salir*/
		existe_email = controlador -> verificar_email_empleado(email_empleado);
		if(!existe_email){
			cout << endl << REDB "No existe un empleado registrado con ese email. Intenta de nuevo... " NC << endl;
		}
	}

	DT_reviews = listar_comentarios_sr(email_empleado);
	
	cout << endl << "Ingrese el codigo de la review a comentar: ";
	getline(cin, codigo_review);
	if(codigo_review == "salir"){return;} /* en caso de que desee salir*/

	cout << endl << "Ingrese la respuesta: ";
	getline(cin, respuesta);
	if(respuesta == "salir"){return;} /* en caso de que desee salir*/

	try{
		//Falta controlar que el codigo review pertenezca al DT_reviews, algo similar se hace en registrar estadía
		controlador -> alta_respuesta(stoi(codigo_review),email_empleado,respuesta);
		cout << GREEN << "RESPUESTA INGRESADA CORRECTAMENTE!" NC << endl;
	}catch(invalid_argument const& Excepcion){
		cout << endl << REDB "ERROR: " << Excepcion.what() << NC << endl;
	}

	delete DT_reviews;
}

void consulta_usuario(){
	string email;
	int existe_email = -1;
	OrderedDictionary* emails;

	string limpiar_buffer;
	getline(cin,limpiar_buffer);

	emails = obtener_usuarios();

	if (emails->isEmpty()){
		cout << endl << REDB "No hay usuarios registrados en el sistema." NC << endl;
		return;
	}

	cout << endl <<  CYAN "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." NC << endl;

	while(existe_email == -1){
		cout << endl << "Ingresa el email del usuario que deseas consultar: " ;
		getline(cin,email);
		if(email == "salir"){return;} /* en caso de que desee salir*/
		existe_email = controlador -> verificar_email_y_tipo(email);

		if(existe_email == 0){
			obtener_huesped_completo(email);
		}else if(existe_email == 1){
			obtener_empleado_completo(email);
		}else {
			cout << endl << REDB "No existe un usuario con ese email. Intenta de nuevo..." NC << endl;
		}
	}
}

void consulta_hostal(){
	string nombre_hostal;
	OrderedDictionary* hostales;
	OrderedDictionary* reservas_hostal;
	
	string limpiar_buffer; 
	getline(cin,limpiar_buffer);

	/* 1.. */
	hostales = obtener_hostales();
	if (hostales->isEmpty()){
		cout << endl << REDB "No hay hostales registrados en el sistema." NC << endl;
		return;
	}

	cout << CYAN "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." NC << endl;
	
	cout << endl << "Ingresa el nombre del hostal que deseas consultar detalles: ";
	getline(cin, nombre_hostal);
	if(nombre_hostal == "salir"){return;} /* en caso de que desee salir*/

	try{
		/* Si no existe el hostal se lanza una excepción y se retorna al menú principal */
		controlador -> no_existe_hostal(nombre_hostal);
	} catch(invalid_argument const& Excepcion){
		cout << endl << REDB "ERROR: " << Excepcion.what() << NC << endl;
		return;
	}

	/* 2.. */
	obtener_hostal_completo(nombre_hostal);

	/* 3.. */
	reservas_hostal = controlador->obtener_reservas_hostal(nombre_hostal);
	if(reservas_hostal->isEmpty()) { 
		cout << endl << REDB "No se han realizado reservas para el hostal indicado anteriormente." NC << endl;
		return;
	}
	mostrar_reservas_hostal(reservas_hostal, nombre_hostal);
}

/* Si da el tiempo, toda la impresión de las reservas se podría hacer sobrecargando el operador << en DTReserva_completo */
void consulta_reserva(){
	string nombre_hostal = "";
	OrderedDictionary* hostales;

	string limpiar_buffer;
	getline(cin,limpiar_buffer);
	hostales = obtener_hostales_con_promedio();
	
	if (hostales->isEmpty()){
		cout << endl << REDB "No hay hostales registrados en el sistema." NC << endl;
		return;
	}

	cout << CYAN "NOTA: Puede ingresar 'salir' en cualquier momento para volver al menu principal." NC << endl;
	
	cout << endl << "Ingrese el nombre del hostal en el cual desea consultar la reserva: " << endl;
	getline(cin,nombre_hostal);
	if(nombre_hostal == "salir"){return;} /* en caso de que desee salir*/

	try{
		controlador -> no_existe_hostal(nombre_hostal);

		cout << endl<< GREEN << "Mostrando las reservas del hostal: " << nombre_hostal << NC << endl;

		OrderedDictionary* reservas_hostal = controlador -> obtener_reservas_completas_hostal(nombre_hostal);
		for(IIterator* it = reservas_hostal -> getIterator(); it -> hasCurrent(); it -> next()){
        	DTReserva_completo* reserva = dynamic_cast<DTReserva_completo*>(it -> getCurrent());

			string estado = obtener_estado_reserva(reserva->get_estado());
		 	cout << "|Codigo: " << CYAN << reserva -> get_codigo() << NC << " |" << endl <<
			"|Estado: " << CYAN << estado << NC << " |" << endl <<
			"|Numero habitacion: " << CYAN << reserva -> get_numero_habitacion() << NC << " |" << endl;
			cout << "|Huesped(es): " << endl;

			for(IIterator* it_huespedes = reserva -> get_huespedes() -> getIterator(); it_huespedes -> hasCurrent(); it_huespedes -> next()){
				String* nombre_usuario = dynamic_cast<String*>(it_huespedes -> getCurrent());
        		cout << "->" << CYAN << nombre_usuario->getValue() << NC " |" << endl;
			}

			cout << "|Checkin: ";
			imprimir_fecha(reserva -> get_checkin());
			cout << " |" << endl << "|Checkout: ";
			imprimir_fecha(reserva -> get_checkout());
			cout << " |" << endl << endl << endl;
        }
	}catch(invalid_argument const& Excepcion){
		cout << endl << REDB "ERROR: " << Excepcion.what() << NC << endl;
	}
}

void consulta_estadia(){
	cout << endl << REDB "La remamos como unos bestias pero no llegamos a hacer este caso de uso." NC << endl;
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
	cout << endl << endl;

	while(!fecha_valida) {
		cout << "Ingrese la fecha y hora con el siguiente formato de ejemplo " << RED "'25/07/2023 - 18'" NC ": ";
		/* Se ingresa una nueva fecha por teclado */
		getline(cin, fecha_hora_str); 

		fecha_valida = verificar_fecha(fecha_hora_str, &nueva_fecha);	
	}

	controlador->set_fecha_sistema(&nueva_fecha);
	controlador -> actualizar_estado_reservas();

	cout << endl << "Nueva fecha del sistema: ";
	imprimir_fecha(controlador->get_fecha_sistema());
	cout << endl << endl;
}
int cargados = 0;
void datos_prueba(){
	if(cargados == 0){
		cargados += 1;
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
			/* ======================================================================================================= */
			// Hostel Habitación  Tipo 		  CheckIn 		  CheckOut 			Huespedes
			// HO1 	  HA1 		  Individual  01/05/22 - 2pm  10/05/22 - 10am   H1
			tm checkin_1 = {};
			istringstream iss_0("01/05/2022 - 14");
			iss_0 >> get_time(&checkin_1, "%d/%m/%y - %H");
			
			tm checkout_1 = {};
			istringstream iss_1("10/05/2022 - 10");
			iss_1 >> get_time(&checkout_1, "%d/%m/%y - %H");
			controlador -> alta_reserva_individual("La posada del finger",1,"sofia@mail.com",&checkin_1,&checkout_1);
			/* ======================================================================================================= */
			// HO3    HA6 		  Grupal      04/01/01 - 8pm  05/01/01 - 2am    H2,H3,H4,H5
			OrderedDictionary* dict_emails = new OrderedDictionary();		
			string emails[] = {"frodo@mail.com","sam@mail.com","merry@mail.com","pippin@mail.com"}; 
			char parsed_email_1[emails[0].length()+1];
			strcpy(parsed_email_1,emails[0].c_str());
			dict_emails -> add(new String(parsed_email_1), new String(parsed_email_1));	
			
			char parsed_email_2[emails[1].length()+1];
			strcpy(parsed_email_2,emails[1].c_str());
			dict_emails -> add(new String(parsed_email_2), new String(parsed_email_2));	
			
			char parsed_email_3[emails[2].length()+1];
			strcpy(parsed_email_3,emails[2].c_str());
			dict_emails -> add(new String(parsed_email_3), new String(parsed_email_3));

			char parsed_email_4[emails[3].length()+1];
			strcpy(parsed_email_4,emails[3].c_str());
			dict_emails -> add(new String(parsed_email_4), new String(parsed_email_4));		

			tm checkin_2 = {};
			istringstream iss_2("04/01/2001 - 20");
			iss_2 >> get_time(&checkin_2, "%d/%m/%y - %H");
			
			tm checkout_2 = {};
			istringstream iss_3("05/01/2001 - 02");
			iss_3 >> get_time(&checkout_2, "%d/%m/%y - %H");
			controlador -> alta_reserva_grupal("El Pony Pisador", 1, dict_emails, &checkin_2, &checkout_2);
			/* ======================================================================================================= */
			// HO1    HA3 		  Individual  7/06/22 - 2pm   30/06/22 - 11am   H1
			tm checkin_3 = {};
			istringstream iss_4("07/06/2022 - 14");
			iss_4 >> get_time(&checkin_3, "%d/%m/%y - %H");
			tm checkout_3 = {};
			istringstream iss_5("30/06/2022 - 11");
			iss_5 >> get_time(&checkout_3, "%d/%m/%y - %H");
			controlador -> alta_reserva_individual("La posada del finger",3,"sofia@mail.com",&checkin_3,&checkout_3);

			/* ======================================================================================================= */
			// HO5    HA5 		  Individual  10/06/22 - 2pm  30/06/22 - 11am   H6
			tm checkin_4 = {};
			istringstream iss_6("10/06/2022 - 14");
			iss_6 >> get_time(&checkin_4, "%d/%m/%y - %H");
			tm checkout_4 = {};
			istringstream iss_7("30/06/2022 - 11");
			iss_7 >> get_time(&checkout_4, "%d/%m/%y - %H");
			controlador -> alta_reserva_individual("Caverna Lujosa",1,"seba@mail.com",&checkin_4,&checkout_4);
			// /* ======================================================================================================= */
		
		/* Estadías */
			tm checkin_5 = {};
			istringstream iss_8("01/05/2022 - 18");
			iss_8 >> get_time(&checkin_5, "%d/%m/%y - %H");
			controlador -> alta_estadia(1, "sofia@mail.com",&checkin_5);
			tm checkin_6 = {};
			istringstream iss_9("04/01/2001 - 21");
			iss_9 >> get_time(&checkin_6, "%d/%m/%y - %H");
			controlador -> alta_estadia(2, "frodo@mail.com",&checkin_6);
			controlador -> alta_estadia(2, "sam@mail.com",&checkin_6);
			controlador -> alta_estadia(2, "merry@mail.com",&checkin_6);
			controlador -> alta_estadia(2, "pippin@mail.com",&checkin_6);
			tm checkin_7 = {};
			istringstream iss_10("07/06/2022 - 18");
			iss_10 >> get_time(&checkin_7, "%d/%m/%y - %H");
			controlador -> alta_estadia(4, "seba@mail.com",&checkin_7);
			
			// controlador -> calificar_estadia("La posada del finger",1,"muy malo",2,"sofia@mail.com");

		/* Finalización de estadías */
			// Estadía  Huesped   Check out
			// ES1 		H1 		  10/05/22 - 9am
			tm checkout_8 = {};
			istringstream iss_11("10/05/2022 - 09");
			iss_11 >> get_time(&checkout_8, "%d/%m/%y - %H");
			controlador -> finalizar_estadia(1,"sofia@mail.com",&checkout_8);
			// // ES2 		H2 		  05/01/01 - 2am
			tm checkout_9 = {};
			istringstream iss_12("05/01/2001 - 02");
			iss_12 >> get_time(&checkout_9, "%d/%m/%y - %H");
			controlador -> finalizar_estadia(2,"frodo@mail.com",&checkout_9);
			controlador -> finalizar_estadia(3,"sam@mail.com",&checkout_9);
			controlador -> finalizar_estadia(4,"merry@mail.com",&checkout_9);
			controlador -> finalizar_estadia(5,"pippin@mail.com",&checkout_9);
			// ES6 		H6 		  15/06/22 - 10pm
			tm checkout_10 = {};
			istringstream iss_13("15/06/2022 - 22");
			iss_13 >> get_time(&checkout_10, "%d/%m/%y - %H");
			controlador -> finalizar_estadia(6,"seba@mail.com",&checkout_10);

		/* Calificar estadía */
			/* Ref Estadía Huesped Comentario Calificación Fecha */
			
			/* C1  ES1     H1 
				Un poco caro para lo que ofrecen. 
				El famoso gimnasio era una caminadora (que hacía tremendo ruido) y 2 pesas, la piscina parecía
				el lago del Parque Rodó y el desayuno eran 2 tostadas con mermelada. Internet se pasaba cayendo. No vuelvo.
				3 11/05/22 - 6pm
			*/
			tm fecha_0 = {};
			istringstream iss_14("11/05/2022 - 18");
			iss_14 >> get_time(&fecha_0, "%d/%m/%y - %H");
			controlador -> calificar_estadia("La posada del finger", 1, "Un poco caro para lo que ofrecen. El famoso gimnasio era una caminadora (que hacía tremendo ruido) y 2 pesas, la piscina parecía el lago del Parque Rodó y el desayuno eran 2 tostadas con mermelada. Internet se pasaba cayendo. No vuelvo.",3,"sofia@mail.com", &fecha_0);
			/* C2 ES2 H2 Se pone peligroso de noche, no recomiendo. Además no hay caja fuerte para guardar anillos.
				2 05/01/01 - 3am 
			*/
			tm fecha_1 = {};
			istringstream iss_15("05/01/2001 - 03");
			iss_15 >> get_time(&fecha_1, "%d/%m/%y - %H");
			controlador -> calificar_estadia("El Pony Pisador", 2, "Se pone peligroso de noche, no recomiendo. Además no hay caja fuerte para guardar anillos.", 2, "frodo@mail.com",&fecha_1);
			/* C3 ES6 H6 Había pulgas en la habitación. Que lugar más mamarracho!! 1 15/06/22 - 11pm */
			tm fecha_2 = {};
			istringstream iss_16("15/06/2022 - 23");
			iss_16 >> get_time(&fecha_2, "%d/%m/%y - %H");
			controlador -> calificar_estadia("Caverna Lujosa", 6, "Había pulgas en la habitación. Que lugar más mamarracho!!", 1, "seba@mail.com",&fecha_2);

		/* Comentar calificación */
			// Calificación Empleado Respuesta 						Fecha
			// C2 			 E4 	  Desapareció y se fue sin pagar.   06/01/01 - 3pm
			tm fecha_3 = {};
			istringstream iss_17("15/06/2022 - 23");
			iss_17 >> get_time(&fecha_3, "%d/%m/%y - %H");
			controlador -> alta_respuesta(2,"barli@mail.com","Desapareció y se fue sin pagar",&fecha_3);
		cout << GREEN "Datos de prueba cargados correctamente!" NC << endl;
		controlador -> actualizar_estado_reservas();
		getchar(); //Si al llegar a esta línea, pide el enter, eliminar línea
	}else{
		cout << RED << "Los datos de prueba ya han sido cargados!, si desea cargarlos nuevamente reinicie el programa." << NC << endl;
		getchar(); //Si al llegar a esta línea, pide el enter, eliminar línea
	}
}

void exit(){
	cout << endl << endl<< CYAN "Has terminado la ejecución del programa." NC << endl << endl;
}
/*Fin funciones del menu principal*/