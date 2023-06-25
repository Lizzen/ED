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
	if (a.esVacio()) {
		return true;
	}
	else if (a.hijoDer().esVacio() && a.hijoIz().esVacio()) {
		minimo = a.raiz();
		return true;
	}
	
	
	bool izq, der;
	int min1 = minimo, min2 = minimo;
	izq = es_rebuscado_aux(a.hijoIz(), min1);
	der = es_rebuscado_aux(a.hijoDer(), min2);

	if (izq && der && min1 != a.raiz() && min2 != a.raiz()) {
		minimo = min(min1, a.raiz());
		minimo = min(min2, min1);
		return true;
	}

	return false;
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