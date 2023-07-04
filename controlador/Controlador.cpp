#include "Controlador.h"
#include "../classes/headers/Habitacion.h"
#include "../classes/headers/Review.h"
using namespace std;

Controlador *Controlador::instance = nullptr;

Controlador::~Controlador() {

}

Controlador::Controlador() {
    this->hostales = new OrderedDictionary();
    this->huespedes = new OrderedDictionary();
    this->empleados = new OrderedDictionary();
    this->fecha_sistema = chrono::system_clock::now(); //Se setea la fecha actual del sistema
    this->set_contador_reserva(1);
	this->set_contador_estadia(1);
	this->set_contador_review(1);
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

/* Fecha del sistema*/
tm* Controlador::get_fecha_sistema() {
    // Se convierte la fecha a un formato de tiempo local
    time_t fecha_time = chrono::system_clock::to_time_t(this->fecha_sistema);
    tm* fecha_tm = localtime(&fecha_time);
    return fecha_tm;
}

void Controlador::set_fecha_sistema(tm* nueva_fecha) {
    tm fecha_tm = *nueva_fecha;
    time_t time = mktime(&fecha_tm);
    this->fecha_sistema = chrono::system_clock::from_time_t(time);
}

ComparacionFecha Controlador::compararFechas(tm* nueva_fecha){
    auto fecha_existente = chrono::system_clock::to_time_t(this->fecha_sistema);
    auto fecha_nueva_TP = chrono::system_clock::from_time_t(mktime(nueva_fecha));

    if (chrono::operator<(fecha_nueva_TP, chrono::system_clock::from_time_t(fecha_existente))) {
        return ComparacionFecha::Menor;
    } else if (chrono::operator>(fecha_nueva_TP, chrono::system_clock::from_time_t(fecha_existente))) {
        return ComparacionFecha::Mayor;
    } else {
        return ComparacionFecha::Igual;
    }
}

/// @brief compara el primer parametro contra el segundo (ambos fechas)
/// @return devuelve si la primera fecha es menor, mayor o igual que la segunda
ComparacionFecha Controlador::comparar_fechas_generico(tm* primera_fecha, tm* segunda_fecha){
    auto fecha_nueva_primera = chrono::system_clock::from_time_t(mktime(primera_fecha));
    auto fecha_nueva_segunda = chrono::system_clock::from_time_t(mktime(segunda_fecha));

    if (chrono::operator<(fecha_nueva_primera,fecha_nueva_segunda)) {
        return ComparacionFecha::Menor;
    } else if (chrono::operator>(fecha_nueva_primera,fecha_nueva_segunda)) {
        return ComparacionFecha::Mayor;
    } else {
        return ComparacionFecha::Igual;
    }
}
/// @brief una vez actualizada la fecha del sistema, recorre todas las reservas de todos los usuarios y todas
///aquellas reservas que haya pasado su fecha de checkout y no tengan estadias, es decir, nadie se presento,
///cambia su estado a canceladas
void Controlador::actualizar_estado_reservas(){
    for(IIterator* it_huespedes = huespedes -> getIterator(); it_huespedes -> hasCurrent(); it_huespedes -> next()){
        /*por cada huesped*/
        Huesped* huesped = dynamic_cast<Huesped*>(it_huespedes -> getCurrent());
        /*recorro sus reservas individuales*/
        for(IIterator* it_ri = huesped -> get_reservas_individuales() -> getIterator(); it_ri -> hasCurrent(); it_ri -> next()){
        Reserva* ri = dynamic_cast<Reserva*>(it_ri -> getCurrent());
        
            /*buscamos targetear reservas que no se encuentren cancelada y ademas nadie se presento e hizo una estadia*/
            if(ri -> get_estado() != 2 && ri -> get_cantidad_estadias() == 0){
                tm* checkout = ri -> get_checkout();
                if(compararFechas(checkout) == 0){
                    ri -> set_estado(Cancelada);
                }
            }
        }
        /*recorro sus reservas grupales*/
        for(IIterator* it_rg = huesped -> get_reservas_grupales() -> getIterator(); it_rg -> hasCurrent(); it_rg -> next()){
        Reserva* rg = dynamic_cast<Reserva*>(it_rg -> getCurrent());
        
            /*buscamos targetear reservas que no se encuentren cancelada y ademas nadie se presento e hizo una estadia*/
            if(rg -> get_estado() != 2 && rg -> get_cantidad_estadias() == 0){
                tm* checkout = rg -> get_checkout();
                if(compararFechas(checkout) == 0){
                    rg -> set_estado(Cancelada);
                }
            }
        }
    }
}

/// @brief compara la fecha que el usuario 'desea' reservar contra las que ya estan 'ocupadas' en una reserva
/// @param r la reserva donde se encuentran las fechas ya 'ocupadas'
/// @param fecha_deseada_checkin la fecha que el usuario 'desea' para el checkin
/// @param fecha_deseada_checkout la fecha que el usuario 'desea' para el checkout
/// @return true si las fechas no solapan | false si las fechas se solapan
bool Controlador::comparar_fechas_reserva(Reserva* r, tm* fecha_deseada_checkin, tm* fecha_deseada_checkout){
    /*armo la variable que representa la fecha checkin ya ocupada de la reserva r*/
    auto ocupada_checkin = chrono::system_clock::to_time_t(r -> get_checkin_chrono());
    /*armo la variable que representa la fecha checkout ya ocupada de la reserva r*/
    auto ocupada_checkout = chrono::system_clock::to_time_t(r -> get_checkout_chrono());

    /*armo la variable que representa la fecha deseada de checkin*/
    auto deseada_checkin = chrono::system_clock::from_time_t(mktime(fecha_deseada_checkin));
    /*armo la variable que representa la fecha deseada de checkout*/
    auto deseada_checkout = chrono::system_clock::from_time_t(mktime(fecha_deseada_checkout));

    if((chrono::operator<=(deseada_checkin, chrono::system_clock::from_time_t(ocupada_checkin))) && (chrono::operator<=(deseada_checkout, chrono::system_clock::from_time_t(ocupada_checkin)))){
        return true;
    } else if ((chrono::operator>=(deseada_checkin, chrono::system_clock::from_time_t(ocupada_checkout))) && (chrono::operator>=(deseada_checkout, chrono::system_clock::from_time_t(ocupada_checkout)))) {
        return true;
    } else {
        return false;
    }
}

/* Fin fecha del sistema*/

/* Contadores */
void Controlador::set_contador_reserva(int numero){
    contador_reserva = numero;
}

int Controlador::get_contador_reserva(){
    return contador_reserva;
}

void Controlador::set_contador_estadia(int numero){
    contador_estadia = numero;
}

int Controlador::get_contador_estadia(){
    return contador_estadia;
}

void Controlador::set_contador_review(int numero){
    contador_review = numero;
}

int Controlador::get_contador_review(){
    return contador_review;
}

/* Métodos de los casos de uso*/
void Controlador::alta_huesped(DTHuesped nuevo_huesped){
    string email = nuevo_huesped.get_email();
    char parce_char[email.length()+1];
    strcpy(parce_char,email.c_str());

    IKey* ik = new String(parce_char);
    Huesped* huesped = new Huesped(nuevo_huesped);
    this -> huespedes -> add(ik,huesped);
}

void Controlador::alta_empleado(DTEmpleado nuevo_empleado){
    string email = nuevo_empleado.get_email();
    char parce_char[email.length()+1];
    strcpy(parce_char,email.c_str());

    IKey* ik = new String(parce_char);
    Empleado* empleado = new Empleado(nuevo_empleado);
    this -> empleados -> add(ik,empleado);
}

void Controlador::alta_hostal(DTHostal nuevo_hostal){
    string nombre = nuevo_hostal.get_nombre();
    char parce_char[nombre.length()+1];
    strcpy(parce_char,nombre.c_str());

    IKey* ik = new String(parce_char);
    Hostal* hostal = new Hostal(nuevo_hostal);
    this -> hostales -> add(ik,hostal);
}

void Controlador::alta_habitacion(DTHabitacion nueva_habitacion, string nombre_hostal){
    char parce_nombre_hostal[nombre_hostal.length()+1];
    strcpy(parce_nombre_hostal,nombre_hostal.c_str());

    IKey* ik_hostal = new String(parce_nombre_hostal);
    Hostal* ptr_hostal = dynamic_cast<Hostal*>(hostales -> find(ik_hostal));

    /* Se busca si el número de habitación a ingresar ya existe en el hostal */
    IKey* ik_habitacion = new Integer(nueva_habitacion.get_numero());
    Habitacion* habitacion = dynamic_cast<Habitacion*>(ptr_hostal->get_habitaciones() -> find(ik_habitacion));

    if(habitacion){ // En caso de que exista la habitación se lanza una exepción
        throw invalid_argument("El número de habitación que ingresaste ya existe en el hostal!");  
    }
    ptr_hostal -> alta_habitacion(nueva_habitacion, ptr_hostal); // Si no existe, se da de alta
}

void Controlador::asignar_empleado_hostal(string nombre_hostal,string email_empleado,Cargo cargo){
    //1.me traigo el hostal
    char parce_char_hostal[nombre_hostal.length()+1];
    strcpy(parce_char_hostal,nombre_hostal.c_str());
    IKey* ik_hostal = new String(parce_char_hostal);
    Hostal* ptr_hostal = dynamic_cast<Hostal*>(hostales -> find(ik_hostal));

    //2.me traigo el empleado
    char parce_char_empleado[email_empleado.length()+1];
    strcpy(parce_char_empleado,email_empleado.c_str());
    IKey* ik_empleado = new String(parce_char_empleado);
    Empleado* ptr_empleado = dynamic_cast<Empleado*>(empleados -> find(ik_empleado));
    
    //3.le digo al empleado que se asigne el hostal y el cargo que le paso
    ptr_empleado-> asignar_cargo(cargo,ptr_hostal);
    //4.y le paso el empleado al hostal para que lo agrege a su lista de empleados
    ptr_hostal -> asignar_empleado(ptr_empleado);
}

void Controlador::finalizar_estadia(int codigo_estadia,string email_huesped){
    char parce_nombre_email[email_huesped.length()+1];
    strcpy(parce_nombre_email,email_huesped.c_str());
    IKey* ik_email = new String(parce_nombre_email);   
    Huesped* ptr_huesped = dynamic_cast<Huesped*>(huespedes -> find(ik_email));
    ptr_huesped -> existe_estadia_activa(codigo_estadia);
}

void Controlador::calificar_estadia(string nombre_hostal,int codigo_estadia,string comentario, int calificacion,string email_huesped){
    char parce_nombre_hostal[nombre_hostal.length()+1];
    strcpy(parce_nombre_hostal,nombre_hostal.c_str());
    IKey* ik_hostal = new String(parce_nombre_hostal);
    Hostal* ptr_hostal = dynamic_cast<Hostal*>(hostales -> find(ik_hostal));

    char parce_nombre_email[email_huesped.length()+1];
    strcpy(parce_nombre_email,email_huesped.c_str());
    IKey* ik_email = new String(parce_nombre_email);   
    Huesped* ptr_huesped = dynamic_cast<Huesped*>(huespedes -> find(ik_email));

    ptr_huesped -> calificarHostal(ptr_hostal,codigo_estadia,comentario,calificacion);    
}

void Controlador::alta_respuesta(int codigo_review,string email_empleado, string respuesta){
    char parce_nombre_email[email_empleado.length()+1];
    strcpy(parce_nombre_email,email_empleado.c_str());
    IKey* ik_email = new String(parce_nombre_email);   
    Empleado* ptr_empleado = dynamic_cast<Empleado*>(empleados -> find(ik_email));

    for(IIterator* it = huespedes->getIterator(); it -> hasCurrent(); it -> next()){
        Huesped* huesped = dynamic_cast<Huesped*>(it -> getCurrent());
        huesped -> alta_respuesta(codigo_review,ptr_empleado,respuesta);
    }

}

OrderedDictionary* Controlador::obtener_reservas_completas_hostal(string nombre_hostal){
    OrderedDictionary* dt_reservas_hostal = new OrderedDictionary();
    
    char parce_nombre_hostal[nombre_hostal.length()+1];
    strcpy(parce_nombre_hostal,nombre_hostal.c_str());
    IKey* ik_hostal = new String(parce_nombre_hostal);

    Hostal* hostal = dynamic_cast<Hostal*>(hostales -> find(ik_hostal));

    for(IIterator* it = hostal -> get_habitaciones() -> getIterator(); it -> hasCurrent(); it -> next()){
        Habitacion* habitacion = dynamic_cast<Habitacion*>(it -> getCurrent());
        for(IIterator* it_reserva = habitacion -> get_reservas() -> getIterator(); it_reserva -> hasCurrent(); it_reserva -> next()){
            
            Reserva* reserva = dynamic_cast<Reserva*>(it_reserva -> getCurrent());

            if(reserva -> get_tipo()){
                ReservaGrupal* rg = dynamic_cast<ReservaGrupal*>(it_reserva -> getCurrent());
                DTReserva_completo* dt_reserva = new DTReserva_completo(rg);
                
                IKey* ik_reserva = new Integer(rg -> get_codigo());
                
                dt_reservas_hostal -> add(ik_reserva,dt_reserva);
            } else{
                ReservaIndividual* ri = dynamic_cast<ReservaIndividual*>(it_reserva -> getCurrent());
                DTReserva_completo* dt_reserva = new DTReserva_completo(ri);
                IKey* ik_reserva = new Integer(ri -> get_codigo());
                
                dt_reservas_hostal -> add(ik_reserva,dt_reserva);
            }
        }
    }
    return dt_reservas_hostal;
}

OrderedDictionary* Controlador::obtener_reservas_hostal(string nombre_hostal){
    OrderedDictionary* dt_reservas_hostal = new OrderedDictionary();
    
    char parce_nombre_hostal[nombre_hostal.length()+1];
    strcpy(parce_nombre_hostal,nombre_hostal.c_str());
    IKey* ik_hostal = new String(parce_nombre_hostal);

    Hostal* hostal = dynamic_cast<Hostal*>(hostales -> find(ik_hostal));

    for(IIterator* it = hostal -> get_habitaciones() -> getIterator(); it -> hasCurrent(); it -> next()){
        Habitacion* habitacion = dynamic_cast<Habitacion*>(it -> getCurrent());

        for(IIterator* it_reserva = habitacion -> get_reservas() -> getIterator(); it_reserva -> hasCurrent(); it_reserva -> next()){
            
            Reserva* reserva = dynamic_cast<Reserva*>(it_reserva -> getCurrent());

            if(reserva -> get_tipo()){
                ReservaGrupal* rg = dynamic_cast<ReservaGrupal*>(it_reserva -> getCurrent());
                DTReserva* reserva = new DTReserva(rg);
                
                dt_reservas_hostal -> add(new Integer(rg -> get_codigo()), reserva);
            } else{
                ReservaIndividual* ri = dynamic_cast<ReservaIndividual*>(it_reserva -> getCurrent());

                DTReserva* reserva = new DTReserva(ri);
                dt_reservas_hostal -> add(new Integer(ri -> get_codigo()),reserva);   
            }
        }
    }
    return dt_reservas_hostal;
}

DTHostal_completo Controlador::obtener_hostal_completo(string nombre_hostal){
    char parsed_nombre_hostal[nombre_hostal.length()+1];
    strcpy(parsed_nombre_hostal, nombre_hostal.c_str());

    IKey* ik_hostal = new String(parsed_nombre_hostal);

    Hostal* hostal = dynamic_cast<Hostal*>(hostales -> find(ik_hostal));

    DTHostal_completo hostal_completo(hostal -> get_DTCompleto());
    return hostal_completo;
}

/* Fin métodos de los casos de uso*/

/* Métodos auxiliares*/

bool Controlador::verificar_email(string entrada){

    /*
    parceamos la entrada de string a un array de caracteres
    porque es lo que recibe como parametro la String que proporciona
    ICollections.
    */

    char parce_char[entrada.length()+1];
    strcpy(parce_char,entrada.c_str());

    IKey* ik = new String(parce_char);
    
    if(this -> huespedes -> member(ik)){
        return true;
    }else if(this -> empleados -> member(ik)){
        return true;
    }else{
        return false;
    }

}

/// @brief Verifica que exista un huesped con el email recibido por param
/// @return true si el mail es de un huesped, false en cualquier otro caso.
bool Controlador::validar_email_huesped(string email_huesped){
    
    /* parceamos la entrada de string a un array de caracteres
    porque es lo que recibe como parametro la String que proporciona
    ICollections. */

    char parce_char[email_huesped.length()+1];
    strcpy(parce_char, email_huesped.c_str());

    IKey* ik = new String(parce_char);
    
    if(!(this -> huespedes -> member(ik))){
        return false;
    }
    
    return true;
}

void Controlador::existe_hostal(string nombre){
    char parce_char[nombre.length()+1];
    strcpy(parce_char,nombre.c_str());

    IKey* ik = new String(parce_char);
    
    if(this -> hostales -> member(ik)){
        throw invalid_argument("Hostal ya existente!");
    }
}

void Controlador::no_existe_hostal(string nombre){
    char parce_char[nombre.length()+1];
    strcpy(parce_char,nombre.c_str());

    IKey* ik = new String(parce_char);
    
    if(!(this -> hostales -> member(ik))){
        throw invalid_argument("Hostal no existente!");
    }
}

bool Controlador::existe_hostal_bool(string nombre_hostal){
    char parce_char[nombre_hostal.length()+1];
    strcpy(parce_char,nombre_hostal.c_str());

    IKey* ik = new String(parce_char);
    
    if(this -> hostales -> member(ik)){
        return true;
    }
    return false;
}

OrderedDictionary* Controlador::obtener_hostales(){
    //por cada iteracion, paso el obj Hostal a DTHostal,
    //lo agrego a la lista y lo devuelvo

    //lista que voy a devolver con los hostales pasados a dt
    OrderedDictionary* DTHostales = new OrderedDictionary(); 

    //1. ciclar en la lista de hostales
    for(IIterator* it = hostales -> getIterator(); it -> hasCurrent(); it -> next()){
        Hostal* hostal = dynamic_cast<Hostal*>(it -> getCurrent());
        
        string cadena = hostal -> get_nombre();
        char parce_char[cadena.length()+1];
        strcpy(parce_char,cadena.c_str());

        IKey* ik = new String(parce_char);

        //2. convertirlo a dt
        DTHostal* hostal_singular = new DTHostal(hostal -> get_DT());

        //3. agregarlo a la lista
        DTHostales -> add(ik, hostal_singular);
    }

    /*
    ¿tendria que hacerle el delete a cada hostal_singular?
    en caso de hacerlo, no pierdo esa informacion de la lista tambien?
    */
    /* Alexis - En este caso el ttl del objeto hostal singular, es en el scope del for, al salir del bucle se libera. 
     En cuanto a la lista de hostales, no se debe eliminar nunca ya que es una puntero del controlador y permanece por 
     toda la ejecución del programa. En todo caso se podría poner en el destructor para que se libere */

    //4. devolver la lista
    return DTHostales;
}

OrderedDictionary* Controlador::obtener_no_empleados_hostal(string nombre_hostal){
    OrderedDictionary* DTEmpleados = new OrderedDictionary(); 
    /*estaria bueno que el parce este y el find del hostal fuera una funcion auxiliar
     por que lo vamos a usar todo el tiempo*/
    char parce_char[nombre_hostal.length()+1];
    strcpy(parce_char,nombre_hostal.c_str());

    IKey* ik = new String(parce_char);

    Hostal* ptr_hostal = dynamic_cast<Hostal*>(hostales -> find(ik));

    for(IIterator* it = empleados -> getIterator(); it -> hasCurrent(); it -> next()){
        Empleado* empleado = dynamic_cast<Empleado*>(it -> getCurrent());
        string email = empleado -> get_email();
        
        if(!ptr_hostal -> no_es(email)){
            char parce_char[email.length()+1];
            strcpy(parce_char,email.c_str());
            IKey* ik = new String(parce_char);

            //2. convertirlo a dt
            DTEmpleado* empleado_singular = new DTEmpleado(
                empleado ->get_nombre(),
                empleado -> get_email(),
                empleado -> get_contrasena(),
                " *sin asignar* ",
                empleado ->get_cargo()
            ); //estamos teniendo un error con este constructor
            
            //3. agregarlo a la lista
            DTEmpleados -> add(ik, empleado_singular);
        } 
    }
    return DTEmpleados;
}

OrderedDictionary* Controlador::obtener_usuarios(){
    OrderedDictionary* nombre_usuarios = new OrderedDictionary();

    for(IIterator* it = huespedes -> getIterator(); it -> hasCurrent(); it -> next()){
        Huesped* huesped = dynamic_cast<Huesped*>(it -> getCurrent());
        
      
        string cadena = huesped -> get_email();
        char parce_char[cadena.length()+1];
        strcpy(parce_char,cadena.c_str());

        IKey* ik = new String(parce_char);
        String* huesped_nombre = new String(parce_char);

        nombre_usuarios -> add(ik, huesped_nombre);
        //delete huesped_nombre;
    }

    for(IIterator* it = empleados -> getIterator(); it -> hasCurrent(); it -> next()){
        Empleado* empleado = dynamic_cast<Empleado*>(it -> getCurrent());
        
      
        string cadena = empleado -> get_email();
        char parce_char[cadena.length()+1];
        strcpy(parce_char,cadena.c_str());

        IKey* ik = new String(parce_char);
        String* empleado_nombre = new String(parce_char);

        nombre_usuarios -> add(ik, empleado_nombre);
        //delete huesped_nombre;
    }

    return nombre_usuarios;
}

/// @brief verifica a que tipo de usuario corresponde un determinado email
/// @param email 
/// @return retorna 0 si corresponde a un huesped, 1 si corresponde a un empleado y -1 si no existe el email
int Controlador::verificar_email_y_tipo(string email){

    char parce_char[email.length()+1];
    strcpy(parce_char,email.c_str());

    IKey* ik = new String(parce_char);
    
    if(this -> huespedes -> member(ik)){
        return 0;
    }else if(this -> empleados -> member(ik)){
        return 1;
    }
    
    return -1;
 }

DTHuesped Controlador::obtener_huesped_completo(string email){
    char parce_char_email[email.length()+1];
    strcpy(parce_char_email,email.c_str());

    IKey* ik_huesped = new String(parce_char_email);

    Huesped* huesped = dynamic_cast<Huesped*>(huespedes -> find(ik_huesped));
 
    DTHuesped huesped_completo(huesped -> get_DT());
    return huesped_completo;
}

DTEmpleado Controlador::obtener_empleado_completo(string email){
    char parce_char_email[email.length()+1];
    strcpy(parce_char_email,email.c_str());

    IKey* ik_empleado = new String(parce_char_email);

    Empleado* empleado = dynamic_cast<Empleado*>(empleados -> find(ik_empleado));
    
    DTEmpleado empleado_completo(empleado -> get_DT());
    return empleado_completo;
}

void Controlador::alta_reserva_individual(string nombre_hostal, int numero_Habitacion, string email_huesped, tm* checkin, tm* checkout){
    /*encuentro el hostal*/
    char parce_nombre_hostal[nombre_hostal.length()+1];
    strcpy(parce_nombre_hostal,nombre_hostal.c_str());

    IKey* ik_hostal = new String(parce_nombre_hostal);

    Hostal* hostal = dynamic_cast<Hostal*>(this -> hostales -> find(ik_hostal));

    /*encuentro el huesped*/
    char parce_email_huesped[email_huesped.length()+1];
    strcpy(parce_email_huesped,email_huesped.c_str());

    IKey* ik_huesped = new String(parce_email_huesped);

    Huesped* huesped = dynamic_cast<Huesped*>(this -> huespedes -> find(ik_huesped));

    hostal -> agregar_reserva(contador_reserva,numero_Habitacion, huesped, checkin, checkout, 0);
    this->set_contador_reserva((get_contador_reserva()) + 1);
}

void Controlador::alta_reserva_grupal(string nombre_hostal, int numero_habitacion, OrderedDictionary* lista_huespedes_seleccionados, tm* checkin, tm* checkout){
    /*encuentro el hostal*/
    char parce_nombre_hostal[nombre_hostal.length()+1];
    strcpy(parce_nombre_hostal,nombre_hostal.c_str());

    IKey* ik_hostal = new String(parce_nombre_hostal);

    Hostal* hostal = dynamic_cast<Hostal*>(this -> hostales -> find(ik_hostal));

    OrderedDictionary* huespedes_encontrados = new OrderedDictionary();

    /*por cada string contenida en mi lista de huespedes_seleccionados*/
    for(IIterator* it = lista_huespedes_seleccionados -> getIterator(); it -> hasCurrent(); it -> next()){
        /*casteo el ICollectible a string*/
        String* email_huesped = dynamic_cast<String*>(it -> getCurrent());
        /*con esa string hago una ik*/
        IKey* ik_email_huesped = new String(email_huesped -> getValue());
        /*con esa ik encuentro al huesped*/
        Huesped* huesped = dynamic_cast<Huesped*>(huespedes -> find(ik_email_huesped));
        /*guardo al huesped encontrado*/
        huespedes_encontrados -> add(ik_email_huesped,huesped);
    }

    hostal -> agregar_reserva(contador_reserva,numero_habitacion, huespedes_encontrados, checkin, checkout, 1);
    this->set_contador_reserva((get_contador_reserva()) + 1);
}

OrderedDictionary* Controlador::obtener_habitaciones_individuales(string nombre_hostal, string str_tipo, tm *checkin, tm *checkout){
    OrderedDictionary* lista_hab_disponibles = new OrderedDictionary();
    bool disponible = false;
    
    char parce_nombre_hostal[nombre_hostal.length()+1];
    strcpy(parce_nombre_hostal,nombre_hostal.c_str());
    IKey* ik_hostal = new String(parce_nombre_hostal);
    Hostal* hostal = dynamic_cast<Hostal*>(this -> hostales -> find(ik_hostal));

    /* Se recorren todas las habitaciones que tiene el hostal */
    for(IIterator* it = hostal -> get_habitaciones() -> getIterator(); it -> hasCurrent(); it -> next()){
        /*no se puede saber la disponibilidad con un booleano ya que este tiene solo 2 estados y se sobreescribe
        con el ultimo resultdo, es decir, si una habitacion tiene 3 reservas, y en las primeras 2 las fechas se
        solapan pero en la ultima no, el valor final de disponibilidad va a representar como que la habitacion esta
        disponible siendo que no es asi. 
        Por lo que cada para cada habitacion del hostal se le define esta flag en 0 y cada vez
        que una habitacion encuentre una reserva que se solapa, le suma 1 a esta flag, si recorre
        todas sus reservas y el flag sigue en 0 es porque realmente esta disponible.*/
        int flag_disponible = 0;
        Habitacion* habitacion = dynamic_cast<Habitacion*>(it -> getCurrent());
        IKey* ik_habitacion = new Integer(habitacion -> get_numero());

        /* Si la habitación no tiene reservas y ademas es individual entonces == disponible
        si no es individual ya se marca como no valida, ya que se puede
        dar el caso de que tenga todas reservas validas pero la habitacion no sea individual*/
        if((habitacion -> get_reservas() -> isEmpty()) && habitacion -> get_capacidad() >= 1) { 
            disponible = true;
        }else if(habitacion -> get_capacidad() != 1){
            disponible = false;
            flag_disponible += 1;
        }

        /* Si la habitación tiene reservas, se debe recorrerlas para ver cual no se solapa con el rango de fechas
         recibido por parámtro */ 
        if(!(habitacion -> get_reservas() -> isEmpty())){
            for(IIterator* it = habitacion -> get_reservas() -> getIterator(); it -> hasCurrent(); it -> next()){
                Reserva* reserva = dynamic_cast<Reserva*>(it -> getCurrent());
                /*este if se encarga de que si la capacidad de la habitacion a la que pertenece no es 1, sea
                automaticamente descartada y no se tenga en cuenta para agregarla a la lista de habitaciones disponibles*/
                if(habitacion -> get_capacidad() != 1){
                    disponible = false;
                    flag_disponible += 1;
                }
                if(!comparar_fechas_reserva(reserva, checkin, checkout)){ //el motivo de este if se explica en la definicion de 'flag_disponible'
                    flag_disponible += 1;
                }
            }     
        }
        //se agrega a la lista solo cuando la habitacion no tenia reservas o NINGUNA de sus reservas se solapa con las fechas deseadas
        if(disponible == true || flag_disponible == 0){ 
            DTHabitacion* dt_habitacion = new DTHabitacion(habitacion -> get_DT());
            lista_hab_disponibles -> add(ik_habitacion, dt_habitacion);
        }
        disponible = false; //lo setea para el siguiente bucle del for
    }
    
    return lista_hab_disponibles;
}

OrderedDictionary* Controlador::obtener_habitaciones_grupales(string nombre_hostal, string str_tipo, tm *checkin, tm *checkout){
    OrderedDictionary* lista_hab_disponibles = new OrderedDictionary();
    bool disponible = false;
    
    char parce_nombre_hostal[nombre_hostal.length()+1];
    strcpy(parce_nombre_hostal,nombre_hostal.c_str());
    IKey* ik_hostal = new String(parce_nombre_hostal);
    Hostal* hostal = dynamic_cast<Hostal*>(this -> hostales -> find(ik_hostal));

    /* Se recorren todas las habitaciones que tiene el hostal */
    for(IIterator* it = hostal -> get_habitaciones() -> getIterator(); it -> hasCurrent(); it -> next()){
        int flag_disponible = 0;

        Habitacion* habitacion = dynamic_cast<Habitacion*>(it -> getCurrent());
        IKey* ik_habitacion = new Integer(habitacion -> get_numero());

        if((habitacion -> get_reservas() -> isEmpty()) && habitacion -> get_capacidad() < 1) { 
            disponible = true;
        }else if(habitacion -> get_capacidad() <= 1){
            disponible = false;
            flag_disponible += 1;
        }

        if(!(habitacion -> get_reservas() -> isEmpty())){
            for(IIterator* it = habitacion -> get_reservas() -> getIterator(); it -> hasCurrent(); it -> next()){
                Reserva* reserva = dynamic_cast<Reserva*>(it -> getCurrent());
                
                if(habitacion -> get_capacidad() <= 1){
                    disponible = false;
                    flag_disponible += 1;
                }
                if(!comparar_fechas_reserva(reserva, checkin, checkout)){ //el motivo de este if se explica en la definicion de 'flag_disponible'
                    flag_disponible += 1;
                }
            }     
        }
        //se agrega a la lista solo cuando la habitacion no tenia reservas o NINGUNA de sus reservas se solapa con las fechas deseadas
        if(disponible == true || flag_disponible == 0){ 
            DTHabitacion* dt_habitacion = new DTHabitacion(habitacion -> get_DT());
            lista_hab_disponibles -> add(ik_habitacion, dt_habitacion);
        }
        disponible = false; //lo setea para el siguiente bucle del for
    }
    
    return lista_hab_disponibles;
}

OrderedDictionary* Controlador::obtener_huespedes(){
    OrderedDictionary* email_huespedes= new OrderedDictionary();

    for(IIterator* it = huespedes -> getIterator(); it -> hasCurrent(); it -> next()){
        Huesped* huesped = dynamic_cast<Huesped*>(it -> getCurrent());
        
      
        string cadena = huesped -> get_email();
        char parce_char[cadena.length()+1];
        strcpy(parce_char,cadena.c_str());

        IKey* ik = new String(parce_char);
        String* huesped_nombre = new String(parce_char);

        email_huespedes -> add(ik, huesped_nombre);
    }
    return email_huespedes;
}

/// @brief devuelve la capacidad de una habitacion valida dentro de un hostal
/// @param numero_habitacion el numero de la habitacion del que nos interesa saber la capacidad
/// @param nombre_hostal  el nombre del hostal donde se encuentra la habitacion
/// @return la capacidad de la habitacion
int Controlador::obtener_capacidad_habitacion(int numero_habitacion, string nombre_hostal){

    char parce_nombre_hostal[nombre_hostal.length()+1];
    strcpy(parce_nombre_hostal,nombre_hostal.c_str());
    IKey* ik_hostal = new String(parce_nombre_hostal);

    Hostal* hostal = dynamic_cast<Hostal*>(hostales -> find(ik_hostal));

    IKey* ik_habitacion = new Integer(numero_habitacion);
    Habitacion* habitacion = dynamic_cast<Habitacion*>(hostal -> get_habitaciones() -> find(ik_habitacion));
    return habitacion -> get_capacidad();
}

/*esta es una primera aproximacion donde se va a devolver el top 3 de hostales basados en un promedio
cargado a mano y no calculado por las habitaciones como deberia ser en la implementacion final*/
OrderedDictionary* Controlador::obtener_top_3_hostales(){
    /*lista donde se van a guardar los dts de todos los hostales
    que tenga en mi controlador*/
    OrderedDictionary* lista_dt_hostales = new OrderedDictionary();
    DTHostal* top1 = new DTHostal();
    DTHostal* top2 = new DTHostal();
    DTHostal* top3 = new DTHostal();
    OrderedDictionary* lista_top_3 = new OrderedDictionary();

    /*paso todos los objetos a dts*/
    for(IIterator* it = hostales -> getIterator(); it -> hasCurrent(); it -> next()){
        Hostal* hostal = dynamic_cast<Hostal*>(it -> getCurrent());

        char parce_char[hostal -> get_nombre().length()+1];
        strcpy(parce_char,hostal -> get_nombre().c_str());

        IKey* ik_hostal = new String(parce_char);
        
        DTHostal* dt_hostal = new DTHostal(hostal -> get_DT());
        lista_dt_hostales -> add(ik_hostal, dt_hostal);
    }
    
    /*por cada ciclo recorre mi 'lista_dt_hostales' y encuentra el valor 'maximo',
    este proceso se repite 3 veces por lo que en el primer ciclo va a encontrar el valor maximo
    y una vez terminada la iteracion entre los distintos hostales (el segundo for) va a guardarlo
    en mi lista_top_3 y luego lo saca de mi lista de hostales ya que dicho hostal no lo quiero
    seguir teniendo en cuenta para hacer el top
    
    los Ordered Dictionary se ordenan descendientemente de forma automatica, y dado que la ik con
    la que guardo cada valor es el i del for, este tiene que ir de mayor a menor para que 
    cuando iteremos se muestren en un orden con sentido. En cuanto a los valores arbitrarios de 3 y 1
    es para intentar representar que estamos manejando puestos pero en verdad podrian haber sido cualquier
    valor.

    ik con i = 3 es el primer puesto
    ik con i = 2 es el segundo puesto
    ik con i = 1 es el tercer puesto*/
    for(int i = 3; i >= 1; i--){
        DTHostal* maximo = new DTHostal();
        
        for(IIterator* it = lista_dt_hostales -> getIterator(); it -> hasCurrent(); it -> next()){
        DTHostal* dt_hostal = dynamic_cast<DTHostal*>(it -> getCurrent());
        float promedio_hostal_actual = dt_hostal -> get_promedio();
            if(promedio_hostal_actual >= maximo -> get_promedio()){
                maximo = dt_hostal;
            }
        }
        IKey* ik_puesto = new Integer(i);
        
        lista_top_3 -> add(ik_puesto,maximo);

        char char_ik_maximo[maximo -> get_nombre().length()+1];
        strcpy(char_ik_maximo,maximo -> get_nombre().c_str());

        IKey* ik_maximo = new String(char_ik_maximo);
        /*saco este hostal para no tenerlo en cuenta en mi siguiente busqueda*/
        lista_dt_hostales -> remove(ik_maximo);
    } 

    return lista_top_3;
}


OrderedDictionary* Controlador::obtener_reserva_usuario(string nombre_hostal,string email){
    OrderedDictionary* DTreservas_usuario = new OrderedDictionary();

    char parce_nombre_email[email.length()+1];
    strcpy(parce_nombre_email,email.c_str());
    IKey* ik_email = new String(parce_nombre_email);   
    Huesped* huesped = dynamic_cast<Huesped*>(huespedes -> find(ik_email));

    for(IIterator* it = huesped -> get_reservas_individuales()->getIterator(); it -> hasCurrent(); it -> next()){
        ReservaIndividual* reserva_individual = dynamic_cast<ReservaIndividual*>(it -> getCurrent());

        if(reserva_individual -> pertenece_a_hostal(nombre_hostal) && reserva_individual->get_estado() == 0 || reserva_individual->get_estado() == 1){
            IKey* ik_reserva_individual = new Integer(reserva_individual -> get_codigo());
            DTReserva* reserva = new DTReserva(reserva_individual);
            DTreservas_usuario -> add(ik_reserva_individual,reserva);
        }
    }

    for(IIterator* it = huesped -> get_reservas_grupales()->getIterator(); it -> hasCurrent(); it -> next()){
        ReservaGrupal* reserva_grupal = dynamic_cast< ReservaGrupal*>(it -> getCurrent());

        if(reserva_grupal -> pertenece_a_hostal(nombre_hostal) && reserva_grupal->get_estado() == 0 || reserva_grupal->get_estado() == 1){
            IKey* ik_reserva_grupal = new Integer(reserva_grupal -> get_codigo());
            DTReserva* reserva = new DTReserva(reserva_grupal);
            DTreservas_usuario -> add(ik_reserva_grupal,reserva);
        }
    }
    return DTreservas_usuario;
    //FALTA CHECKEAR ESTO CUANDO SE PUEDA CANCElAR UNA RESERVA
}

void Controlador::alta_estadia(int codigo_reserva, string email_huesped /* ,string nombre_hostal */){
    /* char parce_nombre_hostal[nombre_hostal.length()+1];
    strcpy(parce_nombre_hostal,nombre_hostal.c_str());
    IKey* ik_hostal = new String(parce_nombre_hostal);

    Hostal* hostal = dynamic_cast<Hostal*>(hostales -> find(ik_hostal)); */

    char parce_nombre_email[email_huesped.length()+1];
    strcpy(parce_nombre_email,email_huesped.c_str());
    IKey* ik_email = new String(parce_nombre_email);   
    Huesped* huesped = dynamic_cast<Huesped*>(huespedes -> find(ik_email));

    huesped -> alta_estadia(huesped,codigo_reserva);
    this->set_contador_estadia(this->get_contador_estadia() + 1);
}

int Controlador::existe_estadia(string nombre_hostal, string email_huesped){
    char parce_nombre_email[email_huesped.length()+1];
    strcpy(parce_nombre_email,email_huesped.c_str());
    IKey* ik_email = new String(parce_nombre_email);   
    Huesped* ptr_huesped = dynamic_cast<Huesped*>(huespedes -> find(ik_email));
    return ptr_huesped -> existe_estadia_activa(nombre_hostal);
 }

OrderedDictionary* Controlador::obtener_estadias_fin_huesped(string nombre_hostal, string email_huesped){
    char parce_nombre_hostal[nombre_hostal.length()+1];
    strcpy(parce_nombre_hostal,nombre_hostal.c_str());
    IKey* ik_hostal = new String(parce_nombre_hostal);

    Hostal* ptr_hostal = dynamic_cast<Hostal*>(hostales -> find(ik_hostal));

    char parce_nombre_email[email_huesped.length()+1];
    strcpy(parce_nombre_email,email_huesped.c_str());
    IKey* ik_email = new String(parce_nombre_email);   
    Huesped* ptr_huesped = dynamic_cast<Huesped*>(huespedes -> find(ik_email));

    return ptr_huesped -> estadia_fin(nombre_hostal);
}

OrderedDictionary* Controlador::listar_comentarios_sin_responder(string email_empleado){
    OrderedDictionary* reviews_a_devolver = new OrderedDictionary();
    OrderedDictionary* respuestas_de_huespedes = new OrderedDictionary();
    char parce_nombre_email[email_empleado.length()+1];
    strcpy(parce_nombre_email,email_empleado.c_str());
    IKey* ik_email = new String(parce_nombre_email);   
    Empleado* ptr_empleado = dynamic_cast<Empleado*>(empleados -> find(ik_email));

    Hostal* ptr_hostal = ptr_empleado -> get_puntero_hostal();

    for(IIterator* it = huespedes->getIterator(); it -> hasCurrent(); it -> next()){
        Huesped* huesped = dynamic_cast<Huesped*>(it -> getCurrent());
        respuestas_de_huespedes = huesped -> listar_comentarios_sin_resp(ptr_hostal ->get_nombre());
       for(IIterator* it = respuestas_de_huespedes->getIterator(); it -> hasCurrent(); it -> next()){
            DTReview* review = dynamic_cast<DTReview*>(it -> getCurrent());
            IKey* ik_review = new Integer(review -> get_codigo());
            reviews_a_devolver -> add(ik_review,review);
        }
    }
   return reviews_a_devolver;
}

/* Fin métodos auxiliares*/

