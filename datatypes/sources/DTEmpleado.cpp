#ifndef DTEMPLEADO_CPP_
#define DTEMPLEADO_CPP_
#include "../headers/DTEmpleado.h"

DTEmpleado::DTEmpleado(){

}

DTEmpleado::DTEmpleado(string nombre, string email, string contrasena, Cargo cargo){
    this -> nombre = nombre;
    this -> email = email;
    this -> contrasena = contrasena;
    this -> cargo = cargo;
}

DTEmpleado::DTEmpleado(string nombre, string email, string contrasena, string nombre_hostal, Cargo cargo){
    this -> nombre = nombre;
    this -> email = email;
    this -> contrasena = contrasena;
    this -> nombre_hostal = nombre_hostal;
    this -> cargo = cargo;
}

string DTEmpleado::get_nombre(){
    return this -> nombre;
}

string DTEmpleado::get_email(){
    return this -> email;
}

string DTEmpleado::get_contrasena(){
    return this -> contrasena;
}

string DTEmpleado::get_nombre_hostal(){
    return this -> nombre_hostal;
}

Cargo DTEmpleado::get_cargo(){
    return this -> cargo;
}

ostream& operator << (ostream& salida, DTEmpleado empleado) {
    string cargo;
	string nombre_hostal = (!(empleado.get_nombre_hostal()).empty()) ? empleado.get_nombre_hostal() : "No tiene hostal asignado";

    switch(empleado.get_cargo()){
		case 0:{
			cargo = "Administracion";
			break;
		}
		case 1:{
			cargo = "Limpieza";
			break;
		}
		case 2:{
			cargo = "Recepcion";
			break;
		}
		case 3:{
			cargo = "Infraestructura";
			break;
		}
	}

    salida << "| Nombre: " << empleado.get_nombre() << " |" << endl <<
	"| Email: " << empleado.get_email() << " |" << endl <<
	"| Trabaja para el hostal de nombre: " << nombre_hostal << " |" << endl <<
	"| Cargo: " << cargo << " |" << endl;

    return salida;
} 

#endif // DTEMPLEADO_CPP_