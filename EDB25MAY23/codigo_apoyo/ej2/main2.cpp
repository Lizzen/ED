/**
  NOMBRE Y APELLIDOS: David Ferreras Díaz
  USUARIO DE DOMJUDGE USADO EN EL EXAMEN:
*/


#include "Arbin.h"
#include <iostream>
#include <string>
using namespace std;


/*
*  COMPLEJIDAD: Determina justificadamente la complejidad 
*	O(n) ya que se tiene que recorrer todos los nodos del árbol. 
* 
*/
bool es_rebuscado_aux(const Arbin<int>& a, int& minimo) {
	// A IMPLEMENTAR
	if (!a.esVacio()) {
		bool der, iz;
		int min_der = minimo, min_iz = minimo;

		der = es_rebuscado_aux(a.hijoDer(), min_der);
		iz = es_rebuscado_aux(a.hijoIz(), min_iz);

		minimo = a.raiz();
		if (der && iz && min_der != minimo && min_iz != minimo) {
			if (min_der > min_iz) {
				minimo = min(min_iz, minimo);
			}
			else {
				minimo = min(min_der, minimo);
			}
		}
		else { return false; }
	}

	return true;
}

bool es_rebuscado(const Arbin<int>& a) {
	 // A IMPLEMENTAR
	int minimo = 10000;
	return es_rebuscado_aux(a, minimo);
}


/*
*  NO MODIFICAR EL CODIGO QUE SIGUE
*
*/

Arbin<int> lee_arbol(istream& in) {
	char c;
	in >> c;
	switch (c) {
	case '#': return Arbin<int>();
	case '[': {
		int raiz;
		in >> raiz;
  		in >> c;
		return Arbin<int>(raiz);
	}
	case '(': {
		Arbin<int> iz = lee_arbol(in);
		int raiz;
		in >> raiz;
		Arbin<int> dr = lee_arbol(in);
		in >> c;
		return Arbin<int>(iz, raiz, dr);
	}
	default: return Arbin<int>();
	}
}

void muestra_solucion(bool rebuscado) {
  if (rebuscado) {
	 cout << "SI" << endl; 
  }	
  else {
	 cout << "NO" << endl; 
  }
}

int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		Arbin<int> a = lee_arbol(cin);
		muestra_solucion(es_rebuscado(a));
		string resto_linea;
		getline(cin, resto_linea);
	}
    return 0;       
}
