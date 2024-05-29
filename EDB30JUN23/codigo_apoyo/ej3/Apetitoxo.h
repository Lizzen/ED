/**
  NOMBRE Y APELLIDOS:
  USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/

#ifndef _APETITOXO_H
#define _APETITOXO_H

#include "lista.h"
#include <string>
#include "DiccionarioHash.h"
#include "cola.h"
using namespace std;


typedef unsigned int tDni; 
typedef string tFecha;  


class tReserva { // clase para la operación reservas()
public:
    void setFecha(tFecha f) { _fecha =f; }
    void setDni(tDni d) { _dni = d; }
    tFecha getFecha() const { return _fecha; }
    tDni getDni() const { return _dni; }
private:
    tFecha _fecha;
    tDni _dni;
};


class EErrorCliente{}; // para annadeSolicitud, enEspera, cedePuesto
class ENoHaySolicitudes {}; // para primeroEnEspera

class DatosSoli {
public:
    DatosSoli(tDni dni, tFecha fecha) {
        _dni = dni;
        _fecha = fecha;
    }
    tDni _dni;
    tFecha _fecha;
};

class Apetitoxo {
public:
    Apetitoxo();
    void annadeSolicitud(tDni dni, tFecha fecha);
    tFecha enEspera(tDni dni) const;  
    void primeroEnEspera(tDni& dni) const;  
    bool atiendeSolicitud();
    bool disponible(tFecha fecha) const;
    Lista<tReserva> reservas() const;
    void cedePuesto(tDni dni_del_que_cede, tDni dni_nuevo, tFecha fecha_nuevo);
private:
   // A incluir la representación
    DiccionarioHash<tDni, tFecha> _clientes;
    Lista<DatosSoli> _solicitudes;
    Lista<tReserva> _reservas;
   
};

#endif