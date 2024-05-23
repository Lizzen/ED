/**
  NOMBRE Y APELLIDOS: David Ferreras Díaz
  LABORATORIO:
  PUESTO:
  USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/

#include "GestionAdmisiones.h"

/** 
Implementación de las operaciones de la clase Paciente 
*/

Paciente::Paciente(const string& nombre, unsigned int edad, const string& sintomas):
    _nombre(nombre), _sintomas(sintomas), _edad(edad) {}	

unsigned int Paciente::edad() const {
   return _edad;	
}
const string& Paciente::nombre() const {
   return _nombre;	
}
const string& Paciente::sintomas() const {
   return _sintomas;	
}

/**
Implementa aquí los métodos de las clases adicionales
*/

 
/**
Debes completar la implementación de las operaciones de GestionAdmisiones,
y justificar la complejidad de las mismas.
*/ 

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
*/
GestionAdmisiones::GestionAdmisiones() {
	// A IMPLEMENTAR
	pacientes = DiccionarioHash<CodigoPaciente, infoPaciente>();
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
	En el peor de los casos, la complejidad es O(n) donde n es el número de elementos usados en la lista de colisiones 
	ya que tanto inserta() como contiene() tienen un coste lineal en ese caso. Si no existen colisiones, su complejidad es O(1).
*/
void GestionAdmisiones::an_paciente(CodigoPaciente codigo, const string& nombre, unsigned int edad, const string& sintomas) {
	// A IMPLEMENTAR
	if (pacientes.contiene(codigo)) {
		throw EPacienteDuplicado();
	}

	infoPaciente datos;
	datos.nombre = nombre;
	datos.edad = edad;
	datos.sintomas = sintomas;

	pacientes.inserta(codigo, datos);
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
	La complejidad de la función es O(n) debido a que para busacar el paciente en el peor de los casos habrá que recorrer todo el diccionario.
	La asignación de valores tiene coste O(1).
*/
void GestionAdmisiones::info_paciente(CodigoPaciente codigo, string& nombre, unsigned int& edad, string& sintomas) const {
	// A IMPLEMENTAR
	DiccionarioHash<CodigoPaciente, infoPaciente>::ConstIterator paciente = pacientes.cbusca(codigo);

	if (paciente == pacientes.cend()) {
		throw EPacienteNoExiste();
	}

	nombre = paciente.valor().nombre;
	edad = paciente.valor().edad;
	sintomas = paciente.valor().sintomas;
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
	La complejidad de la función es O(n) porque en el peor de los casos, para conseguir la clave, tendrá que recorrer todo el diccionario.
*/
void GestionAdmisiones::siguiente(CodigoPaciente& codigo) const {
	// A IMPLEMENTAR
	if (pacientes.esVacio()) {
		throw ENoHayPacientes();
	}

	codigo = pacientes.cbegin().clave();
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
	O(1) ya que solo verifica si existe algun elemento en el diccionario.
*/
bool GestionAdmisiones::hay_pacientes() const {  
  // A IMPLEMENTAR
	if (pacientes.esVacio()) {
		return false;
	}

	return true;
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
	O(n) ya que en el peor de los casos, tendrá que recorrer todo el diccionario.
*/
void GestionAdmisiones::elimina(CodigoPaciente codigo) {
	// A IMPLEMENTAR
	pacientes.borra(codigo);
}
   
