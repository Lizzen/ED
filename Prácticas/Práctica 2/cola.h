/*
NOMBRE Y APELLIDOS PRIMER INTEGRANTE DEL GRUPO: �lvaro G�mez Tejedor 
NOMBRE Y APELLIDOS SEGUNDO INTEGRANTE DEL GRUPO: David Ferreras D�az
USUARIO DEL JUEZ DOMJUDGE: B20
 */


/**
  @file Cola.h

  Implementaci�n del TAD Cola utilizando una
  lista enlazada de nodos.

  Estructura de Datos y Algoritmos
  Facultad de Inform�tica
  Universidad Complutense de Madrid

 (c) Marco Antonio G�mez Mart�n, 2012   Mercedes G�mez Albarr�n, 2016
*/
#ifndef __COLA_LISTA_ENLAZADA_H
#define __COLA_LISTA_ENLAZADA_H
#include <cstddef>
#include <iostream>
using namespace std;

/// Excepciones generadas por algunos m�todos
class EColaVacia {};


/**
 Implementaci�n del TAD Cola utilizando una lista enlazada.

 Las operaciones son:

 - ColaVacia: -> Cola. Generadora implementada en el
   constructor sin par�metros.
 - pon: Cola, Elem -> Cola. Generadora
 - quita: Cola - -> Cola. Modificadora parcial.
 - primero: Cola - -> Elem. Observadora parcial.
 - esVacia: Cola -> Bool. Observadora.

 @author Marco Antonio G�mez Mart�n   Mercedes G�mez Albarr�n
 */
template <class T>
class Cola {
public:
    /* COMPLEJIDAD: Determina justificadamente la complejidad de esta operaci�n
		Complejidad lineal O(n).
		Su complejidad se debe a que el algoritmo recorre solo una vez la lista hasta fin,
		por lo tanto recorre n elementos y el tiempo de ejecuci�n
		es proporcional al n�mero de elementos que hay en la cola.
	*/
    void penalizaSecuencia(int inicio, int fin) {
		/*  A IMPLEMENTAR */
		if (fin >= inicio && !esVacia()) {
			Nodo* primero = NULL, *antPrimero = NULL;
			Nodo* ultimo = NULL;
			int numElems = 0;
			Nodo* act = _prim;
			bool fueraRango = false;

			while (act != NULL && numElems <= fin) {
				if (inicio == 0) {
					primero = _prim;
					antPrimero = NULL;
				}
				if (numElems == inicio - 1) {
					antPrimero = act;
					primero = act->_sig;
				}
				else if (act->_sig == NULL) {
					numElems = fin + 1;
					fueraRango = true;
				}
				else if (numElems == fin) {
					ultimo = act;
				}

				act = act->_sig;
				++numElems;
			}

			if (!fueraRango) {
				if (primero != NULL && ultimo != NULL) {
					if (antPrimero == NULL) {
						_prim = ultimo->_sig;
					}
					else {
						antPrimero->_sig = ultimo->_sig;
					}

					if (ultimo == _ult) {
						_ult = antPrimero;
					}
				}

				ultimo->_sig = NULL;
				if (_ult == NULL) {
					_prim = primero;
				}
				else {
					_ult->_sig = primero;
				}
				_ult = ultimo;
			}
		}
	}
	
	void imprime() {
		cout << "/";
		if (_prim != NULL) {
			Nodo* act;
			act = _prim;
			while (act != _ult) {
				cout << act->_elem << " ";
				act = act->_sig;
			}
			cout << act->_elem;
		}
		cout << "/";
	}


	/** Constructor; operacion ColaVacia */
	Cola() : _prim(NULL), _ult(NULL) {
	}

	
	/**
	 A�ade un elemento en la parte trasera de la cola.
	 Operaci�n generadora.

	 @param elem Elemento a a�adir.
	*/
	void pon(const T &elem) {
		Nodo *nuevo = new Nodo(elem);
		if (esVacia()) _prim = nuevo; 
		else _ult->_sig = nuevo;
		_ult = nuevo;
	}

	/**
	 Elimina el primer elemento de la cola.
	 Operaci�n modificadora parcial.

	 error: falla si la cola est� vac�a
	*/
	void quita() {
		if (esVacia())
			throw EColaVacia();
		Nodo *aBorrar = _prim;
		if (_prim == _ult) 
			_prim = _ult = NULL;
		else
			_prim = _prim->_sig;
		delete aBorrar;
	}

	/**
	 Devuelve el primer elemento de la cola. Operaci�n
	 observadora parcial.
	 
	 error: falla si la cola est� vac�a
	 @return El primer elemento de la cola.
	 */
	const T &primero() const {
		if (esVacia())
			throw EColaVacia();
		return _prim->_elem;
	}

	/**
	 Indica si la cola tiene elementos o no.

	 @return true si la cola no tiene ning�n elemento.
	 */
	bool esVacia() const {
		return _prim == NULL;
	}


	/** Destructor; elimina la lista enlazada. */
	~Cola() {
		libera();
		_prim = _ult = NULL;
	}


	/** Constructor copia */
	Cola(const Cola<T> &other) : _prim(NULL), _ult(NULL) {
		copia(other);
	}

	/** Operador de asignaci�n */
	Cola<T> &operator=(const Cola<T> &other) {
		if (this != &other) { 
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparaci�n. */
	bool operator==(const Cola<T> &rhs) const {
		Nodo *p1 = _prim;
		Nodo *p2 = rhs._prim;
		while ((p1 != NULL) && (p2 != NULL) && (p1->_elem == p2->_elem)) {
			p1 = p1->_sig;
			p2 = p2->_sig;
		}
		return (p1 == NULL) && (p2 == NULL);
	}

	bool operator!=(const Cola<T> &rhs) const {
		return !(*this == rhs);
	}
	

private:

	/**
	 Clase nodo que almacena internamente el elemento (de tipo T),
	 y un puntero al nodo siguiente, que podr�a ser NULL si
	 el nodo es el �ltimo de la lista enlazada.
	 */
	class Nodo {
	public:
		Nodo() : _sig(NULL) {}
		Nodo(const T &elem) : _elem(elem), _sig(NULL) {}
		Nodo(const T &elem, Nodo *sig) : 
		    _elem(elem), _sig(sig) {}

		T _elem;
		Nodo *_sig;
	};


	/**
	Genera una copia de other en la cola receptora
	*/
	void copia(const Cola &other) {
		if (other.esVacia())
			_prim = _ult = NULL;
		else {
			Nodo *puntAOrigen = other._prim; 
			Nodo *ultimo; 
			_prim = new Nodo(puntAOrigen->_elem); 
			ultimo = _prim; 
			while (puntAOrigen->_sig != NULL) { 
				puntAOrigen = puntAOrigen->_sig; 
				ultimo->_sig = new Nodo(puntAOrigen->_elem); 
				ultimo = ultimo->_sig; 
			}
			_ult = ultimo;
		}
	}

	
	/**
	 Elimina todos los nodos de la lista enlazada que soporta la cola.
	 */
	void libera() {
		while (_prim != NULL) {
			Nodo *aBorrar = _prim;
			_prim = _prim->_sig;
			delete aBorrar;
		}
	}

	
	/** Puntero al primer elemento. */
	Nodo *_prim;

	/** Puntero al �ltimo elemento. */
	Nodo *_ult;
};

#endif // __COLA_LISTA_ENLAZADA_H
