/**
  NOMBRE Y APELLIDOS: David Ferreras Díaz
  USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/

#include "biblioteca.h"
#include <iostream>
using namespace std;


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
	
*/
Biblioteca::Biblioteca() {
	// A IMPLEMENTAR

}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
	O(1) 
*/
void Biblioteca::annadir_libro(tSignatura signatura, tNumEjemplares num_ejemplares) {
	// A IMPLEMENTAR
	if (libros.contiene(signatura)) {
		throw ELibroExistente();
	}

	libros.inserta(signatura, infoLibros(num_ejemplares, Lista<tCodigo>()));
}
 

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
	O(1)
*/
void Biblioteca::annadir_socio(tCodigo id, tNombre nombre) {
	// A IMPLEMENTAR
	if (socios.contiene(id)) {
		throw ESocioExistente();
	}

	socios.inserta(id, infoSocios(nombre, Diccionario<tSignatura, tFecha>()));
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
	O(1)
*/
unsigned int Biblioteca::prestar(tSignatura signatura, tCodigo id, tFecha fecha) {
	// A IMPLEMENTAR
	if (!libros.contiene(signatura) || !socios.contiene(id)) {
		throw EPrestamoNoAdmitido();
	}

	if (socios.busca(id).valor().sig_fecha.contiene(signatura)) {
		return 0;
	}
	else if (libros.valorPara(signatura).num_ejemplares > 0) {
		socios.busca(id).valor().sig_fecha.inserta(signatura, fecha);
		Diccionario<tSignatura, infoLibros>::Iterator itc = libros.busca(signatura);
		itc.valor().num_ejemplares--;
		return 1;
	}
	else {
		libros.busca(signatura).valor().espera.pon_final(id);
		return 2;
	}
}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
	O(1)
*/
Codigo_y_Nombre Biblioteca::primeroEnEspera(tSignatura signatura) const {
	// A IMPLEMENTAR
	if (!libros.contiene(signatura)) {
		throw ELibroInexistente();
	}
	else if (libros.valorPara(signatura).espera.esVacia()) {
		throw ESinEsperas();
	}

	Codigo_y_Nombre primero;
	primero.id = libros.valorPara(signatura).espera.primero();
	primero.n = socios.valorPara(primero.id).nombre;

	return primero;
}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
	O(n)
*/
Lista<Signatura_y_Fecha> Biblioteca::prestados(tCodigo id) const {
	// A IMPLEMENTAR
	Lista<Signatura_y_Fecha> sig_fecha;
	if (!socios.contiene(id)) {
		throw ESocioInexistente();
	}
	else if (!socios.valorPara(id).sig_fecha.esVacio()) {
		Signatura_y_Fecha aux;
		Diccionario<tSignatura, tFecha>::ConstIterator itc = socios.valorPara(id).sig_fecha.cbegin();
		while (itc != socios.valorPara(id).sig_fecha.cend()) {
			aux.fecha = itc.valor();
			aux.signatura = itc.clave();
			sig_fecha.pon_final(aux);
			itc.next();
		}
	}
	
	return sig_fecha;
}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación
	O(1)
*/
bool Biblioteca::devolver(tSignatura signatura, tCodigo id, tFecha fecha) {
    // A IMPLEMENTAR
	if (!libros.contiene(signatura) || !socios.contiene(id)) {
		throw EDevolucionNoAdmitida();
	}
	else if (!socios.busca(id).valor().sig_fecha.contiene(signatura)) {
		return false;
	}
	
	socios.busca(id).valor().sig_fecha.borra(signatura);
	Diccionario<tSignatura, infoLibros>::Iterator itc = libros.busca(signatura);
	++itc.valor().num_ejemplares;
	if (!libros.busca(signatura).valor().espera.esVacia()) {
		Codigo_y_Nombre prestamoId = primeroEnEspera(signatura);
		int prestamo = prestar(signatura, prestamoId.id, fecha);
		libros.busca(signatura).valor().espera.quita_ppio();
	}

	return true;
}


