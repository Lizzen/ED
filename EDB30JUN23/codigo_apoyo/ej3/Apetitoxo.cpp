/**
  NOMBRE Y APELLIDOS:
  USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/

#include "Apetitoxo.h"


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
Apetitoxo::Apetitoxo() {
	// A IMPLEMENTAR

}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
void Apetitoxo::annadeSolicitud(tDni dni, tFecha fecha) {
	// A IMPLEMENTAR
	if (_clientes.contiene(dni)) {
		throw EErrorCliente();
	}

	_clientes.inserta(dni, fecha);
	_solicitudes.pon_final(DatosSoli(dni, fecha));
}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
tFecha Apetitoxo::enEspera(tDni dni) const {
	// A IMPLEMENTAR
	DiccionarioHash<tDni, tFecha>::ConstIterator cliente = _clientes.cbusca(dni);

	if (cliente == _clientes.cend()) {
		throw EErrorCliente();
	}

	return cliente.valor();
}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
void Apetitoxo::primeroEnEspera(tDni& dni) const {
	// A IMPLEMENTAR
	if (_solicitudes.esVacia()) {
		throw ENoHaySolicitudes();
	}

	dni = _solicitudes.primero()._dni;
}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
bool Apetitoxo::atiendeSolicitud() {
	// A IMPLEMENTAR
	if (_solicitudes.esVacia()) {
		return false;
	}

	tDni dni = _solicitudes.primero()._dni;
	tFecha fecha = _solicitudes.primero()._fecha;
	_solicitudes.quita_ppio();
	_clientes.borra(dni);

	if (disponible(fecha)) {
		tReserva reserva;
		reserva.setDni(dni);
		reserva.setFecha(fecha);
		_reservas.pon_final(reserva);
		return true;
	}

	return false;
}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
bool Apetitoxo::disponible(tFecha fecha) const {
	// A IMPLEMENTAR
	
	Lista<tReserva>::ConstIterator reserva = _reservas.cbegin();

	for (int i = 0; i < _reservas.longitud(); ++i) {
		if (reserva.elem().getFecha() == fecha) {
			return false;
		}

		reserva.next();
	}

	return true;
}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
Lista<tReserva> Apetitoxo::reservas() const {
	// A IMPLEMENTAR
	return _reservas;
}


/**
 COMPLEJIDAD: Determina y justifica aquí la complejidad de la operación

*/
void Apetitoxo::cedePuesto(tDni dni_del_que_cede, tDni dni_nuevo, tFecha fecha_nuevo) {
    // A IMPLEMENTAR
	Lista<DatosSoli>::Iterator solicitante = _solicitudes.begin();
	int i = 0;
	while (i < _solicitudes.longitud()) {
		if (solicitante.elem()._dni == dni_del_que_cede) {
			i = _solicitudes.longitud();
		}
		else {
			solicitante.next();
			++i;
		}
	}
	if (_clientes.contiene(dni_nuevo) || solicitante == _solicitudes.end()) {
		throw EErrorCliente();
	}

	solicitante.set(DatosSoli(dni_nuevo, fecha_nuevo));
}


	
