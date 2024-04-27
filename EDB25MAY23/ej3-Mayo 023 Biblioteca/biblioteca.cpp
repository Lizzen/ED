/**
  NOMBRE Y APELLIDOS:	David Ferreras Díaz
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

*/
void Biblioteca::annadir_libro(tSignatura signatura, tNumEjemplares num_ejemplares) {
	// A IMPLEMENTAR
	if (libros.contiene(signatura)) {
		throw ELibroExistente();
	}

	infoLibro libro;
	libro.n = num_ejemplares;
	libro.espera = Lista<Codigo_y_Nombre>();
	libros.inserta(signatura, libro);
}
 

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
void Biblioteca::annadir_socio(tCodigo id, tNombre nombre) {
	// A IMPLEMENTAR
	if (socios.contiene(id)) {
		throw ESocioExistente();
	}

	infoSocio socio;
	socio.nombre = nombre;
	socio.SyF = Diccionario<tSignatura, tFecha>();
	socios.inserta(id, socio);
}

/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
unsigned int Biblioteca::prestar(tSignatura signatura, tCodigo id, tFecha fecha) {
	// A IMPLEMENTAR
	DiccionarioHash<tSignatura, infoLibro>::Iterator libro = libros.busca(signatura);
	DiccionarioHash<tCodigo, infoSocio>::Iterator socio = socios.busca(id);
	if (libro == libros.end() || socio == socios.end()) {
		throw EPrestamoNoAdmitido();
	}
	else if (socio.valor().SyF.contiene(signatura)) {
		return 0;
	}
	else if (libro.valor().n > 0) {
		socio.valor().SyF.inserta(signatura, fecha);
		libro.valor().n--;
		return 1;
	}
	else {
		Codigo_y_Nombre info;
		info.id = id;
		info.n = socio.valor().nombre;
		libro.valor().espera.pon_final(info);
		return 2;
	}
}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
Codigo_y_Nombre Biblioteca::primeroEnEspera(tSignatura signatura) const {
	// A IMPLEMENTAR
	DiccionarioHash<tSignatura, infoLibro>::ConstIterator libro = libros.cbusca(signatura);
	if (libro == libros.cend()) {
		throw ELibroInexistente();
	}
	else if (libro.valor().espera.esVacia()) {
		throw ESinEsperas();
	}

	return libro.valor().espera.primero();
}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
Lista<Signatura_y_Fecha> Biblioteca::prestados(tCodigo id) const {
	// A IMPLEMENTAR
	DiccionarioHash<tCodigo, infoSocio>::ConstIterator socio = socios.cbusca(id);
	if (socio == socios.cend()) {
		throw ESocioInexistente();
	}

	Diccionario<tSignatura, tFecha>::ConstIterator sf = socio.valor().SyF.cbegin();
	Lista<Signatura_y_Fecha> lista_SyF;
	Signatura_y_Fecha datos;

	while (sf != socio.valor().SyF.cend()) {
		datos.fecha = sf.valor();
		datos.signatura = sf.clave();
		lista_SyF.pon_final(datos);
		sf.next();
	}

	return lista_SyF;

}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
bool Biblioteca::devolver(tSignatura signatura, tCodigo id, tFecha fecha) {
    // A IMPLEMENTAR
	DiccionarioHash<tSignatura, infoLibro>::Iterator libro = libros.busca(signatura);
	DiccionarioHash<tCodigo, infoSocio>::Iterator socio = socios.busca(id);

	if (libro == libros.end() || socio == socios.end()) {
		throw EDevolucionNoAdmitida();
	}
	else if (!socio.valor().SyF.contiene(signatura)) {
		return false;
	}

	socio.valor().SyF.borra(signatura);
	libro.valor().n++;

	if (!libro.valor().espera.esVacia()) {
		prestar(signatura, libro.valor().espera.primero().id , fecha);
		libro.valor().espera.quita_ppio();
	}

	return true;
}


