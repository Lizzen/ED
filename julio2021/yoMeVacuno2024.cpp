/*
NOMBRE Y APELLIDOS:

USUARIO DomJudge ASIGNADO:

*/

#include "yoMeVacuno.h"


/*
 DETERMINACION DE LA COMPLEJIDAD

*/
YoMeVacuno::YoMeVacuno(tAnio anio, tNumVacunas n) {
	// A IMPLEMENTAR
	min_anio = anio;
	vacunas = n;
}

/*
 DETERMINACION DE LA COMPLEJIDAD

*/
void YoMeVacuno::fija_Anio_NumVacunas(tAnio anio, tNumVacunas n) {
	// A IMPLEMENTAR 
	min_anio = anio;
	vacunas += n;
}

/*
 DETERMINACION DE LA COMPLEJIDAD

*/
void YoMeVacuno::registra_centro(tIdCentro id, tDireccion dir) {
	// A IMPLEMENTAR 
	if (centros.contiene(id)) {
		throw ECentroDuplicado();
	}
	
	centros.inserta(id, dir);
}

/*
 DETERMINACION DE LA COMPLEJIDAD

*/
void YoMeVacuno::registra_ciudadano(tIdCiudadano id, tAnio anio) {
	// A IMPLEMENTAR 
	if (ciudadanos.contiene(id)) {
		throw ECiudadanoDuplicado();
	}

	infoCiudadano datos;
	datos.anio = anio;
	datos.solicitado = false;
	ciudadanos.inserta(id, datos);
}

/*
 DETERMINACION DE LA COMPLEJIDAD

*/
void YoMeVacuno::pide_cita(tIdCiudadano id) {
	// A IMPLEMENTAR
	DiccionarioHash<tIdCiudadano, infoCiudadano>::Iterator ciudadano = ciudadanos.busca(id);

	if (ciudadano == ciudadanos.end()) {
		throw ECiudadanoInexistente();
	}
	else if (ciudadano.valor().anio < min_anio) {
		throw EAnioErroneo();
	}
	else if (ciudadano.valor().solicitado) {
		throw EExisteCita();
	}



	solicitudes.pon_final(id);
}

/*
 DETERMINACION DE LA COMPLEJIDAD
 
*/
bool YoMeVacuno::en_espera() {
	// A IMPLEMENTAR
	if (solicitudes.esVacia()) {
		return false;
	}

	return true;
}

/*
 DETERMINACION DE LA COMPLEJIDAD
 
*/
Lista<Asignacion> YoMeVacuno::atiende_solicitudes() {
	// A IMPLEMENTAR
	if (centros.esVacio()) {
		throw EErrorDeAtencion();
	}

	Lista<Asignacion> asignaciones;
	DiccionarioHash<tIdCentro, tDireccion>::Iterator centro = centros.begin();
	Asignacion datos;
	while (centro != centros.end() && vacunas > 0 && !solicitudes.esVacia()) {
		datos.ponCentro(centro.clave());
		datos.ponCiudadano(solicitudes.primero());
		datos.ponDireccion(centro.valor());
		solicitudes.quita_ppio();
		asignaciones.pon_ppio(datos);
		vacunas--;
		centro.next();
	}
}

/*
 DETERMINACION DE LA COMPLEJIDAD
 
*/
bool YoMeVacuno::administra_vacuna(tIdCentro idCentro) {
// A IMPLEMENTAR

}
