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
	anioLc = anio;
	num_vacunas = n;
}

/*
 DETERMINACION DE LA COMPLEJIDAD

*/
void YoMeVacuno::fija_Anio_NumVacunas(tAnio anio, tNumVacunas n) {
	// A IMPLEMENTAR 
	anioLc = anio;
	num_vacunas += n;
}

/*
 DETERMINACION DE LA COMPLEJIDAD

*/
void YoMeVacuno::registra_centro(tIdCentro id, tDireccion dir) {
	// A IMPLEMENTAR 
	if (reg_centro.contiene(id)) {
		throw ECentroDuplicado();
	}

	reg_centro.inserta(id, InfoCentro(dir, Lista<tIdCiudadano>()));
}

/*
 DETERMINACION DE LA COMPLEJIDAD

*/
void YoMeVacuno::registra_ciudadano(tIdCiudadano id, tAnio anio) {
	// A IMPLEMENTAR 
	if (reg_ciudadano.contiene(id)) {
		throw ECiudadanoDuplicado();
	}

	reg_ciudadano.inserta(id, InfoCiudadano(anio, false));
}

/*
 DETERMINACION DE LA COMPLEJIDAD

*/
void YoMeVacuno::pide_cita(tIdCiudadano id) {
	// A IMPLEMENTAR
	if (!reg_ciudadano.contiene(id)) {
		throw ECiudadanoInexistente();
	}

	if (reg_ciudadano.valorPara(id).anio != anioLc){
		throw EAnioErroneo();
	}

	if (reg_ciudadano.valorPara(id).solicitado) {
		throw EExisteCita();
	}
	solicitudes.pon_final(id);

	DiccionarioHash<tIdCiudadano, InfoCiudadano>::Iterator soli = reg_ciudadano.busca(id);
	soli.valor().solicitado = true;
}

/*
 DETERMINACION DE LA COMPLEJIDAD
 
*/
bool YoMeVacuno::en_espera() {
	// A IMPLEMENTAR
	return !solicitudes.esVacia();
}

/*
 DETERMINACION DE LA COMPLEJIDAD
 
*/
Lista<Asignacion> YoMeVacuno::atiende_solicitudes() {
	// A IMPLEMENTAR
	if (solicitudes.esVacia()) {
		throw EErrorDeAtencion();
	}

	Lista<Asignacion> atendidos = Lista<Asignacion>();
	Diccionario<tIdCentro, InfoCentro>::Iterator centro = reg_centro.begin();

	while (centro != reg_centro.end()) {
		tIdCentro centroId = centro.clave();
		tDireccion dirCentro = centro.valor().dir;
		tIdCiudadano ciudadano = solicitudes.primero();
		solicitudes.quita_ppio();
		centro.valor().l_ciu.pon_final(ciudadano);
		Asignacion asig;
		asig.ponCentro(centroId);
		asig.ponCiudadano(ciudadano);
		asig.ponDireccion(dirCentro);
		atendidos.pon_final(asig);
		centro.next();
	}
	return atendidos;
}

/*
 DETERMINACION DE LA COMPLEJIDAD
 
*/
bool YoMeVacuno::administra_vacuna(tIdCentro idCentro) {
// A IMPLEMENTAR
	if (!reg_centro.contiene(idCentro)) {
		throw ECentroInexistente();
	}

	bool vacunado = false;
	Diccionario<tIdCentro, InfoCentro>::Iterator centro = reg_centro.busca(idCentro);

	if (!centro.valor().l_ciu.esVacia()) {
		tIdCiudadano ciudadano = centro.valor().l_ciu.primero();
		reg_ciudadano.borra(ciudadano);
		centro.valor().l_ciu.quita_ppio();
		vacunado = true;
	}

	return vacunado;
}
