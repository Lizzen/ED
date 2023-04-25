#include "Arbin.h"
#include <iostream>
#include <string>

using namespace std;


/** Indica aquí, razonadamente, la complejidad de numero_neutros
	La complejidad de la función depende del número de nodos que se encuentren en el árbol, por lo tanto su complejidad sera O(n);
*/

int numero_neutros_aux(const Arbin<int>& a, int& neutro);

unsigned int numero_neutros(const Arbin<int>& a) {
	// A IMPLEMENTAR
	int neutro = 0;
	numero_neutros_aux(a, neutro);
	return neutro;
}

int numero_neutros_aux(const Arbin<int>& a, int& neutro) {
	if (a.esVacio()) {
		return 0;
	}

	int der = numero_neutros_aux(a.hijoDer(), neutro);
	int izq = numero_neutros_aux(a.hijoIz(), neutro);

	if (der == izq) {
		++neutro;
	}

	if (a.raiz() > 0) {
		return der + izq + 1;
	}
	else {
		return der + izq;
	}
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
