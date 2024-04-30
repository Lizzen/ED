#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;


/** Indica aquí, razonadamente, la complejidad de numero_neutros

*/

unsigned int numero_neutros_aux(const Arbin<int>& a, int& nodos) {
	if (a.esVacio()) {
		return 0;
	}

	int nodos_der = 0, nodos_iz = 0;
	int der = numero_neutros_aux(a.hijoDer(), nodos_der);
	int iz = numero_neutros_aux(a.hijoIz(), nodos_iz);
	
	if (a.raiz() > 0) {
		nodos += 1 + nodos_der + nodos_iz;
	}
	else {
		nodos += nodos_der + nodos_iz;
	}

	if (nodos_der == nodos_iz) {
		return der + iz + 1;
	}
	else {
		return der + iz;
	}
}

unsigned int numero_neutros(const Arbin<int>& a) {
	// A IMPLEMENTAR
	int nodos = 0;
	return numero_neutros_aux(a, nodos);
}

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


int main() {
	Arbin<int> arbol;
	while (cin.peek() != EOF)  {
		Arbin<int> a = lee_arbol(cin);
		cout << numero_neutros(a) << endl;
		string resto_linea;
		getline(cin, resto_linea);
	}
	return 0;
}
